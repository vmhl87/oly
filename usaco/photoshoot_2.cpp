#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	int s[n],e[n],at[n];
	for(int i=0;i<n;i++)cin>>s[i];
	for(int i=0;i<n;i++)cin>>e[i];
	for(int i=0;i<n;i++){
		s[i]--;e[i]--;
	}
	for(int i=0;i<n;i++)at[s[i]]=i;
	int ret=0,c=n;
	for(int i=n-1;i>=0;i--){
		if(at[e[i]]>c)ret++;
		else c=at[e[i]];
	}
	cout<<ret<<'\n';
}

/*
input n, start, end
creat map array

smallest index = n
iterate backwards through ending positions
	if map[pos] > smallest index: increment ret
	else: smallest index = map[pos]
*/
