import math

def area(v):
	return v*v*math.sqrt(3)/4

def fr(v):
	x = str(v)
	
	return x[:-2]+'.'+x[-2:]

def test_case():
	t = [int(i) for i in input().split(' ')]
	
	print(str(3**t[1]) + ' ' + fr(round(100*(area(t[0])*(.75**t[1])))))

t = int(input())

for i in range(t):
	test_case()
