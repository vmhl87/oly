def score(v):
	return round(1000*(v[1]+v[2]+v[3]+v[4]))

def better(p,r):
	return score(r)<=score(p)*.8

def form(i):
	if i == int(i): return int(i)
	return i

def test_case():
	n = int(input())
	comp = [int(i) for i in input().split(' ')]
	
	for i in range(n):
		rep = [int(i) for i in input().split(' ')]
		
		if better(comp,rep):
			comp = rep
	
	print(str(comp[0])+' '+str(form(score(comp)/1000)))

t = int(input())

for i in range(t):
	test_case()
