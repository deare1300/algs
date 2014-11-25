#!:/bin/python
#--*--encoding:utf-8--*--

# @author: deenw
# this file is create the database and the table

import sys
import MySQLdb
from log import Log
'''
Created on 2014-11-23

@author: Administrator
'''

class DB:
    def __init__(self, db = "byr", host = 'localhost', port = 3306, user = 'root', 
                 passwd = '123456', db_char_set = "utf8", table_char_set = "utf8"):
        self.db = db
        self.host = host
        self.port = port
        self.user = user
        self.passwd = passwd
        self.db_char_set = db_char_set
        self.table_char_set = table_char_set
        self.conn = MySQLdb.connect(host, user, passwd, db, port)
        self.init_conn()
        self.cur =  self.conn.cursor()
        self.init_cursor()
             
    def init_conn(self):
        self.conn.set_character_set(self.db_char_set)
        
    def init_cursor(self):
        self.cur.execute("set names %s;", self.table_char_set)
        self.cur.execute('SET CHARACTER SET %s;', self.table_char_set)
        self.cur.execute('SET character_set_connection= %s;', self.table_char_set)
        
    def close(self):
        return self.conn.close()
    
    def commit(self):
        self.conn.commit()
        
    def execute(self, sql):
        try:
            return self.cur.execute(sql)
        except Exception, e:
            print e
            return None
    
    def fetchall(self):
        return self.cur.fetchall()
    
    def lastrowid(self):
        return self.cur.lastrowid