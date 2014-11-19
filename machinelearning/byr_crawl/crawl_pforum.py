#!:/bin/python
#--*--encoding:utf-8--*--

# author deenw

# 爬论坛大分区
import urllib2
import sys
import os
from BeautifulSoup import BeautifulSoup
from create_table import connect

class ParentForum:
	def __init__(self, url = "http://bbs.byr.cn"):
		self.url = url
	
	def download(self):
		req = urllib2.Request(self.url)
		response = urllib2.urlopen(req)
		return response
	
	def parse(self, content):
		soup = BeautifulSoup(content)
		xlist = soup.findAll('div', {'id':'xlist'})
		if len(xlist) == 0:
			return None
		slist = xlist[0].findAll('li', {'class': 'slist folder-open'})
		if len(slist) == 0:
			return None
		x_child = slist[0].findAll('ul', {'class': 'x-child'})
		if len(x_child) == 0:
			return None
		p_form = x_child[0].findAll('ul', {'class':'folder-close'})

		p_res = [ ]
		for p in p_form:
			text = p.findAll('span', {'class':'text'})
			if len(text) == 0:
				continue
			a = text.findAll('a', href = True)
			if len(a) == 0:
				continue
			p_res.append((a. text,a['href']))
		
		return p_res
	
	def craw(self):
		response = self.download()
		content = response.read()
		p_info = self.parse(content)
		self.store_info(p_info)

	def store_info(self, p_info)
		conn = connect()
		values = ""
		for name, url in p_info:
			value = "(%s, %s)," % (name, url)
		values.strip(',')
		conn.execute("insert into %s(name, url) values %s" %("p_forum", values)
		conn.close()
