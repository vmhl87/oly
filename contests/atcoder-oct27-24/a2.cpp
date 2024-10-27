#include <iostream>
#include <array>
#include <map>

std::map<std::array<int, 8>, std::array<int, 2>> m;

int main(){
	for(int i=0; i<1<<16; ++i){
		int o = i;
		int rows[4] = {};
		rows[0] = i & 15, i >>= 4;
		rows[1] = i & 15, i >>= 4;
		rows[2] = i & 15, i >>= 4;
		rows[3] = i & 15;
		std::array<int, 8> arr = {};
		for(int j=0; j<4; ++j)
			arr[j] = __builtin_popcount(rows[j]);
		for(int j=0; j<4; ++j) arr[4] += rows[j]&1, rows[j] /= 2;
		for(int j=0; j<4; ++j) arr[5] += rows[j]&1, rows[j] /= 2;
		for(int j=0; j<4; ++j) arr[6] += rows[j]&1, rows[j] /= 2;
		for(int j=0; j<4; ++j) arr[7] += rows[j]&1;
		if(m.count(arr)){
			m[arr][1] &= ~(m[arr][0] ^ o);
		}else m[arr] = {o, (1<<16)-1};
		i = o;
	}

	int seen[17] = {};

	for(const auto &[x, map] : m){
		int cnt = __builtin_popcount(map[1]);
		if(!seen[cnt]){
			seen[cnt] = 1;
			for(int i : x) std::cout << i << ' ';
			std::cout << ' ' << cnt << '\n';
			for(int i=0; i<4; ++i)
				for(int j=0; j<4; ++j)
					std::cout << "#-"[((map[1]>>(i*4+j))&1)] << " \n"[j==3];
		}
	}
}
