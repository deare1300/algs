#!:/bin/python
# -*- coding:utf-8 -*-
'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.database.db import DB
import MySQLdb

class Storage(object):
    def __init__(self):
        self.db = DB()
    
    def pre_statement(self, res):
        for key, value in res.items():
            if type(value) == str or type(value) == unicode:
                try:
                    res[key] = MySQLdb.escape_string(res[key])
                except:
                    res[key] = "null"
        return res
    
    def storage(self, data):
        raise("you must complete the storage()")
    
    def complete(self):
        self.db.close()