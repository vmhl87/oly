#include <iostream>

using ll = long long;
ll r;

bool works(ll i, ll j){
	return (i*2+1)*(i*2+1) + (j*2-1)*(j*2-1) <= r*r*4;
}

int main(){
	ll res = 0; std::cin >> r;

	for(int i=0; i<r; ++i){
		int j = 0;
		for(int s=1<<20; s; s/=2)
			if(works(i, j+s)) j += s;
		res += (1+(i>0))*(j*2-1);
	}

	std::cout << res << '\n';
}
