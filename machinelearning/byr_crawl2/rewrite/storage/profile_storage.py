#!:/bin/python
# -*- coding:utf-8 -*-
'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.storage.abstract_storage import Storage
from rewrite.database.tables import byr_tables


class ProfileStorage(Storage):
    def __init__(self):
        super(ProfileStorage, self).__init__()
        
    def store(self, p_infos):
        if not p_infos:
            return 
        self.db.execute('select url from %s' % (byr_tables["outline_section"]))
        stored_urls = self.db.fetchall()
        #print stored_urls
        values = ""
        p_info = p_infos[0]
        self.pre_statement(p_info)
        for url, name in p_info.items():
            if    (url,) not in stored_urls:
                #print "new url", url
                values += "('%s', '%s')," % (name, url)
        values = values.rstrip(',')
        if values:
            sql = "insert into %s(name, url) values %s;" % (byr_tables["outline_section"], values)
            print sql
            nrows = self.db.execute(sql)
            if nrows != len(p_info):
                self.log.log_err("insert not complete:inserted % rows in origin % rows"
                            % (nrows, len(p_info)))
            else:
                print "success inserted"
        self.db.commit()