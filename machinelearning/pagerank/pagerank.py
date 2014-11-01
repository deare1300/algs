#!/bin/python
#code:utf-8

def personrank(G, root, alpha, step):
	rank = dict()
	for x in G:
		rank[x] = 0
	rank[root] = 1
	
	for k in range(step):
		tmp = dict()
		for v in G.keys():
			tmp[v] = 0
		for i, ri in G.items():
			for j, rj in ri.items():
				tmp[j] += alpha*rank[i]/(len(ri)*1.0)
		tmp[root] += 1-alpha
		rank = tmp
		print k
		for key, value in rank.items():
			print key, value,
		print 		
	return rank
				
if __name__ == '__main__':
	G = {'A': {'a' : 1,'c' : 1},
	'B' : {'a' : 1, 'b' : 1, 'c':1, 'd':1},
	'C' : {'c' : 1, 'd' : 1},
	'a' : {'A' : 1, 'B' : 1},
	'b' : {'B' : 1},
	'c' : {'A' : 1, 'B' : 1, 'C':1},
	'd' : {'B' : 1, 'C' : 1}}
	personrank(G, 'A', 0.85, 20)
