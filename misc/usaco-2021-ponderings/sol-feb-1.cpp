// Direct simulation - if a cow has 3 neighbors, there is only one
// possible place to add a new cow so that the previously satisfied
// cow no longer has 3 neighbors. If new cow now has 3 neighbors,
// or causes nearby cow to have, then recurse. All deterministic.

#include <iostream>

int board[3001][3001], cost;

void look(int x, int y);

void consider(int x, int y){
	if(!board[x][y]) board[x][y] = 1;
	look(x, y);
	if(x) look(x-1, y);
	if(y) look(x, y-1);
	if(x<3000) look(x+1, y);
	if(y<3000) look(x, y+1);
}

void look(int x, int y){
	if(!board[x][y]) return;
	int neigh = 0;
	if(x && board[x-1][y]) ++neigh;
	if(y && board[x][y-1]) ++neigh;
	if(x<3000 && board[x+1][y]) ++neigh;
	if(y<3000 && board[x][y+1]) ++neigh;
	if(neigh != 3) return;
	if(x && !board[x-1][y]) ++cost, consider(x-1, y);
	else if(y && !board[x][y-1]) ++cost, consider(x, y-1);
	else if(x<3000 && !board[x+1][y]) ++cost, consider(x+1, y);
	else if(y<3000 && !board[x][y+1]) ++cost, consider(x, y+1);
}

int main(){
	int n; std::cin >> n;

	while(n--){
		int a, b; std::cin >> a >> b, a += 1000, b += 1000;
		if(board[a][b] == 1) --cost;
		board[a][b] = 2;
		consider(a, b);
		std::cout << cost << '\n';
	}
}
