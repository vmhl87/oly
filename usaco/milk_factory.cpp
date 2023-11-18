#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main(){
	ifstream cin("factory.in");
	ofstream cout("factory.out");
	int n;cin>>n;
	bool graph[n][n]; //graph[a][b] = a can travel to b
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)graph[i][j]=false;
		graph[i][i]=true;
	}
	for(int i=1;i<n;i++){
		int a,b;cin>>a>>b;    //a can walk to all that b can
		for(int j=0;j<n;j++)  //all that can walk to a can walk to what b can
			for(int k=0;k<n;k++)
				if(graph[k][a-1])graph[k][j]|=graph[b-1][j];
	}
//for(int i=0;i<n;++i&&cout<<'\n')for(int j=0;j<n;j++)cout<<(graph[i][j]?'*':'-');
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			if(!graph[j][i])goto e;
		cout<<i+1<<'\n';return 0;
e: continue;
	}
	cout<<-1<<'\n';
	return 0;
}

/*
	int n,pn=1;cin>>n;for(int i=0;i<n;i++)pn*=2;pn--;
	int graph[n]; //graph[a]{binary b} = b can walk to a
	for(int i=0;i<n;i++){
		graph[i]=(1<<i);
	}
	for(int i=1;i<n;i++){
		int a,b;cin>>a>>b;    //all that can walk to a, can walk to b
		for(int j=0;j<n;j++)  //all that b can walk to, that which walk to a can
			if(graph[j]&(1<<b-1))graph[j]|=graph[a-1];
	}
//for(int i=0;i<n;++i&&cout<<'\n')
//for(int j=0;j<n;j++)cout<<(graph[j]&(1<<i)?'*':'-');
	for(int i=0;i<n;i++)
		if(graph[i]==pn){
			cout<<i+1<<'\n';return 0;
		}
	cout<<-1<<'\n';
*/
