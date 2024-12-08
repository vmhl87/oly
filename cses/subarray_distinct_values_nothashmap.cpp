//#include <unordered_map>
#include <iostream>

template <int S>
struct not_hashmap{
	int k[1<<S] = {}, v[1<<S] = {};
	bool u[1<<S] = {}, d[1<<S];
	int s, c = 0;

	not_hashmap(){
		s = (1<<S) - 1;
	}

	inline int find(int i){
		int I = i & s;
		while(u[I] & k[I] != i)
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

typedef long long LL;

not_hashmap<18> window;

void inc(int i){
	if(window.has(i)) window.set(i, window.get(i)+1);
	else window.set(i, 1);
}

void dec(int i){
	window.set(i, window.get(i)-1);
	if(window.get(i) == 0) window.erase(i);
}

int main(){
	int n, k; std::cin >> n >> k;

	//std::unordered_map<int, int> window;

	LL res = 0;

	int a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];

	int p = 0;

	for(int i=0; i<n; ++i){
		//++window[a[i]];
		inc(a[i]);

		while(window.size() > k){
			//--window[a[p]];
			//if(window[a[p]] == 0)
				//window.erase(a[p]);
			dec(a[p]);

			++p;
		}

		res += i - p + 1;
	}

	std::cout << res << '\n';
}
