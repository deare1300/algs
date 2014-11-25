#!:/bin/python
#--*--encoding:utf-8--*--
'''
Created on 2014-11-25

@author: Administrator
'''
from rewrite.storage.abstract_storage import Storage
from rewrite.database.tables import byr_tables
import MySQLdb

class UserStorage(Storage):
    def __init__(self):
        super(UserStorage, self).__init__()
        
    def store(self, res):
        #Storage.storage(self, data)
        if not res:
            return None
        columns = ["id", "user_name","face_url", "gender", "qq", "level", "is_online",
                    "last_login_time", "last_login_ip", "is_register", "is_admin", "first_login_time",
                    "role", "status", "full_msg"]
        intcols =  ["login_count", "stay_count"]
        
        self.db.execute('select account from %s' % (byr_tables["user"]))
        users = self.db.fetchall()
        sql = "insert into %s(account, user_name, face_url, gender, qq, level, is_online,\
            last_login_time, last_login_ip, is_register, is_admin, first_login_time,\
            login_count, stay_count, role, status, full_msg) values" % (byr_tables["user"])
        values = ""
        #if "id" not in e:
            
        for e in res:
            if "id" not in e:
                continue
            if (e["id"],) in users:
                continue
            for c in columns:
                if c not in e:
                    e[c] = "null"
            for c in intcols:
                if c not in e:
                    e[c] = -1
                    
            for key, value in e.items():
                if type(value) == str or type(value) == unicode:
                    try:
                        e[key] = MySQLdb.escape_string(e[key])
                    except:
                        e[key] = "null"
            
            values += "('%s', '%s', '%s', '%s', '%s', '%s', '%s',\
                    '%s','%s','%s','%s','%s',\
                    %d,%d,'%s','%s','%s')," % (e["id"], e["user_name"],e["face_url"], e["gender"], e["qq"], e["level"], e["is_online"],
                                               e["last_login_time"], e["last_login_ip"], e["is_register"], e["is_admin"], e["first_login_time"],
                                               e["login_count"], e["stay_count"], e["role"], e["status"], e["full_msg"])
            
        values = values.rstrip(',');
        if not values:
            return 0
        sql += values 
        print sql
        self.db.execute(sql)
        self.db.commit()