def main() :
	while 1 :
		n,d = map(int,raw_input().split(" "))
		if n+d == 0 : break
		print "%d %d %d" % (n,d,f(n,d) - f(n,d-1))

def pown(a,b) :
	if b==0 : return 1
	elif b%2 : return pown(a,b-1) * a
	else :
		temp = pown(a,b/2)
		return temp*temp

def f(n,d) :
	if n==0 and d>0 : return 0
	elif n>0 and d<0 : return 0
	elif n>0 and d==0 : return 1
	elif n>0 and d==1 : return 2
	else : return pown(f(n,d-1),n) + 1

if __name__ == '__main__':
	main()



"""
ans(n,d) = f(n,d) - f(n,d-1)
f(n,d) is the number of n-ary tree with atmost depth d
f(n,d) = f(n,d-1)^n + 1
1           -> just a single vertex
f(n,d-1)^n  -> root has n children and each one of the children can have 
               f(n,d-1) number of trees beneath them
"""