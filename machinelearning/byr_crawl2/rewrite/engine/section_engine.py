'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.engine.abstract_engine import Engine
from rewrite.crawlers.section_crawler import SectionCrawler
from rewrite.engine.filters import SectionFilter
from rewrite.storage.section_storage import SectionStorage

class SectionEngine(Engine):
    def __init__(self, crawler = SectionCrawler, filters = [SectionFilter], 
                 headers = None, storage = SectionStorage,
                 ):
        super(SectionEngine, self).__init__(filters = filters, crawler = crawler,
                                         storage = storage)
        self.headers = headers
    
    def work(self, commits = 1):
        self.crawler(path_url = "/section/ajax_list.json", headers = self.headers)
        sections = self.get_target()
        for s in sections:
            c = self.crawler(profile_id = s[0], path_url = s[1])
            c.crawl()

if __name__ == "__main__":
    headers = dict()
    headers["Connection"] = "keep-alive"
    headers["Accept"] = "application/json,text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8,q=0.01"
    headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
    headers["Accept-Encoding"] = "deflate"
    headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
    headers["X-Requested-With"] = "XMLHttpRequest"
    engine = SectionEngine(headers = headers)
    engine.work()