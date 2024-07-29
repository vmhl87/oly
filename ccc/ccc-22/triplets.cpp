#include <iostream>

using LL = long long;

int at[1000001], c;

int main(){
	int n; std::cin >> n >> c;

	for(int i=0; i<n; ++i){
		int l; std::cin >> l, ++at[l];
	}

	LL all = 0;

	LL one = 0, two = 0;
	for(int i=0; i<c; ++i) if(at[i]){
		all += at[i] * two;
		two += at[i] * one;
		one += at[i];
	}

	LL comp = 0;

	one = 0, two = 0;
	for(int i=0; i<c/2; ++i) if(at[i])
		two += at[i] * one, one += at[i];

	for(int i=0; i<c; ++i){
		int lead = (i+c/2)%c;
		if(at[lead]){
			comp += at[lead] * two;
			two += at[lead] * one;
			one += at[lead];
		}
		if(at[i]){
			one -= at[i];
			two -= at[i] * one;
		}
	}

	std::cout << all - comp << '\n';
}
