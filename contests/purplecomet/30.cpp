#include <iostream>
#include <numeric>

bool adj[5][5];
int order[7];
int order2[7];

bool solve2(){
	for(int i=0; i<7; ++i) if(order2[i]){
		int o = (i+1)%7;
		if(order2[o]){
			if(adj[order2[i]-1][order2[o]-1]) return false;
			if(adj[order2[o]-1][order2[i]-1]) return false;
		}
	}

	return true;
}

int a, b;

void recurse2(int i){
	if(i == 6){
		++b;
		if(solve2()) ++a;

	}else{
		for(int j=0; j<7; ++j) if(!order2[j]){
			order2[j] = i;
			recurse2(i+1);
			order2[j] = 0;
		}
	}
}

void solve(){
	for(int a=0; a<5; ++a)
		for(int b=0; b<5; ++b)
			adj[a][b] = 0;

	for(int i=0; i<7; ++i) if(order[i]){
		int o = (i+1)%7;
		if(order[o]){
			adj[order[i]-1][order[o]-1] = 1;
			adj[order[o]-1][order[i]-1] = 1;
		}
	}

	recurse2(1);
}

void recurse(int i){
	if(i == 6){
		solve();

	}else{
		for(int j=0; j<7; ++j) if(!order[j]){
			order[j] = i;
			recurse(i+1);
			order[j] = 0;
		}
	}
}

int main(){
	recurse(1);
	int c = std::gcd(a, b);
	std::cout << a << ' ' << b << ' ' << c << '\n';
	std::cout << a/c << ' ' << b/c << '\n';
}
