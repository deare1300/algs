'''
Created on 2014-11-23

@author: Administrator
'''

from rewrite.database.db import DB
from rewrite.database.tables import byr_tables
class Filter:
    def __init__(self):
        pass
    
    def filter(self):
        pass


class DefaultUserFilter(Filter):
    def __init__(self, tb_name = byr_tables["article"]):
        self.tb_name = tb_name
        
    def filter(self):
        db = DB()
        db.execute("select distinct answer_user from %s" % (self.tb_name))
        users = db.fetchall()
        db.close()
        return users
    
class UserFilter(Filter):
    def __init__(self, tb_name = byr_tables["article"]):
        self.tb_name = tb_name
    
    def filter(self):
        db = DB()
        #print "select distinct answer_user from %s as au where not exists(select id from %s as ub where au.answer_user = ub.user_name);" % (self.tb_name, byr_tables["user"])
        db.execute("select distinct answer_user from %s as au where not exists(select id from %s as ub where au.answer_user = ub.user_name);" % (self.tb_name, byr_tables["user"]))
        users = db.fetchall()
        db.close()
        return users
    
    
class SubjectFilter(Filter):
    def __init__(self, tb_name = byr_tables["sub_section"]):
        self.tb_name = tb_name
    
    def filter(self):
        filtered_section = []
        db = DB()
        db.execute('select id, url from %s' % (self.tb_name)) 
        section_info = db.fetchall()
        db.execute('select distinct sub_section_id from %s;' % byr_tables["subject"])
        sections = db.fetchall()
        for sid, url in section_info:
            if (sid,) not in sections:
                filtered_section.append((sid, url))
        return filtered_section
    
class SectionFilter(Filter):
    def __init__(self, tb_name = byr_tables["outline_section"]):
        self.tb_name = tb_name
        
    def filter(self):
        db = DB()
        db.execute("select id, url from %s" % self.tb_name)
        id_urls = db.fetchall()
        return id_urls
    
class ProfileFilter(Filter):
    def __init__(self, tb_name = byr_tables["outline_section"]):
        raise("no need filter in profileFilter")
        self.tb_name = tb_name
        
    def filter(self):
        raise("no need filter in profileFilter")
    
    
class ArticleFilter(Filter):
    def filter(self):
        db = DB()
        db.execute("select id, url from subject where not exists\
                    (select subject_id from article where subject_id = subject.id)")
        articles = db.fetchall()
        db.close()
        return articles
        