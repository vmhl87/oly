#include <algorithm>
#include <iostream>
#include <string>
#include <array>
 
const int N = 1e6;
 
std::string s;
int n;
 
std::array<int, 2> order[N];
int rev[N], tmp[N];
 
bool cmp(std::array<int, 2> a, std::array<int, 2> b){
	return rev[a[0]] == rev[b[0]] ? rev[a[1]] < rev[b[1]] : rev[a[0]] < rev[b[0]];
}
 
bool eq(std::array<int, 2> a, std::array<int, 2> b){
	return rev[a[0]] == rev[b[0]] && rev[a[1]] == rev[b[1]];
}
 
int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	std::cin >> s, n = s.length();
 
	for(int i=0; i<n; ++i) order[i] = {i, i}, rev[i] = s[i];
	std::sort(order, order+n, cmp);
 
	for(int p=0; p<22; ++p){
		int sz = 1<<p;
 
		for(int i=0, j=0; i<n; ++i){
			if(i && !eq(order[i-1], order[i])) ++j;
			tmp[order[i][0]] = j;
		}
 
		for(int i=0; i<n; ++i){
			rev[i] = tmp[i];
			order[i][1] = order[i][0]+sz;
			order[i][1] -= n * (order[i][1] >= n);
		}
 
		// std::sort(order, order+n, cmp);
 
		for(int i=0, last=0, val=0; i<=n; ++i){
			int idx = i == n ? -1 : rev[order[i][0]];
			if(idx != val){
				if(i != last+1) std::sort(order+last, order+i, cmp);
				last = i, val = idx;
			}
		}
	}
 
	for(int k=0, j=order[0][0]; k<n; ++k, j = (j+1)%n)
		std::cout << s[j];
	std::cout << '\n';
}
