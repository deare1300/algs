'''
Created on 2014-11-21

@author: Administrator
'''
import urllib2
import cookielib
import urllib
from log import Log

class LoginBYR:
    def __init__(self, url = "http://bbs.byr.cn/#!default", 
                 login_url = "http://bbs.byr.cn/user/ajax_login.json", 
                 user = "deare1300", 
                 passwd = "temp110"):
        self.url = url
        self.log = Log()
        self.user = user
        self.passwd = passwd
        self.save_date = "2"
        headers = dict()
        headers["Connection"] = "keep-alive"
        headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
        headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
        headers["Accept-Encoding"] = "deflate"
        headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
        headers["X-Requested-With"] = "XMLHttpRequest"
        
        self.headers = headers
        self.login_url = login_url
    
    def login(self):
        cj = cookielib.LWPCookieJar()
        cookie_support = urllib2.HTTPCookieProcessor(cj)
        opener = urllib2.build_opener(cookie_support)
        urllib2.install_opener(opener)
        self.cj = cj
        
        postDict = {
                "id": self.user,
                "passwd": self.passwd,
                "CookieDate": self.save_date
                }            
        postData = urllib.urlencode(postDict)
        request = urllib2.Request(self.login_url, postData, self.headers)
        response = urllib2.urlopen(request)
        login_json = response.read()
        
        if "id" in login_json:
            return True
        else:
            return False