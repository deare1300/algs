#!:/bin/python
#-**-coding:utf-8-**-

import sys
import os
import math

class DecisionTree:
	# data is the arr [{"atr1":"some", "atr2":"some"},]
	# key is the attribution of an element of data, such as "atr1"
	def __init__(self, data, key, other_keys, tab = ''):
		self.data = data
		self.key = key
		self.other_keys = other_keys
		self.tab = tab
	
	def cal_entropy(self, data):
		len_data = len(data)
		key_res = dict()
		entropy = 0.0
		for d in self.data:
			value = d[self.key]
			if value not in key_res:
				key_res[value] = 1
			else:
				key_res[value] += 1
			
		for value in key_res.values():
			p = value*1.0/len_data
			entropy += p*math.log(1.0/p)
		return entropy

	def divide_data(self, div_attr):
		divide_res = { }
		for d in self.data:
			value = d[div_attr]
			if value not in divide_res:
				divide_res[value] = [d]
			else:
				divide_res[value].append(d)
		return divide_res

	def get_attributes(self):
		attrs = []
		if len(self.data) == 0:
			return attrs
		for a in data[0]:
			attrs.append(a)
		return attrs

	def decide(self):
		self.entropy = self.cal_entropy(self.data)
		self.attrs = self.get_attributes()
		
		decided_tree = { }
		if self.attrs == self.other_keys:
			return None
		div_res = { }
		div_attr = None
		div_gain = 0.0
		for a in self.attrs:
			if a in self.other_keys:
				continue
			temp_div_res = self.divide_data(a)
			temp_entropy = 0.0
			for t in temp_div_res.values():
				temp_entropy += len(t)*1.0/len(self.data)*self.cal_entropy(t)
			if self.entropy - temp_entropy > div_gain:
				div_res = temp_div_res
				div_attr = a
				div_gain = self.entropy-temp_entropy
		if div_gain == 0.0:
			print "%s the final decision is %s" % (self.tab, self.data[0][key])
			return self.data[0][key]
		
		print "%sdivided by %s, and gain_entropy = %f" % (self.tab, div_attr,div_gain)
		decided_tree[div_attr] = { }
		for attrs,div in div_res.items():
			print "%s%s = %s" % (self.tab, div_attr, attrs)
			temp_keys = self.other_keys[:]
			temp_keys.append(div_attr)
			decision = DecisionTree(div, self.key, temp_keys, tab =
			self.tab+'\t')
			decided_tree[div_attr][attrs] = decision.decide()
		self.decided_tree = decided_tree
		return decided_tree	
	
	def judge(self, d):
		return self.__judge(d, self.decided_tree)
	
	def __judge(self, d, tree):
		if not type(tree) is dict:
			return tree
		keys = tree.keys()
		if len(keys) == 0:
			return "the reason not in predict"
		if keys[0] not in d or d[keys[0]] not in tree[keys[0]]:
			return "the reason first happend"
		return self.__judge(d, tree[keys[0]][d[keys[0]]])

if __name__ == '__main__':
	data = []
	attrs = []

	filename = "sample_input"
	f_input = open(filename)
	attr_line = f_input.readline()
	for a in attr_line.strip().split():
		attrs.append(a)
	key = attrs[len(attrs)-1]	
	for line in f_input:
		d = line.strip().split()
		data.append(dict(zip(attrs, d)))
	d_tree = DecisionTree(data, key, [key])
	print d_tree.decide()
	for d in data:
		print d_tree.judge(d), d[key]
