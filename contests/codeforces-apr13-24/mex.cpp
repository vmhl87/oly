#include <iostream>
#include <stack>
using namespace std;

int l(int i){
	if(i==1)return 0;
	return (l(i-1)<<1) + i-1;
}

void ll(int off,int i){
	if(i==1)return;
	ll(off+1,i-1);
	cout<<off+1<<' '<<off+i-1<<'\n';
	for(int j=off+1;j<off+i-1;++j)cout<<j<<' '<<j<<'\n';
	ll(off,i-1);
}

int main(){
	int n;cin>>n;
	int a[n];for(int i=0;i<n;++i)cin>>a[i];
	int p[n+1];p[0]=0;
	for(int i=0;i<n;++i)p[i+1]=p[i]+a[i];
	int fin[n];bool set[n];
	for(int i=0;i<n;++i){
		fin[i]=a[i];set[i]=0;
	}
	stack<pair<int,int>> ops;
	int opc=0;
	// find subsegment
	for(int len=n;len>0;--len){
		int sq=len*len;
		// offset
		for(int off=0;off+len<=n;++off){
			// if alr set skip
			if(set[off]||set[off+len-1])continue;
			// subseg at off, len+off
			// total sum = p[off+len] - p[off]
			if(sq>p[off+len]-p[off]){
				ops.push(make_pair(off+1,len));
				opc+=len+l(len)+1;
				for(int i=off;i<len+off;++i)if(!set[i]){
					if(a[i]==0)--opc;
					set[i]=1;
					fin[i]=len;
				}
			}
		}
	}
	int sum=0;
	for(int i=0;i<n;++i)sum+=fin[i];
	cout<<sum<<' '<<opc<<'\n';
	while(ops.size()){
		pair<int,int> op=ops.top();ops.pop();
		for(int i=op.first;i<op.first+op.second;++i)if(a[i-1]){
			cout<<i<<' '<<i<<'\n';
		}
		ll(op.first,op.second);
		cout<<op.first<<' '<<op.first+op.second-1<<'\n';
	}
//	for(int i=0;i<n;++i)cout<<fin[i]<<' ';cout<<'\n';
}
