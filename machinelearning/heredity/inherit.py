#!:/bin/python
#coding:utf-8

import os
import sys
import random
import math

class Inherit:
	# init set the bits of every number
	def __init__(self, bits, func):
		self.bits = bits
		self.func = func
	
	def create_sample(self):
		strs = ""
		for i in range(self.bits):
			if random.randint(0, 1) == 0:
				strs += "0"
			else:
				strs += "1"
		return strs
	
	# set and get the sample 
	def sample(self, M):
		self.M = M
		
	def mutation(self, s):
		i = random.randint(0, len(s)-1)
		if s[i] == '0':
			s = s[:i] + '1' + s[i+1:]
		else:
			s = s[:i] + '0' + s[i+1:]
		return s
	
	def cross_over(self, s1, s2):
		len_s = len(s1)
		i = random.randint(0, len_s-1)
		temp_s1 = s1[0:i+1]+s2[i+1:]
		temp_s2 = s2[0:i+1]+s1[i+1:]
		return (temp_s1, temp_s2)
	
	def cal(self, func, data):
		pselect = []
		for d in data:
			pselect.append(func(d))
		return pselect

	def personal_rate(self, pselect):
		rates = []
		sums = sum(pselect)
		for e in pselect:
			rates.append(e/sums)
		return rates	
	
	def add_rate(self, p_rate):
		rates = [] 
		rates.append(p_rate[0])
		for i in range(1, len(p_rate)):
			rates.append(rates[i-1] + p_rate[i])
		return rates
	
	def select(self, add_rate, p):
		for i in range(len(add_rate)):
			if add_rate[i] >= p:
				return i

	def must_res(self, data):
		max_index = 0
		max_res = self.func(data[0])
		for i in range(1, len(data)):
			m =self.func(data[i])
			if m > max_res:
				max_res = m
				max_index = i
		return data[max_index], max_res
		
	def run(self, M, mute = 0.05, cross = 0.75, step = 20):
		sample_data = []
		#self.sample(M)
		self.M = M
		for i in range(M):
			sample_data.append(self.create_sample())
		#print "the step is %d" % step
		for i in range(step):
			# mutation
			if random.random() < 0.05:
				for i in range(M):
					sample_data[i] = self.mutation(sample_data[i])
			# cross_over
			else:
				i = 0
				while i < M-1:
					sample_data[i], sample_data[i+1] = self.cross_over(sample_data[i], sample_data[i+1])
					i += 2
			
			sselect = self.cal(self.func, sample_data)
			personal_rate = self.personal_rate(sselect)
			add_rate = self.add_rate(personal_rate)
			new_sample = []
			for i in range(M):
				rand = random.random()
				new_sample.append(sample_data[self.select(add_rate, rand)])
			sample_data = new_sample
		x, fx = self.must_res(sample_data)
		sample_f(x, True)
		return x, fx

# f(x) = x*sin(10*pi*x) + 2.0
def sample_f(dx, isPrint = False):
	x = -1.0 + int(dx, 2)*3.0/(math.pow(2, 22)-1.0)
	fx = x*math.sin(10.0*math.pi*x) + 2.0
	if isPrint:
		print "f(%f)=%f" % (x, fx)
	return fx

if __name__ == '__main__':
	herit = Inherit(22, sample_f)
	sample = 10
	while sample <= 500:
		#print "sample len is %d:" % sample 
		step = 10
		while step <= 500:
			print "sample=%d\tstep=%d\t" % (sample,step),
			herit.run(sample, step = step)
			step *= 5 
		sample *= 5
