#include <iostream>

using ll = long long;
const int N = 3e5;

ll b[N+2], l[N+2], r[N+2];
int a[N];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	ll res = 0;

	for(ll i=n; i; --i) res += i * (n-i+1);

	for(ll i=0; i<n; ++i){
		res -= (n-i) * (l[a[i]]+b[a[i]]+r[a[i]]);
		r[a[i]-1] = i+1;
		b[a[i]-1] = 0;
		l[a[i]] = 0;
		b[a[i]] = i+1;
		r[a[i]] = 0;
		b[a[i]+1] = 0;
		l[a[i]+1] = i+1;
	}

	std::cout << res << '\n';
}
