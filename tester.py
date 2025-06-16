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

	# genPermutationTestCase(f)
	
	# genQueryTestCase(f)

	genTreeQueryTestCase(f)

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

def genTreeQueryTestCase(f):
	n = 5
	q = 5
	write_list(f, [n,q])
	for i in range(n) :
		f.write(str(random.randint(1,20)) + " ")
	f.write("\n")
	generateTree(f, n, -1)
	for i in range(q) :
		c = random.randint(1,2)
		if c==1 :
			# Query
			u = random.randint(1, n)
			v = random.randint(1, n)
			write_list(f, [1, u, v])
		else :
			# Update
			u = random.randint(1, n)
			val = random.randint(1,20)
			write_list(f, [2, u, val])

def generateTree(f, n, max_weight):
	parent = [i for i in range(n + 1)]
	size = [1 for _ in range(n + 1)]
	edges = []
	weights = []

	for i in range(n - 1):
		x = random.randint(1, n)
		y = random.randint(1, n)
		while find(parent, x) == find(parent, y):
			x = random.randint(1, n)
			y = random.randint(1, n)
		merge(parent, size, x, y)
		edges.append((x, y))

		if (max_weight != -1):
			w = random.randint(1, max_weight)
			weights.append(w)

	for i in range(len(edges)):
		if (max_weight != -1) :
			write_list(f, [edges[i][0], edges[i][1], weights[i]])
		else :
			write_list(f, [edges[i][0], edges[i][1]])


# DSU
def find(parent, x):
    if parent[x] == x:
        return x
    parent[x] = find(parent, parent[x])
    return parent[x]

def merge(parent, size, x, y):
    r1 = find(parent, x)
    r2 = find(parent, y)
    if size[r1] < size[r2]:
        parent[r1] = r2
        size[r2] += size[r1]
    else:
        parent[r2] = r1
        size[r1] += size[r2]

if __name__ == "__main__":
    main()
