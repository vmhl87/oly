#include <iostream>
#include <set>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;cin>>n;
	set<int> s;
	while(n--){
		int t;cin>>t;
		s.insert(t);
	}
	cout<<s.size()<<'\n';
}
