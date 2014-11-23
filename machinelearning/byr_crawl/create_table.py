#!:/bin/python
#--*--encoding:utf-8--*--

# @author: deenw
# this file is create the database and the table

import sys
import MySQLdb
from log import Log

log = Log()
byr_tables = {
		"outline_section": "outline_section",
		"sub_section": "sub_section",
		"subject": "subject",
		"article": "article"
		}

def connect(db = "byr", host = 'localhost', port = 3306, user = 'root', passwd = '123456'):
	try:
		#print "connect"
		conn = MySQLdb.connect(host,  user, passwd, db, port)
		conn.set_character_set('utf8')
		return conn
	except:
		log.stderr("can not connection database %s" % db)
		return None

def create_tables(db_name = None, conn = None):
	
	if conn == None:
		conn = connect()
	
	if conn == None:
		return None
	try:
		print "in try"
		cur = conn.cursor()

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
		# create the article content
		# cur.execute("create table content(
	except Exception, e:
		print e
		print "err create table"
		return None
	finally:	
		conn.close()

if __name__ == '__main__':
	create_tables()