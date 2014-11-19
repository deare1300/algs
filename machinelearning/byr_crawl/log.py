#:!/bin/python
#--*-- encoding:utf-8 --*--

# @authour deenw
# this is log module
import sys
import os
import time

class Log:
	def __init__(self, log_err = "err_file", log_out = "out_file"):
		self.log_time = time.strftime("%y-%m-%d-%H-%M-%S", time.localtime())
		self.log_err = log_err + self.log_time
		self.log_out = log_out + self.log_time
		try:
			self.err = open(self.log_err, "w")
			self.out = open(self.log_out, "w")
		except:
			os.stderr.print("log file err**")
	
	def write(self, fd, msg):
		log_time = time.strftime("%y-%m-%d-%H-%M-%S", time.localtime())
		fd.write("log time %s, %s" % (log_time, msg))
	
	def err(self, msg):
		try:
			self.write(self.err, msg)
		except:
			print "err in log the error msg"
	
	def out(self. msg):
		try:
			self.write(self.out, msg)
		except:
			print "err in log the normal msg"

#log = Log()
