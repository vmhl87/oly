#include <iostream>

char a[200];

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i) std::cin >> a[i];

	if(!(n&1)) goto done;

	for(int l=0, r=n-1; l<r; ++l, --r)
		if(a[l] != '1' || a[r] != '2') goto done;

	if(a[(n+1)/2-1] != '/') goto done;

	std::cout << "Yes\n", exit(0);

done:
	std::cout << "No\n";
}
