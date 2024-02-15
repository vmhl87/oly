#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef struct{
	string a;
	string b;
}p;

int main(){
	int x,y,g,ret=0;
	cin>>x;
	p nos[x];
	for(int i=0;i<x;i++)
		cin>>nos[i].a>>nos[i].b;
	cin>>y;
	p yes[y];
	for(int i=0;i<y;i++)
		cin>>yes[i].a>>yes[i].b;
	cin>>g;
	map<string,int> loc;
	for(int i=0;i<g;i++)
		for(int j=0;j<3;j++){
			string t;cin>>t;
			loc[t]=i;
		}
	for(int i=0;i<x;i++)
		if(loc[nos[i].a]!=loc[nos[i].b])ret++;
	for(int i=0;i<y;i++)
		if(loc[yes[i].a]==loc[yes[i].b])ret++;
	cout<<ret<<'\n';
}

/*
3
A B
G L
J K
2
D F
D G
4
A C G
B D F
E H I
J K L
*/
