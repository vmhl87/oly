#include <iostream>

int d[100], n;

int ldp[100][1000];
bool lv[100][1000];
int lcost(int i, int h){
	if(i==0) return 0;

	if(lv[i][h]) return ldp[i][h];

	int best = -1;
	for(int j=0; j<i; ++j){
		int m = i-1, s = 0, e = 0;
		for(int k=j; k<i; ++k) s += d[k];
		while(s > e+h && m>=j) s -= d[m], e += d[m--];
		int part = e+lcost(j, e+h-s);
		if(best<0 || part<best) best = part;
	}

	lv[i][h] = 1;
	ldp[i][h] = best;
	return best;
}

int rdp[100][1000];
bool rv[100][1000];
int rcost(int i, int h){
	if(i==n-1) return 0;

	if(rv[i][h]) return rdp[i][h];

	int best = -1;
	for(int j=n-1; j>i; --j){
		int m = i, s = 0, e = 0;
		for(int k=j-1; k>=i; --k) s += d[k];
		while(s > e+h && m<=j-1) s -= d[m], e += d[m++];
		int part = e+rcost(j, e+h-s);
		if(best<0 || part<best) best = part;
	}

	rv[i][h] = 1;
	rdp[i][h] = best;
	return best;
}

int main(){
	std::cin >> n;
	for(int i=0; i<n-1; ++i) std::cin >> d[i];

	int best = -1;
	for(int i=0; i<n; ++i){
		int cons = lcost(i, 0) + rcost(i, 0);
		if(best<0 || cons<best) best = cons;
	}

	std::cout << best << '\n';
}
