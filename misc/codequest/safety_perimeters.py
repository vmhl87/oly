import math

def test_case():
	n = int(input())

	r = [int(i) for i in input().split(' ')]

	for i in range(n):
		p = [int(i) for i in input().split(' ')]
		
		dist = math.sqrt((p[0]-r[0])**2+(p[1]-r[1])**2)
		
		ret = ""
		
		if dist < r[2]:
			ret = "DANGER"
		else:
			ret = "SAFE"
		
		print(f'({p[0]},{p[1]}) '+ret)

t = int(input())

for i in range(t):
	test_case()
