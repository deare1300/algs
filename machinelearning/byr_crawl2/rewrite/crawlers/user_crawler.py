#!:/bin/python
#--*--encoding:utf-8--*--

# @author: deenw
# this file is create the database and the table
'''
Created on 2014-11-24

@author: Administrator
'''
from rewrite.crawlers.abstract_crawler import Crawler
from rewrite.database.db import DB
import json
from bs4 import BeautifulSoup
from rewrite.database.tables import byr_tables
from rewrite.crawlers.abstract_crawler import default_url
import MySQLdb
import re
import time

class UserCrawler(Crawler):
    def __init__(self, username, path_url = '/',
                 root_url = default_url, headers = None):
        super(UserCrawler, self).__init__(path_url = path_url, root_url = root_url, headers = headers)
        self.username = username
        self.username = username
        self.db = DB()
    
    def process_url(self):
        url = Crawler.process_url(self)
        url = "%s%s.json" % (url, self.username)
        return url
        
    def parse(self, content):
        #print "content",content
        msg = json.loads(content)
        return (msg,)
        


if __name__ == "__main__":
    from rewrite.engine.abstract_engine import Engine
    headers = dict()
    headers["Connection"] = "keep-alive"
    headers["Accept"] = "application/json,text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8,q=0.01"
    headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
    headers["Accept-Encoding"] = "deflate"
    headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
    headers["X-Requested-With"] = "XMLHttpRequest"
    login_url = 'http://bbs.byr.cn/user/ajax_login.json'
    e = Engine(login_headers=headers, login_url= login_url, user="deare1300", passwd="temp110")
    if e.login():
        print "login success"
        c = UserCrawler("deare1300", path_url="/user/query", headers=headers)
        c.crawl() 
    else:
        print "failed"
                
        