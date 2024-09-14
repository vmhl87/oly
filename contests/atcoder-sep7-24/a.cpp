#include <iostream>

int main(){
	int a, b; std::cin >> a >> b;
	if(a^b) std::cout << (a ? "Yes" : "No") << '\n';
	else std::cout << "Invalid\n";
}
