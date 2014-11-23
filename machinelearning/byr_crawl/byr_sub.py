#!:/bin/python
# -*- coding:utf-8 -*-


# this file is spider for the sub sections of bbs.byr.cn
'''
Created on 2014-11-21

@author: deenw
'''
from login import LoginBYR
from log import Log
import sys
import urllib2
import urllib
from bs4 import BeautifulSoup
from create_table import byr_tables,connect
import re

reload(sys)
sys.setdefaultencoding('utf8')

class SubSection:
    def __init__(self, outline_url, section_id = None, level = 1, user = "deare1300", parent_id = 0,
                 root_url = "http://bbs.byr.cn/"):
        print outline_url, level,"***********level"
        self.outline_url = outline_url
        self.log = Log()
        self.user = user
        headers = dict()
        headers["Connection"] = "keep-alive"
        headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
        headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
        headers["Accept-Encoding"] = "deflate"
        headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
        headers["X-Requested-With"] = "XMLHttpRequest"
        self.headers = headers
        self.section_id = section_id
        self.level = level
        self.parent_id = parent_id
        self.root_url = root_url
     
    def download(self):
        url = self.root_url + self.outline_url 
        #print "full url", url
        req = urllib2.Request(url, headers = self.headers)
        res = urllib2.urlopen(req)
        #print res.headers
        #print res.headers["content-type"]
        origin_text =res.read()
        utf8_text = origin_text.decode("mbcs").encode("UTF8")
        return utf8_text
    
    def __parse_element(self, soup):
        if not soup:
            return None
        #print soup
        a = soup.find('a', href = True)
        #print a
        if a:
            name = a.text
            link = a["href"]
            return (link, name)
        return None
    
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
        title1 = tr.find("td", attrs = {"class": "title_1 bg-odd"})
        title2 = tr.find("td", attrs = {"class": "title_2 bg-odd"})
        e["title"] = self.__parse_element(title1)
        return e
    
    def __parse_tr(self, tr):
        if tr.find("th"):
            return None
        e = self.normal_parse(tr)
        if e is None:
            e = self.dir_parse(tr)
            print "22222222222222222222222"
        print "tr------", tr, e
        return e
    
    def parse(self, content):
        ret = []
        soup = BeautifulSoup(content, from_encoding="utf8")
        table = soup.find("table", attrs={"class": "board-list corner"})
        #print "table",table
        if table == None:
            print "cannot find table"
            return
        trs = table.findAll("tr")
        for tr in trs:
            e = self.__parse_tr(tr)
            if e:
                ret.append(e)
        print ret
        return ret
    
    def crawl(self):
        content = self.download()
        ret = self.parse(content)
        self.store(ret)
        
    def crawl_next(self, url, parent_id):
        next_sub = SubSection(url, section_id = self.section_id, 
                              level= self.level+1, parent_id = parent_id)
        next_sub.crawl()
        
    def store(self, info, update = False):
        conn = connect()
        cur = conn.cursor()
        cur.execute("set names utf8;")
        cur.execute('SET CHARACTER SET utf8;')
        cur.execute('SET character_set_connection=utf8;')
        cur.execute("select url from %s" % byr_tables["sub_section"])
        urls = cur.fetchall()
        print urls
        values = ""
        if not update:
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
                        cur.execute(sql)
                        conn.commit()
                        insert_id = cur.lastrowid
                        self.crawl_next(self.outline_url, parent_id = insert_id)
                    except Exception, e:
                        print e
                        
                    
                else:
                    if e["chairman"] == None:
                        e["chairman"] = ("null", "null")
                    #print byr_tables["sub_section"], url, name, self.level, self.section, self.parent_id, e["chairman"][1], e["online_num"], e["subject_num"],e["article_num"]
                    sql = "insert into %s(url, name, level, outline_id, parent_id, author, online_num, total_subject ,total_article) values('%s', '%s', %s,      %s,        %s,     '%s', %s, %s, %s);" % (byr_tables["sub_section"], url, name, self.level, self.section_id, self.parent_id, e["chairman"][1], e["online_num"], e["subject_num"],e["article_num"])
                    #print sql
                    try:
                        cur.execute(sql)
                    except Exception, e:
                        print e
        else:
            print "not supported"
        conn.commit()
        conn.close()
        return 
             
class CrawlSub:
    def __init__(self, url, user = "deare1300"):
        self.url = url
        self.user = user
    
    def getUrls(self):
        conn = connect()
        cur = conn.cursor()
        cur.execute("select id, url from %s" % byr_tables["outline_section"])
        id_urls = cur.fetchall()
        return id_urls
    
    def login(self):
        self.sign = LoginBYR(user = self.user)
        islogged = self.sign.login()
        print self.sign.cj
        return islogged
    
    def crawl(self):
        if self.login() == False:
            print "logged in subsection failed**"
            sys.exit()
        id_urls = self.getUrls()
        for (id, url) in id_urls:
            print url
            sub = SubSection(url, section_id = id, root_url = self.url)
            sub.crawl()
        
if __name__ == '__main__':
    sub = CrawlSub("http://bbs.byr.cn/")
    sub.crawl()