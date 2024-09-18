#include "gondola.h"

#include <iostream>
#include <set>
#include <map>

int valid(int n, int inputSeq[]){
	std::set<int> seen;
	for(int i=0; i<n; ++i){
		if(seen.count(inputSeq[i])) return 0;
		seen.insert(inputSeq[i]);
	}

	int offset = -1;

	for(int i=0; i<n; ++i){
		if(inputSeq[i] <= n){
			if(offset == -1){
				offset = (inputSeq[i]-i+n)%n;
			}else{
				int check = (inputSeq[i]-i+n)%n;
				if(check != offset) return 0;
			}
		}
	}

	return 1;
}

//----------------------

int replacement(int n, int gondolaSeq[], int replacementSeq[]){
	int max = n;
	for(int i=0; i<n; ++i) max = std::max(max, gondolaSeq[i]);

	std::map<int, int> invert;
	for(int i=0; i<n; ++i) invert[gondolaSeq[i]] = i;

	int offset = 0;
	for(int i=0; i<n; ++i) if(gondolaSeq[i] <= n) offset = (gondolaSeq[i]-i-1+n)%n;

	for(int i=0; i<n; ++i) gondolaSeq[i] = 1+(i+offset)%n;

	for(int i=n+1; i<=max; ++i){
		if(invert.count(i)){
			replacementSeq[i-n-1] = gondolaSeq[invert[i]];
			gondolaSeq[invert[i]] = i;
		}else{
			replacementSeq[i-n-1] = gondolaSeq[invert[max]];
			gondolaSeq[invert[max]] = i;
		}
	}

	return max-n;
}

//----------------------

using ll = long long;

const int m = 1000000009;

ll exp(ll base, int pow){
	ll res = 1;
	for(; pow; pow/=2){
		if(pow&1) res = res * base % m;
		base = base * base % m;
	}
	return res;
}

int countReplacement(int n, int inputSeq[]){
	if(!valid(n, inputSeq)) return 0;

	ll res = n;

	int max = n;
	for(int i=0; i<n; ++i) max = std::max(max, inputSeq[i]);

	std::set<int> seen;
	for(int i=0; i<n; ++i){
		if(inputSeq[i] > n) seen.insert(inputSeq[i]);
		else res = 1;
	}

	int remain = seen.size(), last = n;

	for(int x : seen){
		res = res * exp(remain, x-last-1) % m;
		last = x, --remain;
	}

	return res;
}
