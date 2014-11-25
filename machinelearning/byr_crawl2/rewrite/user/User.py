'''
Created on 2014-11-24

@author: Administrator
'''
import cookielib
import urllib2
import urllib

class UserLogin:
    def __init__(self, url, headers, post_data):
        self.url = url
        self.headers = headers
        self.post_data = post_data

    def login(self, success_key = "id"):
        cj = cookielib.LWPCookieJar()
        cookie_support = urllib2.HTTPCookieProcessor(cj)
        opener = urllib2.build_opener(cookie_support)
        urllib2.install_opener(opener)
        self.cj = cj
        post_data = urllib.urlencode(self.post_data)
        request = urllib2.Request(self.url, post_data, self.headers)
        response = urllib2.urlopen(request)
        login_json = response.read()
        print login_json
        if success_key in login_json:
            return True
        else:
            return False
        
    def logout(self):
        return True
        
def get_default_login():
    headers = dict()
    headers["Connection"] = "keep-alive"
    headers["Accept"] = "application/json,text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8,q=0.01"
    headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
    headers["Accept-Encoding"] = "deflate"
    headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
    headers["X-Requested-With"] = "XMLHttpRequest"
    login_url = 'http://bbs.byr.cn/user/ajax_login.json'
    user_account = {
                "id": "deare1300",
                "passwd": "temp110"
                }
    user = UserLogin(url = login_url, headers = headers, post_data = user_account)
    if user.login("id"):
        return user
    else:
        return None
    
if __name__ == "__main__":
    print get_default_login()
