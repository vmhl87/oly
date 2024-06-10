#include <iostream>

double pow(double a, int b){
	if(b < 0) return 1/pow(a, -b);

	double ans = 1;

	while(b > 0){
		if(b%2 == 1) ans *= a;
		a *= a;
		b /= 2;
	}

	return ans;
}

int main(){
	std::cout << pow(3, 2) << '\n';
	std::cout << pow(1.2, 5) << '\n';
	std::cout << pow(4, -2) << '\n';
}
