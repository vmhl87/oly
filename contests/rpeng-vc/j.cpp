#include <iostream>
#include <map>

using ll = long long;

ll count[9][7];

std::map<char, int> r = {
	{'X', 0},
	{'H', 1},
	{'G', 2},
	{'O', 3},
	{'M', 4},
	{'E', 5},
	{'S', 6},
	{'B', 7},
	{'I', 8},
};

int a[5];
ll ans = 0;

ll rg(const char *b, int n){
	int res = 0;
	for(int i=0; i<n; ++i)
		res += a[r[b[i]]];
	return res % 7;
}

void rec(int i){
	if(i == 5){
		ll res = 1;
		for(int j=0; j<5; ++j)
			res = res*count[j][a[j]];

		if(rg("XHH", 3)*rg("GOH", 3)*rg("MOO", 3) == 0)
			ans += res;

	}else{
		for(int j=0; j<7; ++j)
			a[i] = j, rec(i+1);
	}
}

int main(){
	freopen("bgm.in", "r", stdin);
	freopen("bgm.out", "w", stdout);

	int n; std::cin >> n;

	while(n--){
		char c; std::cin >> c;
		int v; std::cin >> v;
		v %= 7; if(v < 0) v += 7;
		++count[r[c]][v];
	}

	for(int i=0; i<7; ++i)
		for(int j=0; j<7; ++j)
			count[r['H']][(i+j)%7] +=
				count[r['E']][i]*count[r['S']][j];

	for(int i=0; i<7; ++i)
		for(int j=0; j<7; ++j)
			count[r['X']][(i+j)%7] +=
				count[r['B']][i]*count[r['I']][j];

	rec(0);

	std::cout << ans << '\n';
}
