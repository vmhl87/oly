#include <iostream>

int a[500001][41];

int main(){
	int k; std::cin >> k;
	std::string s, t; std::cin >> s >> t;

	for(int i=0; i<41; ++i) a[0][i] = 1e9;
	for(int i=0; i<=20; ++i) a[0][i+20] = i;
	for(int i=0; i<=20; ++i) a[i][20-i] = i;

	for(int i=0; i<s.length(); ++i)
		for(int j=-20; j<=20; ++j){
			int r = a[i][j+20] + (i+j < 0 || i+j >= t.length() || s[i] != t[i+j]);
			if(j > -20)
				r = std::min(r, a[i+1][j+19]+1);
			if(j < 20)
				r = std::min(r, a[i][j+21]+1);
			a[i+1][j+20] = r;
		}

	int m = t.length() - s.length();

	std::cout << (m <= 20 && m >= -20 && a[s.length()][m+20] <= k ? "Yes" : "No") << '\n';
}
