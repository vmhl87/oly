#include <iostream>

const int N = 2e5, P = 1<<20;

int a[N], q1[P], q2[P];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int i=0; i<n; ++i) ++q1[a[i]], ++q2[a[i]];

	for(int x=0; x<20; ++x)
		for(int i=0; i<P; ++i)
			if(i & (1<<x)) q1[i] += q1[i ^ (1<<x)];

	for(int x=0; x<20; ++x)
		for(int i=P-1; i>=0; --i)
			if(!(i & (1<<x))) q2[i] += q2[i ^ (1<<x)];

	for(int i=0; i<n; ++i)
		std::cout << q1[a[i]] << ' ' << q2[a[i]] << ' ' << n-q1[((1<<20)-1)^a[i]] << '\n';
}
