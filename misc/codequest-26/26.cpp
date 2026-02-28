#include <iostream>
#include <sstream>
#include <vector>

const int N = 3e5;

std::vector<int> a[N];

void test(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i){
		std::string s; std::getline(std::cin, s);
		std::stringstream V(s);

		int u = -1;

		std::string v;

		while(std::getline(V, v, ' ')){
			if(!v.size()) continue;
			std::cout << "#" << v << '\n';
			if(u == -1) u = std::stoi(v);
			else a[u].push_back(std::stoi(v));
		}
	}

	std::string s; std::getline(std::cin, s);
	std::stringstream V(s);
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
