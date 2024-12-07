#include <iostream>
#include <vector>

using ll = long long;

bool p[(int)3e6];
std::vector<ll> r;
ll n;

bool f(ll x){
	return x <= n;
}

int main(){
	for(int i=2; i<3e6; ++i) p[i] = 1;
	for(int i=2; i<3e6; ++i) if(p[i]){
		for(int j=i+i; j<3e6; j+=i) p[j] = 0;
		r.push_back(i);
	}

	std::cin >> n;

	ll x = 0;
	for(int j=1<<22; j; j/=2)
		if((x+j)*(x+j) <= n) x += j;

	n = x;

	int res = 0;

	for(int i=0; i<r.size(); ++i)
		for(int j=i+1; j<r.size(); ++j){
			if(f(r[i]*r[j])) ++res;
			else break;
		}

	for(int i=2; i<200; ++i) if(p[i]){
		if(i*i*i*i <= n) ++res;
		else break;
	}

	std::cout << res << '\n';
}
