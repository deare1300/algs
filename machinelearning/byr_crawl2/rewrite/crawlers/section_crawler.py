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

class SectionCrawler(Crawler):
    def __init__(self, path_url = '/',
                 root_url = default_url, headers = None, 
                 profile_id = None, level = 1, parent_section_id = 0):
        super(SectionCrawler, self).__init__(path_url = path_url, 
              root_url = root_url, headers = headers)
        self.section_id = None
        self.profile_id = self.section_id
        self.level = level
        self.parent_id = parent_section_id
        self.db = DB()
    
    def crawl_next(self, url, parent_id):
        child_crawler = SectionCrawler(path_url = url, 
              root_url = self.root_url, headers = self.headers,
              profile_id = self.profile_id, level = self.level+1, parent_section_id = parent_id
              )
        child_crawler.crawl(self.download_args, self.download_code)
    
    def normal_parse(self, tr):
        e = {"title": None,
                 "chairman": None,
                 "latest_subject": None,
                 "online_num":None,
                 "today_updated": None,
                 "subject_num":None,
                 "article_num": None
                  }
            #print tr
        title1 = tr.find("td", attrs = {"class": re.compile("^title_1")})
        title2 = tr.find("td", attrs = {"class": re.compile("^title_2")})
        title3 = tr.find("td", attrs = {"class": re.compile("^title_3")})
        title4 = tr.find("td", attrs = {"class": re.compile("^title_4")})
        title5 = tr.find("td", attrs = {"class": re.compile("^title_5")})
        title6 = tr.find("td", attrs = {"class": re.compile("^title_6")})
        title7 = tr.find("td", attrs = {"class": re.compile("^title_7")})
        
        #print title1
        e["title"] = self.__parse_element(title1)
        e["chairman"] = self.__parse_element(title2)
        e["latest_subject"] = self.__parse_element(title3)
        if title4:
            e["online_num"] = title4.text
        if title5: 
            e["today_updated"] = title5.text  
        if title6: 
            e["subject_num"] = title6.text
        if title7:
            e["article_num"] = title7.text
        return e
    
    def dir_parse(self, tr):
        e = {"title": None,
                 "chairman": None,
                 "latest_subject": None,
                 "online_num":None,
                 "today_updated": None,
                 "subject_num":None,
                 "article_num": None
                  }
        title1 = tr.find("td", attrs = {"class": re.compile("^title_1")})
        #title2 = tr.find("td", attrs = {"class": re.compile("^title_2")})
        e["title"] = self.__parse_element(title1)
        return e
    
    def __parse_tr(self, tr):
        if tr.find("th"):
            return None
        e = self.normal_parse(tr)
        if e is None:
            e = self.dir_parse(tr)
        return e
    
    def parse(self, content):
        ret = []
        soup = BeautifulSoup(content, from_encoding = self.parse_code)
        table = soup.find("table", attrs={"class": "board-list corner"})
        if table == None:
            print "cannot find table"
            return
        trs = table.findAll("tr")
        for tr in trs:
            e = self.__parse_tr(tr)
            if e:
                ret.append(e)
        return ret
    
    def crawl(self, download_args={}, download_code="gbk"):
        info = Crawler.crawl(self, download_args=download_args, download_code=download_code)
        
        for e in info:
                if not e or e["title"] == None:
                    continue
                url = e["title"][0]
                name = e["title"][1]
                #print re.match("^\s*$", e["online_num"]), e["online_num"]
                if (url,) in urls:
                    continue
                
                if e["latest_subject"] == None and e["chairman"] == None:
                    
                    print "============================================next level",e
                    sql = "insert into %s(url, name, level, outline_id, parent_id) values('%s', '%s', %s, %s, %s)" % (byr_tables["sub_section"], url, name, self.level, self.section_id, self.parent_id)
                    #print sql
                    try:
                        self.db.execute(sql)
                        self.db.commit()
                        insert_id = self.db.lastrowid
                        self.crawl_next(url, parent_id = insert_id)
                    except Exception, e:
                        print e           
                else:
                    if e["chairman"] == None:
                        e["chairman"] = ("null", "null")
                    #print byr_tables["sub_section"], url, name, self.level, self.section, self.parent_id, e["chairman"][1], e["online_num"], e["subject_num"],e["article_num"]
                    sql = "insert into %s(url, name, level, outline_id, parent_id, author, online_num, total_subject ,total_article) values('%s', '%s', %s,      %s,        %s,     '%s', %s, %s, %s);" % (byr_tables["sub_section"], url, name, self.level, self.section_id, self.parent_id, e["chairman"][1], e["online_num"], e["subject_num"],e["article_num"])
                    try:
                        self.db.execute(sql)
                    except Exception, e:
                        print e
        else:
            print "not supported"
        self.db.commit()
        self.db.close()
        return 