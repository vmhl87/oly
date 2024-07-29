elem = [
	{'i':0,'num':1,'sy':'H','wa':[410,486,656]},
	{'i':1,'num':2,'sy':'He','wa':[587]},
	{'i':2,'num':8,'sy':'O2','wa':[627,686,759,822,898]},
	{'i':3,'num':11,'sy':'Na','wa':[588,589]},
	{'i':4,'num':12,'sy':'Mg','wa':[516,517,518]},
	{'i':5,'num':20,'sy':'Ca','wa':[430]},
	{'i':6,'num':20,'sy':'Ca+','wa':[393,396]},
	{'i':7,'num':22,'sy':'Ti+','wa':[336]},
	{'i':8,'num':26,'sy':'Fe','wa':[302,358,382,430,438,466,495,516,527]},
	{'i':9,'num':28,'sy':'Ni','wa':[299]},
	{'i':10,'num':80,'sy':'Hg','wa':[546]}
]

def isin(el,wav):
	for i in el['wa']:
		for j in wav:
			if j[0] == i or j[0] == i+1:
				j[1].add(el['i'])

def cm(a):
	return elem[a]['num']

def isem(a):
	if len(a[1])>0: return True
	return False

def test_case():
	wav = [[int(i),set()] for i in input().split(' ')]
	
	for i in elem:
		isin(i,wav)
	
	m = []
	
	while len(wav):
		ch = wav[0][1].pop()
		wav[0][1].add(ch)
		for i in wav:
			if len(i[1])==1:
				ch=i[1].pop()
				i[1].add(ch)
				break
		
		m.append(ch)
		
#		print(ch)
#		print(wav)
		
#		for i in wav:
#			if ch in i[1]: i[1].remove(ch)
		
#		wav = list(filter(isem,wav))
		
		next = []
		for i in wav:
			if ch not in i[1]:
				next.append(i)
		
		wav = next
	
	m.sort(key=cm)
	
	r = ''
	
	for i in m:
		if len(r) > 0: r += ' '
		r += elem[i]['sy']
	
	print(r)

t = int(input())

for i in range(t):
	test_case()
