#include <iostream>
#include <string>
using namespace std;

int main(){
	int w;cin>>w;
	int spaces[w];
	for(int i=0;i<w;i++)cin>>spaces[i];
	string str;cin>>str;
	int index=1,look=0;
	for(char c:str){
		cout<<c;
		if(spaces[look]==index){
			look++;cout<<' ';
		}
		index++;
	}
	cout<<'\n';
}
