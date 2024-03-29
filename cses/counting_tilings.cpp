#include <iostream>
#include <stack>
using namespace std;

#define M 1000000007

int main(){
	int n,m;cin>>n>>m;
	long long a[1<<n],b[1<<n];
	for(int i=0;i<1<<n;++i)a[i]=0;
	stack<int> dfs;int len=1,p=0;
	dfs.push(1);
	while(dfs.size()){
		int top=dfs.top();
		if(len==n){
			dfs.pop();
			a[p]=1;
			// handle p
			continue;
		}
		if(len>n){
			dfs.pop();
			// handle p
			continue;
		}
		if(top==3){
			len-=2;dfs.pop();
			// handle p
		}else{
			len+=2;
			dfs.pop();dfs.push(2);
			dfs.push(1);
			// handle p
		}
	}
}
