#!:/bin/python
# -*- coding:utf-8 -*-

# author deenw

# this file is spider for the subject list
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


class BYRSubject:
    def __init__(self, section_url = None, section_id = None, 
                 root_url = "http://bbs.byr.cn/", user = "deare1300"):
        self.root_url = root_url
        self.section_url = section_url
        self.section_id = section_id
        headers = dict()
        headers["Connection"] = "keep-alive"
        headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
        headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
        headers["Accept-Encoding"] = "deflate"
        headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
        headers["X-Requested-With"] = "XMLHttpRequest"
        self.headers = headers
        self.user = user
        self.spider_time = time.strftime("%H-%m-%d %X", time.localtime())
        
    def download(self, page=1):
        url = "%s%s?p=%d" % (self.root_url, self.section_url, page)
        req = urllib2.Request(url, headers = self.headers)
        res = urllib2.urlopen(req)
        origin_text =res.read()
        utf8_text = origin_text.decode("mbcs").encode("UTF8")
        return utf8_text
    
    def parse_user(self, link_str):
        user_pattern = re.compile("/user/query/(\w+)$")
        users = user_pattern.findall(link_str)
        if not users:
            return ""
        return users[0]
    
    def parse_line(self, tr):
        #print "tr-----------",tr
        res = {}
        tds = tr.findAll("td")
        if not tds:
            return {}
        print "*****************************************"
        
        for i in range(len(tds)):
            #print type(tds[i])
            td = tds[i]
            if i == 1:
                #print "name"
                link = td.find("a", href = True)
                if not link:
                    return {}
                #print link
                res["subject"] = link.text
                res["url"] = link["href"]
                
            if i == 2:
                publish_time = tds[i]
                if publish_time:
                    #print "time"
                    res["publish_time"] = publish_time.text
                    #print publish_time
                    continue
                
            if i == 3:
                author = tds[i].find("a", href = True)
                if author:
                    #print "author"
                    res["author"] = self.parse_user(author["href"])
                    print author
                    continue
            if i == 4:
                reply_num = tds[i]
                if reply_num:
                    #print "reply"
                    res["reply_num"] = reply_num.text
                    continue
                
            if i == 5:
                print "latest user time", tds[i]
                latest_author_time = tds[i]
                if latest_author_time:
                    #print "latest_author"
                    res["latest_reply_time"] = latest_author_time.text
                    continue
            
            if i == 6:
                latest_author = tds[i].find("a", href = True)
                if latest_author:
                    res["latest_author"] = self.parse_user(latest_author["href"])
        #latest_reply_author = tr.find("td", atrrs = {"class": re.compile("^title_11")})
        print "result is",res
        if len(res) != 7:
            print len(res),res
            return {}
        #sys.exit()
        return res                    
    
    def parse(self, sp):
        ret = []
        div_content = sp.find("div", attrs={"class": "b-content"})
        if div_content is None:
            print "content is None"
            return 
        table = div_content.find("table")
        if table is None:
            print "table is None"
            return
        tbody = table.find("tbody")
        if tbody is None:
            print "tbody is None"
            return
        trs = table.findAll("tr")
        for tr in trs:
            #print tr
            line = self.parse_line(tr)
            if line:
                ret.append(line)
        return ret
    
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
        page_main = sp.find("ol", attrs = {"class": re.compile("^page-main")})
        if page_main is None:
            return 0
        pages = page_main.findAll("li", attrs = {"class": re.compile("^page-[normal|select]")
                                       })
        print pages
        if len(pages) == 1:
            return 1
        pre_last = pages[len(pages) -2]
        last_page = pages[len(pages)-1]
        last = self.parse_page(last_page)
        pre = self.parse_page(pre_last)
        
        print last, pre
        if last < pre:
            return pre
        return last
    '''
    sub_section_id int,\
            url varchar(255) not null,\
            subject varchar(255) not null,\
            publish_time varchar(255) not null,\
            author varchar(255) not null,\
            reply_num int not null,\
            latest_reply_time varchar(255),\
            latest_reply_author varchar(255),\
            spider_time varchar(255),\
    '''
    def store(self, subjects):
        if not subjects:
            return
        conn = connect()
        conn.set_character_set('utf8')
        cur = conn.cursor()
        cur.execute("set names utf8;")
        cur.execute('SET CHARACTER SET utf8;')
        cur.execute('SET character_set_connection=utf8;')
        cur.execute('select url from %s' % (byr_tables["subject"]))
        
        sql = "insert into %s(sub_section_id, url, subject, publish_time, author,\
            reply_num, latest_reply_time, latest_reply_author, spider_time) values" % byr_tables["subject"]
        urls = cur.fetchall()
        print subjects
        values = ""
        for s in subjects:
            if (s["url"],) not in urls:
                for key, value in s.items():
                    if value.find("'") >= 0:
                        s[key] = value.replace("'", r"\'")
                values += "(%d, '%s', '%s', '%s', '%s', \
                    %d, '%s', '%s', '%s')," % (self.section_id, s["url"], s["subject"], s["publish_time"], s["author"],
                                              int(s["reply_num"]), s["latest_reply_time"], s["latest_author"], self.spider_time)
        values = values.strip(',')
        if not values:
            print "not insert"
        else:    
            sql += values
            #print sql
            try:
                cur.execute(sql)   
                conn.commit()
            except Exception, e:
                print e
        conn.close()
        
    def crawl(self, max_page = 10000):
        content = self.download()
        print content
        sp = BeautifulSoup(content, from_encoding="utf8")
        pages = self.get_pages(sp)
        print "total page is",pages
        subjects = self.parse(sp)
        self.store(subjects)
        if pages > max_page:
            pages = max_page
        
        for i in range(2, pages+1):
            content = self.download(i)
            sp = BeautifulSoup(content)
            subjects = self.parse(sp)
            self.store(subjects)
 
class CrawlBYRSubject:
    def __init__(self, user = "deare1300"):
        self.user = user
    
    def get_sections(self):
        conn = connect()
        conn.set_character_set('utf8')
        cur = conn.cursor()
        cur.execute("set names utf8;")
        cur.execute('SET CHARACTER SET utf8;')
        cur.execute('SET character_set_connection=utf8;')
        cur.execute('select id, url from %s' % (byr_tables["sub_section"]))      
        sections = cur.fetchall()
        conn.close()
        return sections

    def filter_sections(self, section_info):
        filtered_section = []
        conn = connect()
        conn.set_character_set('utf8')
        cur = conn.cursor()
        cur.execute("set names utf8;")
        cur.execute('SET CHARACTER SET utf8;')
        cur.execute('SET character_set_connection=utf8;')
        cur.execute('select distinct sub_section_id from %s;' % byr_tables["subject"])
        sections = cur.fetchall()
        for sid, url in section_info:
            if (sid,) not in sections:
                filtered_section.append((sid, url))
        return filtered_section
        
    def __filter(self, filter_func,urls, args = None):
        return self.filter_func(urls)
        
    def crawl(self):
        self.login = LoginBYR()
        if not self.login.login():
            print "login failed"
            return 
        sections = self.get_sections()
        filtered_sections = self.filter_sections(sections)
        for sid, url in filtered_sections:
            sub = BYRSubject(section_id = sid, section_url = url)
            try:
                sub.crawl()
            except Exception, e:
                print e
        print "crawl over-----"
    
if __name__ == '__main__':
    #'''
    sub_spider = CrawlBYRSubject() 
    sub_spider.crawl()
    #''' 