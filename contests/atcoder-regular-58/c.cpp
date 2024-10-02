#include <iostream>
#include <vector>

int work[10];

int main(){
	int n, k; std::cin >> n >> k;

	for(int i=0; i<10; ++i) work[i] = 1;
	for(int i=0; i<k; ++i){
		int a; std::cin >> a, work[a] = 0;
	}

	std::vector<int> choice;

	while(n){
		int t = n%10, f = 0; n /= 10;

		for(int i=t; i<10; ++i) if(work[i]){
			if(i != t){
				for(int j=0; j<10; ++j) if(work[j]){
					for(int &x : choice) x = j;
					break;
				}
			}
			choice.push_back(i), f = 1;
			break;
		}

		if(!f){
			++n, choice.push_back(0);

			for(int i=0; i<10; ++i) if(work[i]){
				for(int &x : choice) x = i;
				break;
			}
		}
	}

	while(choice.size()) std::cout << choice.back(), choice.pop_back();
	std::cout << '\n';
}
