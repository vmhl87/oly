#include <iostream>
#include <string>

int main(){
	std::string a, b;
	std::cin >> a >> b;

	int diff = 0;
	for(int i=0; i!=a.size(); ++i) if(a[i] != b[i]) ++diff;

	std::cout << diff << '\n';

	for(int i=0; i!=a.size(); ++i) if(a[i] > b[i])
		a[i] = b[i], std::cout << a << '\n';

	for(int i=a.size(); i>=0; --i) if(a[i] < b[i])
		a[i] = b[i], std::cout << a << '\n';
}
