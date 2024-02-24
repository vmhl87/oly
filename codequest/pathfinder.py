def fill(maze,mask,x,y):
	if x==len(maze)-1 and y==len(maze)-1:
		return 1
	
	ret = 0
	mask[x][y] = True
	ln = len(maze)-1
	
	if x>0 and not mask[x-1][y]:
		ret += fill(maze,mask,x-1,y)
	
	if y>0 and not mask[y][x-1]:
		ret += fill(maze,mask,x,y-1)
	
	if x<ln and not mask[x+1][y]:
		ret += fill(maze,mask,x+1,y)
	
	if y<ln and not mask[x][y+1]:
		ret += fill(maze,mask,x,y+1)
	
	mask[x][y] = False
	return ret

def test_case():
	n = int(input())
	
	maze = []
	mask = []
	
	for i in range(n):
		maze.append([i=='1' for i in input()])
		mask.append([False for i in range(n)])
	
	ret = fill(maze,mask,0,0)

t = int(input())

for i in range(t):
	test_case()
