template <int S>
struct clown_map{
	clown_map *next[2];
	int v;
	clown_map(){
		next[0] = 0, next[1] = 0;
		v = 0;
	}
	int _get(int i, int d){
		if(d){
			if(!next[i&1]) return 0;
			return next[i&1]->_get(i/2, d-1);
		}else return v;
	}
	int get(int i){
		return _get(i, S);
	}
	bool _count(int i, int d){
		if(d){
			if(!next[i&1]) return 0;
			return next[i&1]->_count(i/2, d-1);
		}else return 1;
	}
	bool count(int i){
		return _count(i, S);
	}
	void _set(int i, int j, int d){
		if(d){
			if(!next[i&1]) next[i&1] = new clown_map;
			next[i&1]->_set(i/2, j, d-1);
		}else v = j;
	}
	void set(int i, int j){
		_set(i, j, S);
	}
};

#include <iostream>

int main(){
	clown_map<31> m;

	m.set(100, 3);
	m.set(20298342, 104);
	m.set(1, 24);
	m.set(4552, 109423);

	std::cout << m.get(20298342) << '\n';

	std::cout << m.count(342) << ' ' << m.count(4552) << '\n';
}
