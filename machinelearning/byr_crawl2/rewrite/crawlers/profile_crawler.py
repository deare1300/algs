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
#default_url = "http://bbs.byr.cn/"

class ProfileCrawler(Crawler):
    def __init__(self, path_url = '/',
                 root_url = default_url, headers = None):
        super(ProfileCrawler, self).__init__(path_url = path_url, 
              root_url = root_url, headers = headers)
        self.db = DB()
    
    def process_url(self):
        return "http://bbs.byr.cn/section/ajax_list.json?uid=deare1300&root=list-section"
        return Crawler.process_url(self)+"?uid=deare1300&root=list-section"
    def parse(self, content):
        json_profiles = json.loads(content)
        ret = dict()
        for p in json_profiles:
            if "t" not in p:
                continue
            soup = BeautifulSoup(p["t"], from_encoding = self.parse_code)
            a = soup.find('a', href = True)
            if a:
                ret[a['href']] = a.text
        return (ret,) 
    