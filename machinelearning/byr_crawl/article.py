#!:/bin/python
# -*- coding:utf-8 -*-

# author deenw

# this file is spider for the article anwser
import urllib2
import sys
import os
from bs4 import * 
from create_table import connect
import cookielib
import urllib
from log import Log
from create_table import byr_tables
import json
from login import LoginBYR
import re
import time

class BYRArticle:
    def __init__(self, article_url = None,  subject_id = None, root_url = "http://bbs.byr.cn/",
                 user = "deare1300"):
        self.article_url = article_url
        self.root_url = root_url
        self.user = user
        self.subject_id =subject_id
        headers = dict()
        headers["Connection"] = "keep-alive"
        headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
        headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
        headers["Accept-Encoding"] = "deflate"
        headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
        headers["X-Requested-With"] = "XMLHttpRequest"
        self.headers = headers
        
    def download(self, page = 1):
        url = "%s%s?p=%d" % (self.root_url, self.article_url, page)
        req = urllib2.Request(url, headers = self.headers)
        res = urllib2.urlopen(req)
        origin_text =res.read()
        utf8_text = origin_text.decode("mbcs").encode("UTF8")
        return utf8_text
    
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
        
    def parse(self, sp):
        res = []
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
                line = raw_input("continue y?")
                if line == "Y" or line == "y":
                    sys.exit()
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
    
    def get_pages(self, sp):
        
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
        sp = BeautifulSoup(content, from_encoding = "utf8")
        
        pages = self.get_pages(sp)
        pages_res = self.parse(sp)
        if pages_res:
            res.extend(self.parse(sp))
        else:
            return
        if pages > max_page:
            pages = max_page
        for page in range(2, pages+1):
            content = self.download(page = page)
            sp = BeautifulSoup(content, from_encoding = "utf8")
            page_res = self.parse(sp)
            if page_res:
                res.extend(page_res)
        print "final", res
        self.store(res)
    
    def store(self, anwsers):
        print "anwser type",type(anwsers)
        if not anwsers:
            return
        conn = connect()
        conn.set_character_set('utf8')
        cur = conn.cursor()
        cur.execute("set names utf8;")
        cur.execute('SET CHARACTER SET utf8;')
        cur.execute('SET character_set_connection=utf8;')
        cur.execute('select answer_pos from %s where subject_id = %d' % (byr_tables["article"], self.subject_id))
        pos = cur.fetchall()
        sql = "insert into %s(subject_id, answer_pos, answer_user, answer_content, answer_time,\
            answer_ip, answer_source) values" % byr_tables["article"]
        
        values = ""
        print pos
        print type(anwsers[0])
        for e in anwsers:
            print type(e),e
            if (e["position"],) in pos:
                continue
            for key, value in e.items():
                if type(value) == str:
                    e[key] = value.replace("'", r"\'")
            print values
            values += "(%d, %d, '%s', '%s', '%s',\
                '%s', '%s')," % (self.subject_id, e["position"], e["user"], e["context"], e["time"],\
                                 e["ip"], e["source"])
        if not values:
            return
        values = values.strip(',')
        sql += values
        print sql
        try:
            cur.execute(sql)
        except Exception, e:
            print e
        conn.commit()
        conn.close()

class ArticleEngine:
    def __init__(self, user = None, root_url = "http://bbs.byr.cn/"):
        self.user = user
        self.root_url = root_url
    
    def login(self):
        self.login_client = LoginBYR()
        return self.login_client.login()
    
    def get_all_articles(self):
        conn = connect()
        conn.set_character_set('utf8')
        cur = conn.cursor()
        cur.execute("set names utf8;")
        cur.execute('SET CHARACTER SET utf8;')
        cur.execute('SET character_set_connection=utf8;')
        cur.execute("select id, url from subject")
        articles = cur.fetchall()
        conn.close()
        return articles
    
    def get_new_articles(self):
        conn = connect()
        conn.set_character_set('utf8')
        cur = conn.cursor()
        cur.execute("set names utf8;")
        cur.execute('SET CHARACTER SET utf8;')
        cur.execute('SET character_set_connection=utf8;')
        cur.execute("select id, url from subject where not exists\
                    (select subject_id from article where subject_id = subject.id)")
        articles = cur.fetchall()
        conn.close()
        return articles
        
        
    def get_articles(self, section_id = None):
        if section_id == None:
            return self.get_all_articles()
        
    def crawl(self, new_article = False):
        if not self.login():
            print "login failed"
            return 
        if not new_article:
            articles = self.get_articles()
        else:
            articles = self.get_new_articles()
        for subject_id, url in articles:
            article = BYRArticle(article_url = url , subject_id = subject_id, root_url = self.root_url, user = self.user)
            article.crawl()
            
if __name__ == '__main__':
    article = ArticleEngine()
    article.crawl(new_article = True)
    