#include <iostream>

const int M = 998244353;
using ll = long long;

int main(){
	int k; std::cin >> k;

	ll res = 0;

	for(int sum=k-4; sum*3>=k; --sum){
		ll p = 0;

		for(int alt=std::min(sum, k-sum-2); alt*2>=k-sum; --alt){
			int other = k-sum-alt;

			ll f;

			if(sum != alt && alt != other) f = 6;
			else if(sum != alt || alt != other) f = 3;
			else f = 1;

			p += f * (alt-1) * (other-1);
		}

		res = (res + ((p * (sum-1) * (k-sum)) % M)) % M;
	}

	std::cout << res << '\n';
}
