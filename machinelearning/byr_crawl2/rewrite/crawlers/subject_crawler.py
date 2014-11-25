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

class SubjectCrawler(Crawler):
    def __init__(self, path_url = '/',
                 root_url = default_url, headers = None, 
                 section_id = None):
        super(SubjectCrawler, self).__init__(path_url = path_url, 
              root_url = root_url, headers = headers)
        self.section_id = section_id
        self.spider_time = time.strftime("%H-%m-%d %X", time.localtime())
        self.db = DB()
    
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
    
    def parse(self, content):
        ret = []
        sp = BeautifulSoup(content, from_encoding= self.parse_code)
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
    def get_pages(self, content):
        sp = BeautifulSoup(content, from_encoding= self.parse_code)
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
        if last < pre:
            return pre
        return last
    
    def crawl(self, max_page = 10000):
        ret = []
        content = self.download()
        pages = self.get_pages(content)
        print "total page is",pages
        subjects = self.parse(content)
        if not subjects:
            return
        ret.append(subjects)
        if pages > max_page:
            pages = max_page
            
        for i in range(2, pages+1):
            content = self.download(i)
            sp = BeautifulSoup(content)
            subjects = self.parse(sp)
            ret.extend(subjects)
        self.store(ret)
        
    def store(self, subjects):
        if not subjects:
            return
        self.db.execute('select url from %s' % (byr_tables["subject"]))
        
        sql = "insert into %s(sub_section_id, url, subject, publish_time, author,\
            reply_num, latest_reply_time, latest_reply_author, spider_time) values" % byr_tables["subject"]
        urls = self.db.fetchall()
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
                self.db.execute(sql)   
                self.db.commit()
            except Exception, e:
                print e
        self.db.close()