#include <iostream>
#include <vector>

using ll = long long;

int to[200000];
bool vis[200000];

std::vector<int> cyc[200000];
int loc[200000];
int pos[200000];
int idx;

void extract(int i){
	int ct = 0, orig = i;
	do{
		cyc[idx].push_back(i);
		loc[i] = idx, pos[i] = ct++, vis[i] = 1;
		i = to[i];
	}while(i!=orig);
	++idx;
}

ll pow(ll k, ll m){
	ll res = 1, p = 2 % m;
	while(k){
		if(k&1) res = res * p % m;
		p = p * p % m;
		k /= 2;
	}
	return res;
}

int main(){
	int n; ll k; std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> to[i], --to[i];

	for(int i=0; i<n; ++i) if(!vis[i]) extract(i);

	for(int i=0; i<n; ++i)
		std::cout << cyc[loc[i]][(pos[i]+pow(k, cyc[loc[i]].size()))%((ll)cyc[loc[i]].size())]+1 << " \n"[i==n-1];
}
