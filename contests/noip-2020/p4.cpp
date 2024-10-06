#include <iostream>

using ll = long long;

int w[10], c[500000], d[500000];
int shift[10], n, k;

ll res;
int pos[10];

bool bounded(int p[10]){
	for(int i=0; i<k; ++i)
		if(p[i] < 0 || p[i] >= w[i]) return 0;
	return 1;
}

void run(){
	int p[10]; for(int i=0; i<k; ++i) p[i] = pos[i];

	ll step = 0;
	while(bounded(p)){
		for(int i=0; i<n && bounded(p); ++i)
			p[c[i]] += d[i], ++step;

		bool cont = 0;
		for(int i=0; i<k; ++i)
			cont |= shift[i] != 0;

		if(!cont) std::cout << -1 << '\n', exit(0);
	}

	res += step;
}

void fill(int i){
	if(i == k) run();
	else for(int j=0; j<w[i]; ++j)
		pos[i] = j, fill(i+1);
}

ll out[100010];

ll comb(ll a, ll b){
	if(a == 0 || b < a) return b;
	return a;
}

int main(){
	std::cin >> n >> k;
	for(int i=0; i<k; ++i) std::cin >> w[i];
	for(int i=0; i<n; ++i) std::cin >> c[i] >> d[i], --c[i], shift[c[i]] += d[i];

	bool fixed = 1;
	for(int i=0; i<k; ++i)
		fixed &= shift[i] == 0;

	if(fixed){
		int min[10] = {}, max[10] = {}, p[10] = {};
		for(int i=0; i<n; ++i){
			p[c[i]] += d[i];
			min[c[i]] = std::min(min[c[i]], p[c[i]]);
			max[c[i]] = std::max(max[c[i]], p[c[i]]);
		}
		for(int i=0; i<k; ++i)
			if(max[i] - min[i] < w[i])
				std::cout << "-1\n", exit(0);
	}

	if(k == 1){
		int p = 0;
		for(int i=0; i<n; ++i){
			p += d[i];
			if(p > 0){
				if(w[0]-p >= 0)
					out[w[0]-p] = comb(out[w[0]-p], i+1);
			}else if(p < 0){
				if(-p-1 < w[0])
					out[-p-1] = comb(out[-p-1], i+1);
			}
		}

		if(p < 0){
			for(int i=-p; i<w[0]; ++i)
				out[i] = comb(out[i], out[i+p] + (ll)n);
		}else if(p > 0){
			for(int i=w[0]-p-1; i>=0; --i)
				out[i] = comb(out[i], out[i+p] + (ll)n);
		}

		for(int i=0; i<w[0]; ++i){
			//std::cout << out[i] << " \n"[i==w[0]-1];
			if(out[i] == 0) std::cout << "-1\n", exit(0);
			res += out[i];
		}

	}else fill(0);

	std::cout << res << '\n';

	//res = 0, fill(0), std::cout << res << '\n';
}
