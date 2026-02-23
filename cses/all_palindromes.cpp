#include <iostream>
#include <string>

using ll = long long;
const int N = 2e5,
	  m = 1e9 + 7,
	  p = 200003;
 
ll big[1024], small[1025];
 
ll pow(int i) { return big[i>>10] * small[i&1023] % m; }

int a[N], f[N+1], b[N+1], n;

bool palindromic(int l, int r){
	if(l < 0 || r >= n) return 0;
	return (pow(n-r-1)*(m + (f[r+1] - f[l]) % m)) % m == (pow(l)*(m + (b[l] - b[r+1]))) % m;
}

int main(){
	std::string s; std::cin >> s, n = s.size();

	++big[0], ++small[0];
	for(int i=0; i<1024; ++i) small[i+1] = small[i]*p % m;
	for(int i=1; i<1024; ++i) big[i] = big[i-1]*small[1024] % m;

	for(int i=0; i<n; ++i) f[i+1] = (f[i] + s[i]*pow(i)) % m;
	for(int i=0; i<n; ++i) b[n-i-1] = (b[n-i] + s[n-i-1]*pow(i)) % m;

	for(int i=0; i<n; ++i) a[i] = 1;

	for(int i=0, p=0; i<n; p = std::max(++i, p)){
		for(int j=p; j<n && palindromic(i+i-j, j); ++j){
			a[j] = std::max(a[j], (j-i)*2 + 1);
			p = j+1;
		}
	}

	for(int i=0, p=1; i<n-1; p = std::max(++i + 1, p)){
		for(int j=p; j<n && palindromic(i+i-j+1, j); ++j){
			a[j] = std::max(a[j], (j-i)*2);
			p = j+1;
		}
	}

	for(int i=0; i<n; ++i) std::cout << a[i] << " \n"[i==n-1];
}
