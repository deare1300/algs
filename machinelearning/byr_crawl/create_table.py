#!:/bin/python
#--*--encoding:utf-8--*--

# @author: deenw
# this file is create the database and the table

import sys
import MYSQLdb
from log import Log

log = Log()

def connect(db = "byr", host = 'localhost',
		port = 3306, user = 'root', passwd = '123456')
	try:
		return MySQLdb.connect(
				host = host
				port = port,
				user = user,
				passwd = passwd,
				db = db
				)
	except:
		log.err("can not connection database %s" % db)
		return None

def create_table(tbl_name, db_name = None, conn = None):
	if conn = None:
		conn = connect(db_name)
	
	if conn = None:
		return None
	try:
		cur = conn.cursor()

		# create the parent forums
		cur.execute("create table if not exists p_forums(
			id int auto_increment,
			name varchar(255) unique, 
			url varchar(255) unique,
			primary key(id))"
			)
		
		# create the sub forum
		cur.execute("create table if not exists sub_forums(
			id int auto_increment, 
			p_id int,
			level int default 1,
			name varchar(255) unique,
			url varchar(255) unique,
			primary key(id))"
			#foreign key(p_id) references(p_forums)"
			)

		# create the article abstract
		cur.execute("create table if not exists article(
			id int auto_increment,
			sub_id int,
			url varchar(255),
			publish_time varchar(255),
			author varchar(255),
			reply_num int,
			modify_time varchar(255),
			modify_author varchar(255),
			primary key(id),
			foregin key(sub_id) references(sub_id))"
			)

		# create the article content
		# cur.execute("create table content(
			
			
		conn.close()
			
