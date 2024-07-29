#include <iostream>

using LL = long long;

int arr[20];

int main(){
	LL n; std::cin >> n;

	if(n == 1){
		std::cout << "0\n";
		return 0;
	}

	n -= 2;

	LL start = 1, end = 9;

	while(n >= (end-start+1)*2){
		n -= (end-start+1)*2;
		++end, start = end;
		end = (end*10) - 1;
	}

	int mid = 1;
	if(n >= end-start+1) mid = 0, n -= end-start+1;

	n += start;  // final
	
	int dig = 0;
	while(n) arr[dig++] = n%10, n /= 10;

	for(int i=dig-1; i+1; --i) std::cout << arr[i];
	for(int i=mid; i<dig; ++i) std::cout << arr[i];
	std::cout << '\n';
}
