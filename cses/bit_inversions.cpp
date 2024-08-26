#include <iostream>
#include <string>

const int MAXN = 524288, N = 262144;

int in[MAXN], pre[MAXN], post[MAXN], all[MAXN], sz[MAXN];
int vin[MAXN], vpre[MAXN], vpost[MAXN], vall[MAXN];

inline void prop(int i){
	pre[i] = pre[i<<1];
	if(all[i<<1]) pre[i] = sz[i<<1] + pre[i<<1|1];

	post[i] = post[i<<1|1];
	if(all[i<<1|1]) post[i] = sz[i<<1|1] + post[i<<1];

	in[i] = std::max(post[i<<1]+pre[i<<1|1], std::max(
				in[i<<1], in[i<<1|1]));

	all[i] = all[i<<1] & all[i<<1|1];

	vpre[i] = vpre[i<<1];
	if(vall[i<<1]) vpre[i] = sz[i<<1] + vpre[i<<1|1];

	vpost[i] = vpost[i<<1|1];
	if(vall[i<<1|1]) vpost[i] = sz[i<<1|1] + vpost[i<<1];

	vin[i] = std::max(vpost[i<<1]+vpre[i<<1|1], std::max(
				vin[i<<1], vin[i<<1|1]));
	
	vall[i] = vall[i<<1] & vall[i<<1|1];

	sz[i] = sz[i<<1] + sz[i<<1|1];
}

int main(){
	std::string s; std::cin >> s;
	int m; std::cin >> m;
	int n = s.size();

	for(int i=0; i<n; ++i){
		in[i+N] = pre[i+N] = post[i+N] = all[i+N] = (s[i] == '1');
		vin[i+N] = vpre[i+N] = vpost[i+N] = vall[i+N] = (s[i] == '0');
		sz[i+N] = 1;
	}

	for(int i=N-1; i; --i) prop(i);

	for(int i=0; i<m; ++i){
		int a; std::cin >> a, --a;
		s[a] = (s[a] == '1' ? '0' : '1');
		in[a+N] = pre[a+N] = post[a+N] = all[a+N] = (s[a] == '1');
		vin[a+N] = vpre[a+N] = vpost[a+N] = vall[a+N] = (s[a] == '0');
		a = (a+N)/2; for(; a; a >>= 1) prop(a);
		std::cout << std::max(in[1], vin[1]) << " \n"[i==m-1];
	}
}
