#!:/bin/python
# -*- coding:utf-8 -*-
'''
Created on 2014-11-25

@author: Administrator
'''
'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.engine.abstract_engine import Engine
from rewrite.crawlers.article_crawler import ArticleCrawler
from rewrite.engine.filters import ArticleFilter
from rewrite.storage.article_storage import ArticleStorage

class ArticleEngine(Engine):
    def __init__(self, crawler = ArticleCrawler, filters = [ArticleFilter], 
                 headers = None, storage = ArticleStorage,
                 section_id = None):
        super(ArticleEngine, self).__init__(filters = filters, crawler = crawler,
                                         storage = storage)
        self.headers = headers
        self.section_id = section_id
    
    def work(self, commits = 100):
        subjects = self.get_target()
        res = []
        store = self.storage()
        for s in subjects:
            print "subjects", s
            c = self.crawler(subject_id = s[0], path_url = s[1], headers = self.headers)
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
    engine = ArticleEngine(headers = headers)
    engine.work()