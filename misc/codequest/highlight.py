def rcol(v):
	return [int(i) for i in v[1:-1].split(',')]

def blend(high,col,mask):
	ret = [i*mask/2 for i in high]
	for i in range(3):
		ret[i] += col[i]*(1-mask/2)
	return '('+str(int(ret[0]))+','+str(int(ret[1]))+','+str(int(ret[2]))+')'

def test_case():
	high = rcol(input())
	
	w,h = [int(i) for i in input().split(' ')]
	
	mask = []
	
	for i in range(h):
		mask.append([int(i) for i in input().split(' ')])
	
	for i in range(h):
		for j in range(w):
			border = False
			for a in range(-1,2):
				for b in range(-1,2):
					if i+a>=0 and j+b>=0 and i+a<h and j+b<w:
						if mask[i+a][j+b]==1:
							border = True
			if border and mask[i][j]==0: mask[i][j]=2
	
#	for i in range(h):
#		print(' '.join([str(x) for x in mask[i]]))
	
	for i in range(h):
		ret = ''
		cols = [rcol(i) for i in input().split(' ')]
		for j in range(w):
			if j > 0: ret += ' '
			ret += blend(high, cols[j], mask[i][j])
		print(ret)

t = int(input())

for i in range(t):
	test_case()
