'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.storage.abstract_storage import Storage
from rewrite.database.tables import byr_tables

class SectionStorage(Storage):
    def __init__(self):
        super(SectionStorage, self).__init__()
    def store(self, info, update = False):
        self.db.execute("select url from %s" % byr_tables["sub_section"])
        urls = self.db.fetchall()
        print urls
        if not update:
            for e in info:
                if not e or e["title"] == None:
                    continue
                url = e["title"][0]
                name = e["title"][1]
                #print re.match("^\s*$", e["online_num"]), e["online_num"]
                if (url,) in urls:
                    continue
                
                
                if e["latest_subject"] == None and e["chairman"] == None:
                    e = self.pre_statement(e)
                    print "============================================next level",e
                    sql = "insert into %s(url, name, level, outline_id, parent_id) values('%s', '%s', %s, %s, %s)" % (byr_tables["sub_section"], url, name, self.level, self.section_id, self.parent_id)
                    #print sql
                    try:
                        self.db.execute(sql)
                        self.db.commit()
                        insert_id = self.db.lastrowid
                        self.crawl_next(url, parent_id = insert_id)
                    except Exception, e:
                        print e           
                else:
                    e = self.pre_statement(e)
                    if e["chairman"] == None:
                        e["chairman"] = ("null", "null")
                    #print byr_tables["sub_section"], url, name, self.level, self.section, self.parent_id, e["chairman"][1], e["online_num"], e["subject_num"],e["article_num"]
                    sql = "insert into %s(url, name, level, outline_id, parent_id, author, online_num, total_subject ,total_article) values('%s', '%s', %s,      %s,        %s,     '%s', %s, %s, %s);" % (byr_tables["sub_section"], url, name, self.level, self.section_id, self.parent_id, e["chairman"][1], e["online_num"], e["subject_num"],e["article_num"])
                    try:
                        self.db.execute(sql)
                    except Exception, e:
                        print e
        else:
            print "not supported"
        self.db.commit()
        self.db.close()
        return