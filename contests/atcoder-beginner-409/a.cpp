#include <iostream>

char a[200], b[200];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<n; ++i) std::cin >> b[i];

	for(int i=0; i<n; ++i){
		if(a[i] == b[i] && a[i] == 'o'){
			std::cout << "Yes\n";
			return 0;
		}
	}

	std::cout << "No\n";
}
