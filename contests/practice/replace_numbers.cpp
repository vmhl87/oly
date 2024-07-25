// edu d2 119 E: Replace Numbers  -  https://codeforces.com/contest/1620/problem/E

#include <iostream>
#include <vector>
#include <map>

std::vector<int> root;

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int q; std::cin >> q;

	int idx = 0;
	std::map<int, std::vector<int>> occ;
	std::map<int, int> back;
	std::vector<int> arr;

	while(q--){
		int t; std::cin >> t;

		if(t&1){
			int x; std::cin >> x;

			if(occ.count(x)) arr.push_back(occ[x].back());
			else occ[x].push_back(idx), arr.push_back(idx), back[idx] = x,
				++idx, root.push_back(-1);

		}else{
			int a, b; std::cin >> a >> b;

			if(a == b) continue;

			if(!occ.count(a)) occ[a].push_back(idx), back[idx] = a,
				++idx, root.push_back(-1);
			if(!occ.count(b)) occ[b].push_back(idx), back[idx] = b,
				++idx, root.push_back(-1);

			root[occ[a].back()] = occ[b].back();

			occ[a].push_back(idx), back[idx] = a, ++idx, root.push_back(-1);
		}
	}
	
	for(int i=0; i<arr.size(); ++i)
		std::cout << back[find(arr[i])] << " \n"[i==arr.size()-1];
}
