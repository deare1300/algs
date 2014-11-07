#!/bin/python
#--*coding:utf-8*--

import math
from sys import exit

class Ratings:
	def __init__(self, filename):
		self.filename = filename
	
	def process_data(self, max_line = 1000000):
		self.user = {}
		i = 0
		for line in file(self.filename):
			if i == max_line:
				break
			arr = line.strip().split('\t')
			self.user[i] = []
			for score in arr:
				try:
					self.user[i].append(float(score.strip()))
				except:
					print "****error in data process"
					exit()
			i += 1
	
	def get_score(self, arr1, arr2):
		ret = 0.0
		for i in range(len(arr1)):
			ret += math.pow(arr1[i] - arr2[i], 2)
		return math.sqrt(ret)

	def simlar_user(self):
		self.simlar = {}
		for user1 in self.user:
			if user1 not in self.simlar:
				self.simlar[user1] = {}
			for user2 in self.user:
				if user1 == user2:
					continue
				if user2 in self.simlar:
					self.simlar[user1][user2] = self.simlar[user2][user1]
				else:
					self.simlar[user1][user2] = self.get_score(self.user[user1],self.user[user2])
		
		for user1, item in self.simlar.items():
			for user2, score in item.items():
				print "%d,%d,%f" % (user1, user2, score)
	
	def get_sim_user(self, user, top = 5):
		if user not in self.simlar:
			return None

		ret = { }
		i = 0
		for key, value in sorted(self.simlar[user].items(), key = lambda x: x[1]):
			if i == 5:
				break
			ret[key] = value
			i += 1
		print "user %d->" % user,
		for user in ret:
			print user,
		print 
		return ret


	def sim_item(self):
		none
	
	def get_sim_item(self, item, top = 5):
		none
		
if __name__ == '__main__':
	filename = 'jester-data-1.txt'
	line = 100
	
	rating = Ratings(filename)
	rating.process_data(line)
	rating.simlar_user()
	for i in range(line):
		rating.get_sim_user(i)
	
