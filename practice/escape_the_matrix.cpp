// Vova Escapes the Matrix  -  https://codeforces.com/contest/1898/problem/F

#include <iostream>

struct exd { int dist, i, j; };
struct cell { struct exd exits[2]; };

char mat[1000][1000];
int dist[1000][1000];
struct cell cells[1000][1000];

int bfs[2000000][2], (*l)[2], (*r)[2];
int exits[4000][2], (*ep)[2], ec;
int n, m;

static inline void reset() { l = bfs, r = bfs; }
static inline void ereset() { ep = exits, ec = 0; }
static inline void push(int i, int j) { (*r)[0] = i, (*r)[1] = j, ++r; }
static inline void epush(int i, int j) { (*ep)[0] = i, (*ep)[1] = j, ++ep, ++ec; }
static inline void bpush(int i, int j){
	push(i, j);
	if(i == 0 || j == 0 || i == n-1 || j == m-1) epush(i, j);
}

static inline void cycle(void proc(int i, int j, int *par)){
	while(l != r){
		int *cur = *(l++);
		if(cur[0]>0) proc(cur[0]-1, cur[1], cur);
		if(cur[1]>0) proc(cur[0], cur[1]-1, cur);
		if(cur[0]<n-1) proc(cur[0]+1, cur[1], cur);
		if(cur[1]<m-1) proc(cur[0], cur[1]+1, cur);
	}
}

void comp_distance(int i, int j, int *par){
	if(dist[i][j] != 0 || mat[i][j] != '.') return;
	dist[i][j] = dist[par[0]][par[1]] + 1, bpush(i, j);
}

void comp_paths(int i, int j, int *par){
	if(mat[i][j] == '#' || cells[i][j].exits[1].dist != -1) return;
	
	struct cell p = cells[par[0]][par[1]];

	if(p.exits[0].dist == -1) return;
	if(cells[i][j].exits[0].dist == -1){
		cells[i][j].exits[0] = p.exits[0];
		++cells[i][j].exits[0].dist;
		if(p.exits[1].dist != -1){
			cells[i][j].exits[1] = p.exits[1];
			++cells[i][j].exits[1].dist;
		}
		push(i, j);
	}else if(!(cells[i][j].exits[0].i == p.exits[0].i &&
			   cells[i][j].exits[0].j == p.exits[0].j)){
		cells[i][j].exits[1] = p.exits[0];
		++cells[i][j].exits[1].dist;
		push(i, j);
	}else if(p.exits[1].dist != -1 &&
			 !(cells[i][j].exits[0].i == p.exits[1].i &&
			   cells[i][j].exits[0].j == p.exits[1].j)){
		cells[i][j].exits[1] = p.exits[1];
		++cells[i][j].exits[1].dist;
		push(i, j);
	}
}

void test_case(){
	std::cin >> n >> m;
	for(int i=0; i<n; ++i) for(int j=0; j<m; ++j)
		std::cin >> mat[i][j], dist[i][j] = 0,
			cells[i][j].exits[0].dist = -1,
			cells[i][j].exits[1].dist = -1;

	reset(), ereset();
	for(int i=0; i<n; ++i) for(int j=0; j<m; ++j)
		if(mat[i][j] == 'V') bpush(i, j);
	cycle(comp_distance);

	//for(int i=0; i<n; ++i) for(int j=0; j<m; ++j)
	//	std::cout << dist[i][j] << " \n"[j==m-1];

	int res = 0;
	for(int i=0; i<n; ++i) for(int j=0; j<m; ++j)
		if(mat[i][j] == '.') ++res;

	if(ec == 0) std::cout << res << '\n';
	else if(ec == 1)
		std::cout << res - dist[exits[0][0]][exits[0][1]] << '\n';
	else{
		reset();
		for(int (*p)[2] = exits; p != ep; ++p){
			struct cell *c = &cells[(*p)[0]][(*p)[1]];
			c->exits[0].i = (*p)[0], c->exits[0].j = (*p)[1];
			c->exits[0].dist = 0, push((*p)[0], (*p)[1]);
		}
		cycle(comp_paths);

		//for(int i=0; i<n; ++i) for(int j=0; j<m; ++j)
		//	std::cout << cells[i][j].exits[0].dist + cells[i][j].exits[1].dist << " \n"[j==m-1];

		int best = 1000000;
		for(int i=0; i<n; ++i) for(int j=0; j<m; ++j) if(cells[i][j].exits[0].dist != -1)
			best = std::min(best, dist[i][j] +
					cells[i][j].exits[0].dist + cells[i][j].exits[1].dist);
		std::cout << res - best << '\n';
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
