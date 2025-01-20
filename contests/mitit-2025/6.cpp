#include <iostream>
#include <vector>
#include <string>

void test(){
	std::string a, b; std::cin >> a >> b;
	std::string a1, b1, a2, b2;

	for(int i=0; i<a.length(); ++i)
		if(i&1) a1 += a[i], b1 += b[i];
		else a2 += a[i], b2 += b[i];

	int res = 0;

	{
		std::vector<int> c1, d1, c2, d2;

		for(int i=0; i<a1.length(); ++i){
			if(a1[i] == 'A') c1.push_back(i);
			else d1.push_back(i);
			if(b1[i] == 'A') c2.push_back(i);
			else d2.push_back(i);
		}

		if(c1.size() != c2.size() || d1.size() != d2.size()){
			std::cout << "-1\n"; return;
		}

		for(int i=0; i<c1.size(); ++i)
			res += std::abs(c1[i]-c2[i]);
		for(int i=0; i<d1.size(); ++i)
			res += std::abs(d1[i]-d2[i]);
	};

	{
		std::vector<int> c1, d1, c2, d2;

		for(int i=0; i<a2.length(); ++i){
			if(a2[i] == 'A') c1.push_back(i);
			else d1.push_back(i);
			if(b2[i] == 'A') c2.push_back(i);
			else d2.push_back(i);
		}

		if(c1.size() != c2.size() || d1.size() != d2.size()){
			std::cout << "-1\n"; return;
		}

		for(int i=0; i<c1.size(); ++i)
			res += std::abs(c1[i]-c2[i]);
		for(int i=0; i<d1.size(); ++i)
			res += std::abs(d1[i]-d2[i]);
	};

	std::cout << res/2 << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
