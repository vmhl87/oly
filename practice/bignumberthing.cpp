#include <iostream>
#include <vector>
#include <string>

using ll = long long;

int main(){
	std::string s; std::cin >> s;
	std::vector<ll> v;
	v.reserve(1e5), v.push_back(0);

	for(int i=s.length()-1, j=0, k=1; i>=0; --i, ++j){
	  v.back() = v.back() + (s[i]-'0')*k, k *= 10;
	  if(j%9 == 8) v.push_back(0), k=1;
	}

	ll rem = 0;

	while(v.size()){
	  rem = v.back() + rem*1e9;
	  rem %= 2019;
	  v.pop_back();
	}

	std::cout << rem << '\n';
}
