#include <iostream>
#include <string>
using namespace std;

int main(){
	string a, b;
	getline(cin, a);
	getline(cin, b);
	int d[a.size()+1][b.size()+1]; d[0][0] = 0;
	for(int i=0; i<a.size(); ++i) d[i+1][0] = i+1;
	for(int i=0; i<b.size(); ++i) d[0][i+1] = i+1;
	for(int i=0; i<a.size(); ++i)
		for(int j=0; j<b.size(); ++j){
			d[i+1][j+1] = min(
					d[i][j] + (a[i] == b[j] ? 0 : 1),
					min(
						d[i][j+1] + 1,
						d[i+1][j] + 1
					)
				);
		}
	cout << d[a.size()][b.size()] << '\n';
}
