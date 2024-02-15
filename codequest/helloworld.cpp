#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;
	int n;cin>>n;
	getline(cin,s);
	while(n-->0){
		getline(cin,s);
		cout<<s<<'\n';
	}
}
