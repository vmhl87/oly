def rn(a):
	return str(round(a,2))

def test_case():
	l1 = [int(i) for i in input().split(',')]
	l2 = [int(i) for i in input().split(',')]
	
	e1 = [(l2[0]-l1[0])/l1[3],l2[3]/l1[3]]
	e2 = [(l2[1]-l1[1])/l1[4],l2[4]/l1[4]]
	e3 = [(l2[2]-l1[2])/l1[5],l2[5]/l1[5]]
	
	x = (e2[0]-e1[0])/(e1[1]-e2[1])
	y = (x-e1[0])/e1[1]
	
	if x == e3[0]+e3[1]*y:
		ret = ''
		ret += rn(e1[0]+e1[1]*x) + ','
		ret += rn(e2[0]+e2[1]*x) + ','
		ret += rn(e3[0]+e3[1]*x)
		print(ret)
	else:
		print("Miss")

t = int(input())

for i in range(t):
	test_case()
