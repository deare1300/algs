#!:/bin/python
# -*- coding:utf-8 -*-
'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.storage.abstract_storage import Storage
from rewrite.database.tables import byr_tables
import time

class SubjectStorage(Storage):
    def __init__(self):
        super(SubjectStorage, self).__init__()
        self.spider_time = time.strftime("%H-%m-%d %X", time.localtime())
        
    def store(self, subjects, section_id):
        if not subjects:
            return
        self.db.execute('select url from %s' % (byr_tables["subject"]))
        
        sql = "insert into %s(sub_section_id, url, subject, publish_time, author,\
            reply_num, latest_reply_time, latest_reply_author, spider_time) values" % byr_tables["subject"]
        urls = self.db.fetchall()
        #print subjects
        values = ""
        for s in subjects:
            if (s["url"],) not in urls:
                s = self.pre_statement(s)
                values += "(%d, '%s', '%s', '%s', '%s', \
                    %d, '%s', '%s', '%s')," % (section_id, s["url"], s["subject"], s["publish_time"], s["author"],
                                              int(s["reply_num"]), s["latest_reply_time"], s["latest_author"], self.spider_time)
        values = values.strip(',')
        if not values:
            print "not insert"
        else:    
            sql += values
            #print sql
            try:
                self.db.execute(sql)   
                self.db.commit()
            except Exception, e:
                print e
        self.db.close()