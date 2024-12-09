#include <iostream>

template <int S>
struct not_hashmap{
	int k[1<<S] = {}, v[1<<S] = {};
	bool u[1<<S] = {}, d[1<<S];
	int s, c = 0;

	uint64_t splitmix64(uint64_t i){
		uint64_t z = (i += (uint64_t) 0x9e3779b97f4a7c15);
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
		return z ^ (z >> 31);
	}

	not_hashmap(){
		s = (1<<S) - 1;
	}

	inline int find(int i){
		int I = splitmix64(i) & s;
		while(u[I] && k[I] != i)
			I = (I+1) & s;
		return I;
	}

	void set(int i, int j){
		int I = find(i);
		if(!u[I] || d[I]) ++c;
		u[I] = 1, d[I] = 0,
			k[I] = i, v[I] = j;
	}

	int get(int i){
		return v[find(i)];
	}

	bool has(int i){
		int I = find(i);
		return u[I] && !d[I] && k[I] == i;
	}

	void erase(int i){
		int I = find(i);
		if(u[I] && !d[I] && k[I] == i)
			--c, d[I] = 1;
	}

	int size(){
		return c;
	}
};

int main(){
	not_hashmap<4> m;

	m.set(100, 2);
	m.set(95, 8);
	m.set(431, 914);
	m.set(87, 3234);
	m.set(3, -100);

	std::cout << m.get(100) << ' ' << m.get(3) << ' ' << m.size() << '\n';

	m.erase(431);

	std::cout << m.size() << '\n';

	m.set(431, 230);
	
	std::cout << m.get(431) << ' ' << m.size() << '\n';
}
