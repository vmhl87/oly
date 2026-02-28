def tm():
	r = [int(i) for i in input().split(':')]
	return r[0]*4+r[1]/15

def dif(a,b):
	return (a-b+96)%96

def test_case():
	r = input().split(' ')
	if r[0] == 'TRUE':
		for i in range(int(r[1])): input()
		print('NONE')
		return
	
	n = int(r[1])
	threat = 0 # currently NONE
	
	if n >= 12: threat = 1
	if n >= 24: threat = 2
	if n >= 36: threat = 3
	
	last = None
	ln = 0
	entry = 1
	
	for i in range(n):
		t = tm()
		
		if last:
			d = dif(t,last)
			
			if d == 1: ln += 1
			
			else:
				ln = 1
				entry += 1
		
		if ln >= 4 and threat < 1: threat = 1
		if ln >= 8 and threat < 2: threat = 2
		if ln >= 12 and threat < 3: threat = 3
		
		if entry >= 4 and threat < 2: threat = 2
		if entry >= 8 and threat < 3: threat = 3
		
		last = t
	
	levels = ['NONE', 'LOW', 'MEDIUM', 'HIGH']
	print(levels[threat])

t = int(input())

for i in range(t):
	test_case()
