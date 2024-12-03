#include <iostream>
#include <vector>
#include <array>
#include <queue>

using ll = long long;
const int N = 1e3;

std::vector<std::array<int, 3>> adj[N];

ll c[N], d[N];
int e[100];
bool v[N];

int main(){
	freopen("cowroute.in", "r", stdin);
	freopen("cowroute.out", "w", stdout);

	int a, b, n; std::cin >> a >> b >> n;

	for(int i=0; i<n; ++i){
		int c, s; std::cin >> c >> s;
		for(int j=0; j<s; ++j)
			std::cin >> e[j], --e[j];
		for(int j=0; j<s; ++j)
			for(int k=j+1; k<s; ++k)
				adj[e[j]].push_back({e[k], c, k-j});
	}

	std::priority_queue<std::array<ll, 3>> q;
	
	q.push({0, 0, a-1});

	while(q.size()){
		std::array<ll, 3> t = q.top();
		q.pop();

		if(v[t[2]]) continue;

		c[t[2]] = -t[0];
		d[t[2]] = -t[1];
		v[t[2]] = 1;

		for(const auto &[x, c, d] : adj[t[2]])
			if(!v[x]) q.push({t[0]-c, t[1]-d, x});
	}

	if(v[b-1]) std::cout << c[b-1] << ' ' << d[b-1] << '\n';
	else std::cout << "-1 -1\n";
}
