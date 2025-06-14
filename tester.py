import random
import os
import string
import time

def main() :
	'''
	For testing two codes test.cpp and model.cpp
	'''
	compile()
	testcase = 1
	while 1 :
		genTestCase()
		run("a<in>out1", True, "Test")
		run("b<in>out2", True, "Model")
		# run("java Main <in>out2", False)

		f1 = open("out1","r")
		f2 = open("out2","r")
		s1 = f1.read()
		s2 = f2.read()
		if not s1 == s2 :
			print("Checking test case %d \nNOT_OK"%testcase)
			break
		else :
			print("Checking test case %d \nOK"%testcase)
		testcase+=1
		f1.close()
		f2.close()

def compile():
	os.system("g++ -o a test.cpp")
	os.system("g++ -o b model.cpp")
	# os.system("javac Main.java")

def run(cmd, measure_runtime, log_message):
	if measure_runtime:
		start_time = time.perf_counter()
		os.system(cmd)
		end_time = time.perf_counter()
		elapsed_time = end_time - start_time
		print(f"Elapsed time for {log_message} : {elapsed_time} seconds")
	else:
		os.system(cmd)


def write_list(f, a):
	f.write(" ".join(map(str,a))+"\n")

def genTestCase():
	f = open("in","w")

	# n = 10
	# write_list(f, [n])
	# for i in range(n):
	# 	f.write(str(random.randint(1,3)) + " ")

	genPermutationTestCase(f)
	
	# genQueryTestCase(f)

	f.close()

def genPermutationTestCase(f):
	n = 200000
	m = 120000
	write_list(f, [n,m])
	permutation = list(range(n))
	random.shuffle(permutation)
	for i in permutation:
		write_list(f, [i+1])
	sample = random.sample(permutation, m)
	for i in sample:
		write_list(f, [i+1])


def genQueryTestCase(f):
	n = 100
	q = 50
	write_list(f, [n,q])
	for i in range(n) :
		f.write(str(random.randint(1,10000)) + " ")
	f.write("\n")
	for i in range(q) :
		c = random.randint(1,2)
		if c==1 :
			l = 1
			r = n
			write_list(f, [1,l,r])
		else :
			l = 1
			r = n
			k = random.randint(1,1000)
			write_list(f, [2,l,r,k])

if __name__ == "__main__":
    main()
