#include <iostream>

int q[100], r[100];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> q[i] >> r[i];

	int x; std::cin >> x;
	while(x--){
		int t, d; std::cin >> t >> d, --t;
		int rem = d-r[t];
		if(rem <= 0)
			rem = (rem / q[t]) * q[t];
		else
			rem = (1 + (rem - 1) / q[t]) * q[t];
		std::cout << r[t] + rem << '\n';
	}
}
