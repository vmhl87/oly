// BFS spam starting from source, essentially

#include <iostream>

// is square watched by camera?
bool cam[100][100];
char board[100][100];
// length of shortest path
int best[100][100],
	// best bfs method trust
	bfs[10000], *l, *r;

// cycle detection in conveyor loops - consider()
// takes in a cell and figures out if it has a valid
// unvisited endpoint. If so, adds to BFS "queue".

// seen[][] is used while traverse to find cycle
bool seen[100][100];
// return value indicates whether or not hit cycle
bool consider(int i, int j, int d){
	// already processed, do nothing
	if(best[i][j]) return 1;

	// cycle hit; for efficiency we just make the
	// whole trail a wall to avoid future processing
	if(seen[i][j]){
		board[i][j] = 'W';
		return 1;
	}

	// untravelable square
	if(board[i][j] == 'W' || cam[i][j]) return 1;

	// follow conveyors until hit cycle or valid cell
	seen[i][j] = 1;
	switch(board[i][j]){
		case 'L':
			if(consider(i, j-1, d)) board[i][j] = 'W';
			break;
		case 'R':
			if(consider(i, j+1, d)) board[i][j] = 'W';
			break;
		case 'U':
			if(consider(i-1, j, d)) board[i][j] = 'W';
			break;
		case 'D':
			if(consider(i+1, j, d)) board[i][j] = 'W';
			break;
	}
	seen[i][j] = 0;

	// hit valid square; return and add to queue
	if(board[i][j] == '.') best[i][j] = d, *r = i*100 + j, ++r;

	return 0;
}

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i) for(int j=0; j<m; ++j)
		std::cin >> board[i][j];

	// pointer magic
	l = bfs, r = bfs;

	// compute influence of cameras
	for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) if(board[i][j] == 'C'){
		for(int a=0; a<100; ++a){
			if(board[i+a][j] == 'W') break;
			if(board[i+a][j] == '.' || board[i+a][j] == 'S') cam[i+a][j] = 1;
		}
		for(int a=0; a<100; ++a){
			if(board[i-a][j] == 'W') break;
			if(board[i-a][j] == '.' || board[i-a][j] == 'S') cam[i-a][j] = 1;
		}
		for(int a=0; a<100; ++a){
			if(board[i][j+a] == 'W') break;
			if(board[i][j+a] == '.' || board[i][j+a] == 'S') cam[i][j+a] = 1;
		}
		for(int a=0; a<100; ++a){
			if(board[i][j-a] == 'W') break;
			if(board[i][j-a] == '.' || board[i][j-a] == 'S') cam[i][j-a] = 1;
		}
	}

	// find starting position and push on bfs queue
	for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) if(board[i][j] == 'S')
		if(!cam[i][j]) best[i][j] = 1, *r = i*100 + j, ++r;

	// do the BFS
	while(l != r){
		int i = (*l) / 100, j = (*l) % 100, d = best[i][j]+1; ++l;
		consider(i+1, j, d), consider(i-1, j, d),
			consider(i, j+1, d), consider(i, j-1, d);
	}

	// array initializes with all zeroes and i was too lazy to reinit so
	// just set start node with depth 1 and decrement distances - also
	// removes need for visited array
	for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) if(board[i][j] == '.')
		std::cout << best[i][j]-1 << '\n';
}
