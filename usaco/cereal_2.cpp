#include <iostream>
using namespace std;

int main(){
	int n,m;cin>>n>>m;
	int cereal_counts[m],prefs[n][2];
	for(int &i:cereal_counts)i=0;
	for(int i=0;i<n;i++){
		cin>>prefs[i][0]>>prefs[i][1];
	}
	
}

/*

2 1
3 4
2 3
6 5
7 8
6 7
7 5
5 8

1 2 3 4 5 6 7 8
1 2 2 1 3 2 3 2

*/
