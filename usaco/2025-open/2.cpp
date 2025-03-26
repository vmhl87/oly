#include <iostream>
#include <array>
#include <map>
#include <set>

const int N = 2e5;

int a[N], ct[N], t[N*2], t2[N*2+2];

int n;
std::array<int, 4> last;
bool lastset, stillwork;

std::set<int> rev[N+1];
int tmax[N*2+2], tmin[N*2+2];

int maxq(int l, int r){
	int res = 0;
	for(l += n+1, r += n+1; l<r; l/=2, r/=2){
		if(l&1) res = std::max(res, tmax[l++]);
		if(r&1) res = std::max(res, tmax[--r]);
	}
	return res;
}

int minq(int l, int r){
	int res = n+1;
	for(l += n+1, r += n+1; l<r; l/=2, r/=2){
		if(l&1) res = std::min(res, tmin[l++]);
		if(r&1) res = std::min(res, tmin[--r]);
	}
	return res;
}

void update2(int i){
	if(rev[i].size() && i){
		int M = *(--rev[i].end()),
			N = *rev[i].begin();

		tmax[i+n+1] = M;
		for(int j=(i+n+1)/2; j; j/=2) tmax[j] = std::max(tmax[j*2], tmax[j*2+1]);
		tmin[i+n+1] = N;
		for(int j=(i+n+1)/2; j; j/=2) tmin[j] = std::min(tmin[j*2], tmin[j*2+1]);

	}else{
		tmax[i+n+1] = 0;
		for(int j=(i+n+1)/2; j; j/=2) tmax[j] = std::max(tmax[j*2], tmax[j*2+1]);
		tmin[i+n+1] = n+1;
		for(int j=(i+n+1)/2; j; j/=2) tmin[j] = std::min(tmin[j*2], tmin[j*2+1]);
	}
}

void update(int i, int v){
	rev[ct[i]].erase(i); // all the indexes which have ct[i] votes

	update2(ct[i]);

	if(lastset && stillwork){
		if(i == last[0]){
			if(v > ct[i]) last[2] = v;
			else stillwork = 0;
		}
		if(i == last[1]){
			if(v > ct[i]) last[3] = v;
			else stillwork = 0;
		}
	};

	rev[v].insert(i);

	update2(v);

	ct[i] = v;

	int om = t[1];

	t[i+n] = ct[i];
	for(int j=(i+n)/2; j; j/=2) t[j] = std::max(t[j*2], t[j*2+1]);

	//if(t[1] < om) stillwork = 0;

	if(lastset && stillwork && t[1] > last[2]+last[3]) stillwork = 0;

	if(lastset && stillwork && v){
		int M = *(--rev[v].end()); // max val
		if(M > last[1] && v+last[2] >= t[1]){
			last[1] = M;
			last[3] = ct[M];
		}
		int N = *rev[v].begin(); // min val
		if(N < last[0] && v+last[3] >= t[1]){
			last[0] = M;
			last[2] = ct[N];
		}
	};

	if(lastset && stillwork){
		{
			int R = maxq(t[1]-v, n+1);
			if(R-i > last[1]-last[0])
				last = {i, R, ct[i], ct[R]};
		}
		{
			int R = minq(t[1]-v, n+1);
			if(i-R > last[1]-last[0])
				last = {R, i, ct[R], ct[i]};
		}
		{
			int R = maxq(t[1]-last[2], n+1);
			if(R-last[0] > last[1]-last[0])
				last = {last[0], R, last[2], ct[R]};
		}
		{
			int R = minq(t[1]-last[3], n+1);
			if(last[1]-R > last[1]-last[0])
				last = {R, last[1], ct[R], last[3]};
		}
	}
}

int main(){
	int q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i], --a[i];

	for(int i=0; i<n; ++i) ++ct[a[i]];
	for(int i=0; i<n; ++i) t[a[i]+n] = ct[a[i]];
	for(int i=n-1; i; --i) t[i] = std::max(t[i*2], t[i*2+1]);
	for(int i=0; i<n; ++i) rev[ct[i]].insert(i);
	for(int i=0; i<n*2+2; ++i) tmin[i] = n+1;
	for(int i=0; i<=n; ++i) update2(i);

	while(q--){
		{
			int i, x; std::cin >> i >> x, --i, --x;
			if(a[i] != x){
				update(a[i], ct[a[i]]-1);
				update(x, ct[x]+1);
				a[i] = x;

				// if(n <= 3000 && q <= 3000) stillwork = 0;
			}
		};

		if(stillwork) std::cout << last[1]-last[0] << '\n';
		else{
			int max = t[1], best = 0;

			for(int i=n-2; i>=0; --i){
				if(ct[i]){
					int R = maxq(max-ct[i], n+1);
					if(R-i > best){
						best = R-i;
						last = {i, R, ct[i], ct[R]};
						lastset = 1;
						stillwork = 1;
					}
				}
			}

			std::cout << best << '\n';
		}

		// std::cerr << last[0]+1 << ' ' << last[1]+1 << ' ' << last[2] << ' ' << last[3] << '\n';
	}
}
