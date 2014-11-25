#!:/bin/python
# -*- coding:utf-8 -*-
'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.engine.abstract_engine import Engine
from rewrite.crawlers.profile_crawler import ProfileCrawler
from rewrite.storage.profile_storage import ProfileStorage

class ProfileEngine(Engine):
    def __init__(self, crawler = ProfileCrawler, filters = [None], 
                 headers = None, storage = ProfileStorage):
        super(ProfileEngine, self).__init__(filters = filters, crawler = crawler,
                                         storage = storage)
        self.headers = headers
    
    def work(self, commits = 100):
        #sections = self.get_target()
        res = []
        store = self.storage()
        c = self.crawler(headers = self.headers, root_url = "http://bbs.byr.cn/section/ajax_list.json")    
        res.extend(c.crawl())    
        print res
        if res:
            store.store(res)   
        store.complete()
    
if __name__ == "__main__":
    headers = dict()
    headers["Connection"] = "keep-alive"
    headers["Accept"] = "application/json,text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8,q=0.01"
    headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
    headers["Accept-Encoding"] = "deflate"
    headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
    headers["X-Requested-With"] = "XMLHttpRequest"
    engine = ProfileEngine(headers = headers)
    engine.work()