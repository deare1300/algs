'''
Created on 2014-11-23

@author: Administrator
'''

import urllib2
default_url = "http://bbs.byr.cn/"

def encode_args(d):
    value = ""
    for k, v in d:
        value += '&' + k + "=" +v
    value = value.lstrip('&')
    return value 

class Crawler(object):
    def __init__(self, path_url = '/',
                 root_url = default_url, headers = None, parse_code = "utf8"):
        self.path_url = path_url
        self.root_url = root_url
        self.headers = headers
        self.parse_code = parse_code
    
    def process_url(self):
        url = self.root_url + self.path_url.replace("//", '/')
        return url
    
    def download(self, args = {}, code = "gbk", timeout = 2):
        url =  self.process_url()
        #print "download url", url
        if self.headers:
            req = urllib2.Request(url, headers = self.headers)
        else:
            req = urllib2.Request(url)
        try:
            res = urllib2.urlopen(req, timeout = timeout)
        except Exception, e:
            print "dowlonad or expetion timeout", e
            return None
        origin_text =res.read()
        decoded_text = origin_text.decode(code).encode(self.parse_code)
        return decoded_text
    
    def parse(self, content):
        raise("you must complete parse() in your sub crawl")
    
    def crawl(self, download_args = {}, download_code = "gbk"):
        utf8_html = self.download(download_args, download_code)
        if not utf8_html:
            return None
        result = self.parse(utf8_html)
        return result
        
