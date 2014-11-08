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
			self.user[i] = {}
			for item in range(len(arr)):
				try:
					self.user[i][item] = float(arr[item])
				except:
					print "****error in data process"
					exit()
			i += 1
	
	
	# normanized the similar algorithm: 
	# as the userCF data is data[user][item] = score
	# as the itemCF data is data[item][user] = score
	def normal_sim(self, data):
		sim = dict()
		for key1 in data:
			sim[key1] = dict()
			for key2 in data:
				if key1 == key2:
					continue
				if key2 in sim:
					sim[key1][key2] = sim[key2][key1]
				else:
					sim[key1][key2] = self.get_dict_score(data[key1], data[key2])
		return sim
	
	def normal_recommend(self, sim, target, top = 5):
		if target not in sim:
			return None
		ret = { }
		i = 0
		for sim_t, score in sorted(sim[target].items(), key=lambda x: x[1]):
			if i == top:
				break
			i += 1
			ret[sim_t] = score
		
		for sim_t, score in ret.items():
			print sim_t, score

	#dict sqrt
	def get_dict_score(self, dict1, dict2):
		ret = 0.0
		for key in dict1:
			if key not in dict2:
				continue
			ret += math.pow(dict1[key]-dict2[key], 2)
		return math.sqrt(ret)
	
	
	# array sqrt
	def get_score(self, arr1, arr2):
		ret = 0.0
		for i in range(len(arr1)):
			ret += math.pow(arr1[i] - arr2[i], 2)
		return math.sqrt(ret)

	# UserCF
	def simlar_user(self):
		self.userCF = {}
		
		self.userCF = self.normal_sim(self.user)
		for user1, item in self.userCF.items():
			for user2, score in item.items():
				print "%d,%d,%f" % (user1, user2, score)
		return self.userCF

	
	
	def get_sim_user(self, user, top = 5):
		return self.normal_recommend(self.userCF, user, top)

	def get_sim_item(self, item, top = 5):
		return self.normal_recommend(self.itemCF, item, top)
		
	# ItemCF
	def sim_item(self):
		self.itemCF = { }
		self.items = {}
		for user, item_score in self.user.items():
			for i in range(len(item_score)):
				if i not in self.items:
					self.items[i] = { }
				self.items[i][user] = item_score[i] 
				#item i was rating by user with item_score
				
		self.itemCF = self.normal_sim(self.items)

		for item1, item_score in self.itemCF.items():
			for item2, score in item_score.items():
				print "itemCF:",item1,item2,score
		
if __name__ == '__main__':
	filename = 'jester-data-1.txt'
	line = 100
	
	rating = Ratings(filename)
	rating.process_data(line)
	rating.simlar_user()
	for i in range(line):
		rating.get_sim_user(i)
	
	print "itemCF"
	rating.sim_item()
