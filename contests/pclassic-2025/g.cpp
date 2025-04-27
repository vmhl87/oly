#include <iostream>
#include <set>

int count[31][2];

uint32_t contrast(uint32_t x){
	uint32_t res = 0;
	for(int i=0; i<32; ++i){
		if(x&(1<<i)) res += std::max(count[i][0], count[i][1]);
		else res += std::min(count[i][0], count[i][1]);
	}
	return res;
}

uint32_t proc(uint32_t x){
	uint32_t res = x;
	for(int i=0; i<32; ++i)
		if(count[i][1] > count[i][0]) res ^= 1<<i;
	return res;
}

const int N = 1e5;

std::set<uint32_t> a;

uint32_t best(uint32_t s, int T){
	if(a.count(s)){
		uint32_t z = -1, y = 1<<31;

		for(int i=T; i<32; ++i) if(!(s&(1<<i))){
			uint32_t x = best(s|(1<<i), T+1), c = contrast(x);
			if(x == -1) continue;
			if(c < y){
				y = c;
				z = x;
			}else if(c == y){
				if(proc(x) < proc(z)) z = x;
			}
		}

		return z;

	}else return s;
}

int main(){
	int n, m; std::cin >> n >> m;

	while(n--){
		uint32_t x; std::cin >> x;
		for(int i=0; i<32; ++i)
			if(x&(1<<i)) ++count[i][1];
			else ++count[i][0];
	}

	for(int i=0; i<m; ++i){
		uint32_t x; std::cin >> x;
		a.insert(proc(x));
	}

	std::cout << proc(best(0, 0)) << '\n';
}
