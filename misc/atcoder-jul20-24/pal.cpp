#include <iostream>

int n, k, res, str[26], make[10];

void permute(int i){
	if(i == n){
		bool non = 1;
		for(int j=0; j<=n-k; ++j){
			bool is = 1;
			for(int a=0; a<k/2; ++a)
				if(make[j+a] != make[j+k-1-a])
					is = 0;
			if(is){
				non = 0;
				break;
			}
		}
		if(non) ++res;
	}

	for(int j=0; j<26; ++j) if(str[j]){
		make[i] = j, --str[j];
		permute(i+1);
		++str[j];
	}
}

int main(){
	std::cin >> n >> k;

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		++str[c-'a'];
	}

	permute(0);

	std::cout << res << '\n';
}
