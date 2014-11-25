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
from rewrite.database.db import DB

byr_tables = {
        "outline_section": "outline_section",
        "sub_section": "sub_section",
        "subject": "subject",
        "article": "article",
        "user": "byr"
        }
   
class InitTables:
    def __init__(self):
        self.db = DB()
        
    def create_tables(self):
        cur = self.db
        # create the outLine section
        cur.execute("create table if not exists %s( \
            id int auto_increment,\
            name varchar(255) unique not null,\
            url varchar(255) unique not null,\
            primary key(id))" % (byr_tables["outline_section"])
            )
        
    
        # create the sub section 
        cur.execute("create table if not exists %s(\
            id int auto_increment,\
            outline_id int not null,\
            level int default 1,\
            parent_id int default null,\
            name varchar(255) unique not null,\
            english_name varchar(255),\
            url varchar(255) unique not null,\
            latest_subject varchar(255), \
            author varchar(255),\
            online_num int, \
            total_subject int,\
            total_article int,\
            primary key(id),\
            foreign key(outline_id) references %s(id) \
            )" % (byr_tables["sub_section"], byr_tables["outline_section"])
            #foreign key(parent_id) references %s(id)
            )

        
        # create the article abstract
        cur.execute("create table if not exists %s(\
            id int auto_increment,\
            sub_section_id int,\
            url varchar(255) not null unique,\
            subject varchar(255) not null,\
            publish_time varchar(255) not null,\
            author varchar(255) not null,\
            reply_num int not null,\
            latest_reply_time varchar(255),\
            latest_reply_author varchar(255),\
            spider_time varchar(255),\
            is_spider int default 0,\
            primary key(id),\
            foreign key(sub_section_id) references %s(id))" % (byr_tables["subject"],byr_tables["sub_section"])
            )
        
        cur.execute("create table if not exists %s(\
            id int auto_increment,\
            subject varchar(255),\
            subject_id int not null,\
            answer_pos int not null,\
            answer_user varchar(255) not null,\
            answer_content varchar(20000) not null,\
            answer_time varchar(255) not null,\
            answer_ip varchar(255),\
            answer_source varchar(255),\
            unique(subject_id, answer_pos),\
            primary key(id)\
            )" % (byr_tables["article"])
            )
        
        cur.execute("create table if not exists %s(\
            id int auto_increment,\
            account varchar(255) not null unique,\
            user_name varchar(255) not null,\
            face_url varchar(255),\
            gender varchar(10),\
            qq varchar(255),\
            level varchar(10),\
            is_online varchar(10),\
            last_login_time varchar(255),\
            last_login_ip varchar(255),\
            is_register varchar(10),\
            is_admin varchar(10),\
            first_login_time varchar(255),\
            login_count int,\
            stay_count int,\
            role varchar(255),\
            status varchar(255),\
            full_msg varchar(2000),\
            primary key(id)\
            )" % (byr_tables["user"])
            );
            
        
if __name__ == "__main__":
    it = InitTables()
    it.create_tables()