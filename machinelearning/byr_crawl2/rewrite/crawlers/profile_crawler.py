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
    
    def store(self, p_info):
        self.db.execute('select url from %s' % (byr_tables["outline_section"]))
        stored_urls = self.db.fetchall()
        print stored_urls
        values = ""
        for url, name in p_info.items():
            if    (url,) not in stored_urls:
                #print "new url", url
                values += "('%s', '%s')," % (name, url)
        values = values.rstrip(',')
        if values:
            sql = "insert into %s(name, url) values %s;" % (byr_tables["outline_section"], values)
            print sql
            nrows = self.db.execute(sql)
            if nrows != len(p_info):
                self.log.log_err("insert not complete:inserted % rows in origin % rows"
                            % (nrows, len(p_info)))
            else:
                print "success inserted"
        self.db.commit()
        self.db.close()