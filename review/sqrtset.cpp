// UNFINISHED
// dang sorted containers really are a pain

#include <iostream>

//  -- begin sqrt bucket set --
const int sz = 4, inf = 2e9;
struct bucket {int values[sz], size = 0, min, max;};
struct sqrtset{
	bucket buckets[sz], *map[sz];
	int size = 0;
	int find(int x){
		for(int i=0; i<size; ++i)
			if(x >= map[i]->min && x < map[i]->max)
				return i;
		return -1;
	}
	bucket* alloc(){
		for(int i=0; i<sz; ++i) if(!buckets[i].size)
			return buckets+i;
		return NULL;
	}
	void insert(int x){
		if(!size){
			bucket *b = alloc();
			b->min = -inf, b->max = inf;
			b->values[0] = x, b->size = 1;
			map[0] = b, size = 1;
		}else{
			int p = find(x);
			if(map[p]->size == sz){
				map[p]->size = sz/2;
				bucket *b = alloc();
				b->min = map[p]->values[sz/2],
					b->max = map[p]->max, b->size = sz-sz/2,
					map[p]->max = map[p]->values[sz/2];
				for(int i=sz/2; i<sz; ++i)
					b->values[i-sz/2] = map[p]->values[i];
				for(++p; p<=size; ++p) std::swap(map[p], b);
				++size, insert(x);
			}else{
				map[p]->values[map[p]->size] = inf;
				for(int i=0; i<=map[p]->size; ++i)
					if(x < map[p]->values[i])
						std::swap(x, map[p]->values[i]);
				++map[p]->size;
			}
		}
	}
	void print(){
		for(int i=0; i<size; ++i){
			std::cout << "Bucket " << i << ": {";
			for(int j=0; j<map[i]->size; ++j)
				std::cout << map[i]->values[j] <<
					" }"[j==map[i]->size-1];
			std::cout << '\n';
		}
	}
};
//   -- end sqrt bucket set --

int main(){
	sqrtset s;

	std::cout << "--DBUG INIT--\n";
	s.insert(1), s.print();
}
