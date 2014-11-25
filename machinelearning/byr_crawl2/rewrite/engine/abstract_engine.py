'''
Created on 2014-11-23

@author: Administrator
'''
import cookielib
import urllib2
import urllib
from rewrite.log.log import Log 
from rewrite.user.User import get_default_login

#Abstract engine must complete the work 
class Engine(object):
    def __init__(self, user = None, filters = None, crawler = None, storage = None):
        self.user = user
        self.filters = filters
        self.storage = storage
        self.crawler = crawler
        
    def start(self, need_login = True, login_flag = "id",
             crawler_args = {}, filter_args = {}):
        if need_login:
            if self.user and not self.user.login(login_flag):
                self.log.stderr("login failed with user:", self.user)
            else: 
                self.user = get_default_login()
                if not self.user:
                    self.log.stderr("login failed with default user:")
                    return False 
        return True       
    
    def get_target(self):
        #raise("You must complete get_target")
        targets = []
        if self.filters:
            for f in self.filters:
                tmp = f().filter()
                if tmp:
                    targets.extend(tmp)
        return targets
    
    def work(self, commits = 1):
        raise("You must complete work engine")
    
    def end(self):
        if self.user:
            return self.user.logout()
        return True   