#include <iostream>
#include <array>
#include <queue>

struct node{
	int dist[9];
	int vis;
	char c;
};

node board[100][100];
//std::queue<std::array<int, 2>> bfs;

struct chinesebfs{
	std::vector<std::array<int, 2>> a; int l;
	std::array<int, 2> pop(){
		std::array<int, 2> res;
		res[0] = a[l][0], res[1] = a[l][1];
		++l; return res;
	}
	void push(std::array<int, 2> i) { a.push_back(i); }
	int size() { return a.size() - l; }
};

chinesebfs bfs;

void proc(std::array<int, 2> src, std::array<int, 2> loc){
	if(board[loc[0]][loc[1]].c == 'P') return;
	if(board[loc[0]][loc[1]].c == '.'){
		if(board[loc[0]][loc[1]].vis > 10) return;
		bool did = 0;
		for(int i=0; i<9; ++i)
			if((board[src[0]][src[1]].dist[i] < board[loc[0]][loc[1]].dist[i] ||
			   !board[loc[0]][loc[1]].dist[i]) && board[src[0]][src[1]].dist[i]){
				board[loc[0]][loc[1]].dist[i] = board[src[0]][src[1]].dist[i] + 1,
					did = 1;
		}
		if(did) bfs.push(loc), ++board[loc[0]][loc[1]].vis;
	}
	if(board[loc[0]][loc[1]].c == 'C'){
		if(board[loc[0]][loc[1]].vis > 10) return;
		bool did = 0;
		for(int i=0; i<8; ++i)
			if((board[src[0]][src[1]].dist[i] < board[loc[0]][loc[1]].dist[i+1] ||
			   !board[loc[0]][loc[1]].dist[i+1]) && board[src[0]][src[1]].dist[i]){
				board[loc[0]][loc[1]].dist[i+1] = board[src[0]][src[1]].dist[i] + 1;
					did = 1;
		}
		if(did) bfs.push(loc), ++board[loc[0]][loc[1]].vis;
	}
	if(board[loc[0]][loc[1]].c == 'J'){
		if(board[loc[0]][loc[1]].vis > 10) return;
		bool did = 0;
		for(int i=1; i<9; ++i)
			if((board[src[0]][src[1]].dist[i] < board[loc[0]][loc[1]].dist[i-1] ||
			   !board[loc[0]][loc[1]].dist[i-1]) && board[src[0]][src[1]].dist[i]){
				board[loc[0]][loc[1]].dist[i-1] = board[src[0]][src[1]].dist[i] + 1;
					did = 1;
		}
		if(did) bfs.push(loc), ++board[loc[0]][loc[1]].vis;
	}
	if(board[loc[0]][loc[1]].c == 'E'){
		int best = 0;
		for(int i=0; i<9; ++i){
			if((!best || best > board[src[0]][src[1]].dist[i]) && board[src[0]][src[1]].dist[i])
				best = board[src[0]][src[1]].dist[i];
		}
		std::cout << best << '\n';
		exit(0);
	}
}

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j){
			std::cin >> board[i][j].c;
			if(board[i][j].c == 'S'){
				board[i][j].dist[0] = 1;
				bfs.push({i, j});
			}
		}

	while(bfs.size()){
		std::array<int, 2> now = bfs.pop();

		if(now[0]) proc(now, {now[0]-1, now[1]});
		if(now[1]) proc(now, {now[0], now[1]-1});
		
		if(now[0]<n-1) proc(now, {now[0]+1, now[1]});
		if(now[1]<m-1) proc(now, {now[0], now[1]+1});
	}

	std::cout << "SPOOKED!\n";
}
