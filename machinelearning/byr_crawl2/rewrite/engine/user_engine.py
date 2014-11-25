#!:/bin/python
# -*- coding:utf-8 -*-
'''
Created on 2014-11-24

@author: Administrator
'''
from rewrite.engine.abstract_engine import Engine
from rewrite.crawlers.user_crawler import UserCrawler
from rewrite.engine.filters import DefaultUserFilter
from rewrite.engine.filters import UserFilter
from rewrite.storage.user_storage import UserStorage

class UserEngine(Engine):
    def __init__(self, user = None, crawler = UserCrawler, filters = [DefaultUserFilter], 
                 headers = None, storage = UserStorage):
        super(UserEngine, self).__init__(user, filters = filters, crawler = crawler,
                                         storage = storage)
        self.headers = headers
    
    def work(self, commits = 100):
        users = self.get_target()
        res = []
        store = self.storage()
        for user in users:
            print "user",user
            c = self.crawler(user[0], path_url = "/user/query/", headers = self.headers)
            try:
                tmp = c.crawl()
            except Exception, e:
                print e
                continue
            if not tmp:
                continue
            res.extend(tmp)
            if len(res) >= commits:
                store.store(res)
                res = []
            
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
    storage = UserStorage
    engine = UserEngine(filters = [DefaultUserFilter], headers = headers, storage = storage)
    engine.work()
    