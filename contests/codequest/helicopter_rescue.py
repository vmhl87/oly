def of(a, x, y):
	if x<0 or y<0 or x>=len(a) or y>=len(a[0]):
		return {'el':100000,'l':True}
	return a[x][y]

def s(a):
	return a['el']*40000+a['x']*200+a['y']

def test_case():
	d = [int(i) for i in input().split(' ')]
	
	mp = []
	for i in range(d[0]):
		mp.append([])
		r = input().split(' ')
		for j in r:
			el = int(j[:-1])
			w = j[-1]
			mp[-1].append({'el':el,'l':(w=='L')})
	
	lz = []
	
	for i in range(d[0]):
		for j in range(d[1]):
			if of(mp,i,j)['l']:
				el = of(mp,i,j)['el']
				
				works = True
				for xs in range(-1,2):
					for ys in range(-1,2):
						if of(mp,i+xs,j+ys)['el'] < el:
							works = False
				
				if works: lz.append({'el':el,'x':i,'y':j})
	
	lz.sort(key=s)
	
	for l in lz:
		print(str(l['el'])+' '+str(l['x'])+' '+str(l['y']))

t = int(input())

for i in range(t):
	test_case()
