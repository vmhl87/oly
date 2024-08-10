#include <iostream>
#include <map>

int main(){
	int q; std::cin >> q;
	std::map<int, int> balls;

	while(q--){
		int t; std::cin >> t;
		
		if(t==1){
			int x; std::cin >> x;
			++balls[x];
		}else if(t==2){
			int x; std::cin >> x;
			if(!(--balls[x])) balls.erase(x);
		}else{
			std::cout << balls.size() << '\n';
		}
	}
}
