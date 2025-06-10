#include <iostream>
using namespace std;

#define f(m) for(i=0; i<n; ++i) cout << m << " \n"[i==n-1];
int n, a, b, j, t, i;

void r(){
	cin >> n >> a >> b;

	if((j=a+b) <= n && (a*b || !(a+b))){
		cout << "YES\n";

		f(i+1);
		f(1+(i<j ? (i+a)%j : i));

	}else std::cout << "NO\n";
}

main(){
	cin >> t;
	while(t--) r();
}
