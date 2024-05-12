#include <iostream>
#include <queue>
#include <map>

int main(){
	int x, n; std::cin >> x >> n;
	std::priority_queue<int> q;
	std::map<int, int> m;
	for(int i=0; i<n; ++i){
		int t; std::cin >> t;
		if(!m.count(t)) q.push(t);
		++m[t];
	}
}
