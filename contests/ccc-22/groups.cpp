#include <iostream>
#include <string>
#include <map>

std::string same[100001][2], diff[100001][2];

int main(){
	int x; std::cin >> x;
	for(int i=0; i<x; ++i) std::cin >> same[i][0] >> same[i][1];

	int y; std::cin >> y;
	for(int i=0; i<y; ++i) std::cin >> diff[i][0] >> diff[i][1];

	int g; std::cin >> g;
	std::map<std::string, int> group;
	for(int i=0; i<g; ++i)
		for(int j=0; j<3; ++j){
			std::string s; std::cin >> s;
			group[s] = i;
		}

	int res = 0;
	for(int i=0; i<x; ++i) if(group[same[i][0]] != group[same[i][1]]) ++res;
	for(int i=0; i<y; ++i) if(group[diff[i][0]] == group[diff[i][1]]) ++res;

	std::cout << res << '\n';
}
