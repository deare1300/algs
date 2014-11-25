#!:/bin/python
# -*- coding:utf-8 -*-
'''
Created on 2014-11-23

@author: Administrator
'''
from rewrite.crawlers.abstract_crawler import Crawler
from rewrite.database.db import DB
import json
from bs4 import BeautifulSoup
from rewrite.database.tables import byr_tables
from rewrite.crawlers.abstract_crawler import default_url
import re
import time

class ArticleCrawler(Crawler):
    def __init__(self, path_url = '/',
                 root_url = default_url, headers = None, 
                 subject_id = None):
        super(ArticleCrawler, self).__init__(path_url = path_url, 
              root_url = root_url, headers = headers)
        self.section_id = subject_id
    
    def get_position(self, sp):
        name = sp["name"]
        p = re.compile("^a(\d+)$")
        pos = p.findall(name)
        if not pos:
            return -1
        return int(pos[0])
    
    def get_user(self, sp):
        user_name = sp.find("span", attrs = {"class":
                                             "a-u-name"})
        if not user_name:
            print sp
            print "not find user name"
            return
        a = user_name.find("a", href = True)
        if not a:
            print sp
            print "cannot find href"
            user = user_name.text
        else:
            p = re.compile("^/user/query/(\w+)$")
            user = p.findall(a["href"])
        if not user:
            print "no user"
            return
        return user[0]
    
    def get_source(self, sp):
        source = {}
        print sp
        fonts = sp.findAll("font", attrs = {"class": re.compile("f0")})
        #print len(fonts), fonts[len(fonts) - 2]
        if len(fonts) < 2:
            return
        font = fonts[len(fonts)-2]
        if not font:
            print "not found font", sp
            return
        
        a = font.find("a", href = True)
        if not a:
            print "not found source"
            source["source"] = font.text
        else:    
            source["source"] = a["href"]
        p = re.compile(r"\[FROM:\s*([\d\.\*]+)+\]")
        content = font.__str__()
        ip = p.findall(content)
        if not ip:
            print "not found ip"
            #sys.exit()
            return
        source["ip"] = ip[0]
        return source
    
    def get_content(self, sp):
        content = {}
        context = sp.__str__()
        content["context"] = context
        source = self.get_source(sp)
        print "source", source
        if source:
            content.update(source)
        return content
        
    def get_time(self, sp):
        content = sp.__str__()
        #print "get_time 发信站", content
        p = re.compile(r'发信站:[^\(]+\(([^\)]+)\)')
        times = p.findall(content)
        print times
        if times:
            return times[0]
        #sys.exit()
        
    def get_article(self, sp):
        article = {}
        #print sp
        user_info = sp.find("tr", attrs = {"class":"a-head"})
        content = sp.find("tr", attrs = {"class":"a-body"})
        bottom = sp.find("tr", attrs = {"class": "a-bottom"})
        
        #print "content",content
        times = self.get_time(content)
        if not times:
            print "not get time"
            return 
        article["time"] = times
        user = self.get_user(user_info)
        if not user:
            print "not get user"
            return
        article["user"] = self.get_user(user_info)
        contents = self.get_content(content)
        if not contents:
            print "not get contents"
            return
        #print article
        article.update(contents)
        print "aritlce", article
        return article
        
    def parse(self, content):
        res = []
        sp = BeautifulSoup(content, from_encoding=self.parse_code)
        content = sp.find("div", attrs = {"class": re.compile("^b-content")})
        if not content:
            print "not content"
            return
        poses = content.findAll("a", attrs = {"name": re.compile("^a\d+$")})
        articles = content.findAll("table", attrs = {"class": "article"})
        if (len(poses)) != len(articles):
            print "pos != article"
            return
        for i in range(len(poses)):
            position = self.get_position(poses[i])
            article = self.get_article(articles[i])
            if "ip" not in article:
                continue
            if not article:
                continue
            article["position"] = position
            print article
            res.append(article)
        print type, res
        return res
    
    def parse_page(self, page_link):
        a = page_link.find('a', href = True)
        if a is None:
            return 0
        href = a["href"]
        p = re.compile("^[^\?]+\?p=([0-9]+)$")
        page = p.findall(href)
        if not page:
            return 0
        # not the page[0][0]
        return int(page[0])
    
    def get_pages(self, content):
        sp = BeautifulSoup(content, from_encoding=self.parse_code)
        page_sp = sp.find("ul", attrs = {"class":"page"})
        if page_sp is None:
            return -1
        page_main = page_sp.find("ol", attrs = {"class": "page-main"})
        if page_main is None:
            return -1
        pages = page_main.findAll("li", attrs = {"class":"page-normal"})
        if pages is None:
            return 1
        last_pages = pages[len(pages)-1]
        a = last_pages.find("a", href = True)
        if a is None:
            return -1
        link = a["href"]
        return self.parse_page(link)
        
    def crawl(self, max_page = 10000):
        res = []
        content = self.download()
        pages = self.get_pages(content)
        pages_res = self.parse(content)
        if pages_res:
            res.extend(pages_res)
        else:
            return
        if pages > max_page:
            pages = max_page
        for page in range(2, pages+1):
            content = self.download(args = {"p": page}, code = "mbcs")
            sp = BeautifulSoup(content, from_encoding = "utf8")
            page_res = self.parse(sp)
            if page_res:
                res.extend(page_res)
        print "final", res
