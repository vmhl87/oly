#include <iostream>

int board[1002][1002], cost;

void look(int x, int y);

void consider(int x, int y){
	if(!board[x][y]) board[x][y] = 1;
	look(x, y);
	if(x) look(x-1, y);
	if(y) look(x, y-1);
	if(x<1001) look(x+1, y);
	if(y<1001) look(x, y+1);
}

void look(int x, int y){
	int neigh = 0;
	if(x && board[x-1][y]) ++neigh;
	if(y && board[x][y-1]) ++neigh;
	if(x<1001 && board[x+1][y]) ++neigh;
	if(y<1001 && board[x][y+1]) ++neigh;
	if(neigh != 3) return;
	if(x && !board[x-1][y]) ++cost, consider(x-1, y);
	if(y && !board[x][y-1]) ++cost, consider(x, y-1);
	if(x<1001 && !board[x+1][y]) ++cost, consider(x+1, y);
	if(y<1001 && !board[x][y+1]) ++cost, consider(x, y+1);
}

int main(){
	int n; std::cin >> n;

	while(n--){
		int a, b; std::cin >> a >> b, ++a, ++b;
		if(board[a][b] == 1) --cost;
		board[a][b] = 2;
		consider(a, b);
		std::cout << cost << '\n';
	}
}
