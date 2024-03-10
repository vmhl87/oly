#include<bits/stdc++.h>
using namespace std;

#define f first
#define s second

const int MAX_N = 5;//1e2;
const int CHANGE_R[4] = {1, -1, 0, 0};
const int CHANGE_C[4] = {0, 0, 1, -1};

int main() {
	// freopen("countcross.in", "r", stdin);
	// freopen("countcross.out", "w", stdout);
	int n, k, road_num; cin >> n >> k >> road_num;
	bool road[MAX_N][MAX_N][MAX_N][MAX_N];
	for (int i=0; i<road_num; ++i) {
		int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2; --r1; --c1; --r2; --c2;
		road[r1][c1][r2][c2] = true;		
		road[r2][c2][r1][c1] = true;		
	} 

	vector<vector<int>> grid(n, vector<int>(n, -1));
	for (int i=0; i<k; ++i) {
		int r, c; cin >> r >> c; --r; --c;
		grid[r][c] = 0;	
	}

	int curr_comp = 0;
	bool visited[MAX_N][MAX_N];
	int ans = k*(k-1)/2;

	for (int i=0; i<n; ++i) {
		for (int j=0; j<n; ++j) {

			if (visited[i][j] || grid[i][j] == -1) continue;

			int curr_count = 0;
			queue<pair<int, int>> q; q.push({i, j});

			while (!q.empty()) {
				pair<int, int> p = q.front(); q.pop();
				int y = p.f, x = p.s;
				visited[y][x] = true;

				if (grid[y][x] != -1) {
					grid[y][x] = curr_comp;
					++curr_count;
				}

				for (int h=0; h<4; ++h) {
					int r = y+CHANGE_R[h], c = x+CHANGE_C[h];
					if (r<0 || r>=n || c<0 || c>=n || visited[r][c] || road[y][x][r][c]) continue;
					q.push({r, c});
				}
			}

			++curr_comp;
			ans -= (curr_count)*(curr_count-1)/2;
		}
	}

	// for (int i=0; i<n; ++i) {
	// 	for (int j=0; j<n; ++j) {
	// 		cout << grid[i][j] << ' ';	
	// 	}
	// 	cout << '\n';
	// }

	cout << ans;
}
