#!:/bin/python
# -*- coding:utf-8 -*-
'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.engine.abstract_engine import Engine
from rewrite.crawlers.subject_crawler import SubjectCrawler
from rewrite.engine.filters import SubjectFilter
from rewrite.storage.subject_storage import SubjectStorage

class SubjectEngine(Engine):
    def __init__(self, user = None, crawler = SubjectCrawler, filters = [SubjectFilter], 
                 headers = None, storage = SubjectStorage,
                 ):
        super(SubjectEngine, self).__init__(user, filters = filters, crawler = crawler,
                                         storage = storage)
        self.headers = headers
    
    def work(self, commits = 100):
        subjects = self.get_target()
        res = []
        store = self.storage()
        for s in subjects:
            print "subjects", s
            c = self.crawler(section_id = s[0], path_url = s[1], headers = self.headers)
            #try:
            res = c.crawl()
            # except Exception, e:
            #     print e
            #    continue
            if not res:
                continue
            store.store(res, section_id = s[0])
            print "subject over********************************"
        
        store.complete()
        
if __name__ == "__main__":
    headers = dict()
    headers["Connection"] = "keep-alive"
    headers["Accept"] = "application/json,text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8,q=0.01"
    headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
    headers["Accept-Encoding"] = "deflate"
    headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
    headers["X-Requested-With"] = "XMLHttpRequest"
    engine = SubjectEngine(headers = headers)
    engine.work()