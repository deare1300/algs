#!:/bin/python
# -*- coding:utf-8 -*-

# author deenw

# this file is spider for the profile sections of bbs.byr.cn
import urllib2
import sys
import os
from bs4 import * 
from create_table import connect
import cookielib
import urllib
from log import Log
from create_table import byr_tables
import json
from login import LoginBYR

reload(sys)
sys.setdefaultencoding('utf8')

class BYRForum:
	def __init__(self, 
				url = "http://bbs.byr.cn/#!default",
				login_url = "http://bbs.byr.cn/user/ajax_login.json", 
				user = "deare1300",
				passwd = "temp110"):
		self.url = url
		self.log = Log()
		self.user = user
		self.passwd = passwd
		self.save_date = "2"
		headers = dict()
		headers["Connection"] = "keep-alive"
		headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
		headers["User-Agent"] = "Mozilla/5.0 (Windows NT 6.1; rv:32.0) Gecko/20100101 Firefox/32.0"
		headers["Accept-Encoding"] = "deflate"
		headers["Accept-Language"] = "zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3"
		headers["X-Requested-With"] = "XMLHttpRequest"
		
		self.headers = headers
		self.login_url = login_url
		self.profile_url = "http://bbs.byr.cn/section/ajax_list.json"
	
	def download_profile(self):
		url = self.profile_url + "?uid="+self.user+"&root=list-section"
		req = urllib2.Request(url, 
							headers = self.headers)
		res = urllib2.urlopen(req)
		origin_text =res.read()
		utf8_text = origin_text.decode("gbk").encode("utf8")
		return utf8_text
	
	def parse_profile(self, json_content):
		ret = dict()
		profiles = json.loads(json_content)
		for p in profiles:
			if "t" not in p:
				continue
			soup = BeautifulSoup(p["t"], from_encoding="utf8")
			a = soup.find('a', href = True)
			if a:
				ret[a['href']] = a.text
		print ret
		return ret
			
	def login(self):
		self.sign = LoginBYR(login_url = self.login_url)
		islogged = self.sign.login()
		print self.sign.cj
		return islogged 
	
	def craw_profile(self):
		isLogged = self.login()
		if isLogged == False:
			self.log("Error *** log failed***")
			print "Login failed --"
			sys.exit()
		
		print "login success!"
		json_profiles = self.download_profile()
		parsed_profiles = self.parse_profile(json_profiles)
		#content = self.download()
		#print content.decode("gbk").encode("utf8")
		#p_info = self.parse(content)
		
		if parsed_profiles:
			self.store_info(parsed_profiles)

	def store_info(self, p_info):
		conn = connect()
		conn.set_character_set('utf8')
		cur = conn.cursor()
		cur.execute("set names utf8;")
		cur.execute('SET CHARACTER SET utf8;')
		cur.execute('SET character_set_connection=utf8;')
		
		cur.execute('select url from %s' % (byr_tables["outline_section"]))
		stored_urls = cur.fetchall()
		print stored_urls
		values = ""
		for url, name in p_info.items():
			if	(url,) not in stored_urls:
				#print "new url", url
				values += "('%s', '%s')," % (name, url)
		values = values.rstrip(',')
		if values:
			sql = "insert into %s(name, url) values %s;" % (byr_tables["outline_section"], values)
			print sql
			nrows = cur.execute(sql)
			if nrows != len(p_info):
				self.log.log_err("insert not complete:inserted % rows in origin % rows"
							% (nrows, len(p_info)))
			else:
				print "success inserted"
		conn.commit()
		conn.close()

def cookie(cj):
	for index, cookie in enumerate(cj):
		print '[',index,']',cookie
		
if __name__ == "__main__":
	pf = BYRForum()
	#pf.login()
	pf.craw_profile()

