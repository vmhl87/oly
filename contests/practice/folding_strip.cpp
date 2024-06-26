// Folding Strip  -  https://codeforces.com/contest/1966/problem/E

#include <iostream>
#include <vector>

void test_case(){
	int n; std::cin >> n;

	std::vector<int> seq;

	char last = 0;
	int len = 1;

	while(n--){
		char c; std::cin >> c;

		if(c == last) ++len;
		else if(last != 0){
			seq.push_back(len);
			len = 1;
		}

		last = c;
	}

	if(len) seq.push_back(len);

	int pos = 0, min = 0, max = 0, dir = 1;

	for(int sec : seq){
		if(sec & 1){
			pos += dir;

			if(pos < min) min = pos;
			if(pos > max) max = pos;
		}else{
			if(pos+dir < min) min = pos+dir;
			if(pos+dir > max) max = pos+dir;

			dir = -dir;
		}
	}

	std::cout << max - min << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
