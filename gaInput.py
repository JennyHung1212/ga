import sys
import random
from datetime import datetime
import csv
import numpy as np


MAN = int(sys.argv[1])
PARK = int(sys.argv[2])
FACILITY = int(sys.argv[3])
#BUDGET = int(sys.argv[4])
SCALE = 5
TRY_NUM = 10
random.seed(datetime.now())


for iteration in range(TRY_NUM):

	####################  The SCALE set 'S' in each park  ####################
	S = [None]*PARK
	for j in range(PARK):
		Sj_num = random.randint(1,SCALE)
		# S[i] = []
		temp = random.sample(range(1,SCALE+1),Sj_num)
		S[j] = [0]*SCALE
		for k in temp:
			S[j][k-1] = 1

	####################  The FACILITY set 'T' in each park  ####################
	T = [None]*PARK
	for j in range(PARK):
		Tj_num = random.randint(1,FACILITY)
		temp = random.sample(range(1,FACILITY+1),Tj_num)
		T[j] = [0]*FACILITY
		for k in temp:
			T[j][k-1] = 1


	####################  Constructing costs  ####################
	f = [None]*PARK
	for j in range(PARK):
		f[j] = [None]*SCALE
		lastCost = random.randint(500,1500)
		for s in range(SCALE):
			f[j][s] = lastCost + (s)*random.randint(1,200)
			lastCost = f[j][s]


	####################  Floor Area of each scale of each park ####################
	q = [None]*PARK
	for j in range(PARK):
		q[j] = [None]*SCALE
		lastArea = random.randint(50,150)
		for s in range(SCALE):
			q[j][s] = lastArea + (s)*random.randint(1,20)
			lastArea = q[j][s]


	####################  Cost of areas in each facility ####################
	c = [None]*FACILITY
	for t in range(FACILITY):
		c[t] = random.randint(1,10)


	####################  The limit of each facility ####################
	k = [None]*FACILITY
	for t in range(FACILITY):
		k[t] = random.uniform(0,2)
		k[t] = round(k[t],1)
	

	####################  The amount of people in each city ####################
	d = [None]*MAN
	for i in range(MAN):
		d[i] = random.randint(800,1600)
	

	#################### Preference ####################
	p = [None]*MAN
	for i in range(MAN):
		p[i] = [None]*PARK
		for j in range(PARK):
			p[i][j] = [None]*FACILITY
			for t in range(FACILITY):
				p[i][j][t] = random.uniform(-1,1)
				p[i][j][t] = round(p[i][j][t],3)




	#################### Writing to FILE ####################
	filePath = "ga/S_" + str(iteration+1) + ".csv"
	file = open(filePath,'w')
	w = csv.writer(file)
	w.writerows(S)
	file.close()

	filePath = "ga/T_" + str(iteration+1) + ".csv"
	file = open(filePath,'w')
	w = csv.writer(file)
	w.writerows(T)
	file.close()

	filePath = "ga/f_" + str(iteration+1) + ".csv"
	file = open(filePath,'w')
	w = csv.writer(file)
	w.writerows(f)
	file.close()

	filePath = "ga/q_" + str(iteration+1) + ".csv"
	file = open(filePath,'w')
	w = csv.writer(file)
	w.writerows(q)
	file.close()

	filePath = "ga/c_" + str(iteration+1) + ".csv"
	file = open(filePath,'w')
	w = csv.writer(file)
	w.writerows([c])
	file.close()

	filePath = "ga/k_" + str(iteration+1) + ".csv"
	file = open(filePath,'w')
	w = csv.writer(file)
	w.writerows([k])
	file.close()

	filePath = "ga/d_" + str(iteration+1) + ".csv"
	file = open(filePath,'w')
	w = csv.writer(file)
	w.writerows([d])
	file.close()

	filePath = "ga/p_" + str(iteration+1) + ".csv"
	file = open(filePath,'w')
	w = csv.writer(file)
	# w.writerows(p)
	for i in range(MAN):
		for j in range(PARK):
			myID = 'p_' + str(i+1)

		w.writerows([[myID]]+p[i])
	file.close()