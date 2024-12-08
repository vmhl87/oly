#include <iostream>
#include <vector>

int a[50], b[50][100], c[60];
bool s1[60], s2[60];

void test(){
	int n, m; std::cin >> n >> m;
	std::fill(c, c+60, 0);

	for(int i=0; i<m; ++i){
		std::cin >> a[i];
		for(int j=0; j<a[i]; ++j){
			std::cin >> b[i][j];
		}
	}

	// verify 1
	for(int i=0; i<m; ++i){
		std::vector<int> v;

		for(int j=0; j<a[i]; ++j)
			if(c[b[i][j]]){
				if(!v.size() || b[i][j] != v.back())
					goto fail;
				v.pop_back();
				c[b[i][j]] = 0;
			}else{
				v.push_back(b[i][j]);
				c[b[i][j]] = 1;
			}
	}

	for(int i=1; i<=n; ++i) if(c[i]) goto fail;

	// verify 2
	for(int i=1; i<m; ++i){
		std::fill(s1, s1+60, 0);
		std::fill(s2, s2+60, 0);

		for(int j=0; j<a[i-1]; ++j)
			s1[b[i-1][j]] = 1;

		for(int j=0; j<a[i]; ++j)
			s2[b[i][j]] = 1;

		for(int j=1; j<=n; ++j)
			if(s1[j]^s2[j]) ++c[j];

		std::vector<int> v1, v2;

		for(int j=0; j<a[i-1]; ++j)
			if(s2[b[i-1][j]]) v1.push_back(b[i-1][j]);

		for(int j=0; j<a[i]; ++j)
			if(s1[b[i][j]]) v2.push_back(b[i][j]);

		if(v1 != v2) goto fail;
	}

	std::fill(s1, s1+60, 0);
	std::fill(s2, s2+60, 0);

	for(int i=0; i<a[0]; ++i) s1[b[0][i]] = 1;
	for(int i=0; i<a[m-1]; ++i) s2[b[m-1][i]] = 1;

	for(int i=1; i<=n; ++i) if(s1[i]) ++c[i];
	for(int i=1; i<=n; ++i) if(s2[i]) ++c[i];

	for(int i=1; i<=n; ++i) if(c[i] < 2) goto fail;

	std::cout << "YES\n";
	return;

fail:
	std::cout << "NO\n";
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
