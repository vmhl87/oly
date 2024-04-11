#include <iostream>
#include <vector>
using namespace std;

namespace leg{
	vector<int> tree;
	vector<int> lazy;
	int n;
	inline void prop(int i){
		tree[i]=max(tree[i<<1]+lazy[i<<1],tree[i<<1|1]+lazy[i<<1|1]);
	}
	void init(vector<int> v){
		n=v.size();
		tree.resize(n<<1);
		lazy.resize(n<<1);
		for(int i=0;i<n;++i)tree[i+n]=v[i];
		for(int i=n-1;i>0;--i)prop(i);
	}
	void push(int i){
		if(i<1)return;
		push(i>>1);
		lazy[i<<1]+=lazy[i];
		lazy[i<<1|1]+=lazy[i];
		tree[i]+=lazy[i];
		lazy[i]=0;
	}
	int at(int i){
		i+=n;
		push(i>>1);
		tree[i]+=lazy[i];
		lazy[i]=0;
		return tree[i];
	}
	void range(int l,int r,int i){
		l+=n;r+=n;
		while(l<r){
			if(l&1)lazy[l++]+=i;
			if(r&1)lazy[--r]+=i;
			l>>=1;r>>=1;
			prop(l);prop(r);
		}
		while(l){
			l>>=1;
			prop(l);
		}
	}
}

int main(){
	int n;cin>>n;
	vector<int> v(n);
	for(int i=0;i<n;++i)cin>>v[i];
	leg::init(v);
	for(;;){
		int t;cin>>t;
		if(t==1){
			int i;cin>>i;
			cout<<leg::at(i)<<'\n';
		}else if(t==2){
			int l,r,i;cin>>l>>r>>i;
			leg::range(l,r,i);
		}else if(t==3){
			for(int i=1;i<leg::tree.size();++i)cout<<i<<' ';cout<<'\n';
			for(int i=1;i<leg::tree.size();++i)cout<<leg::tree[i]<<' ';cout<<'\n';
			for(int i=1;i<leg::tree.size();++i)cout<<leg::lazy[i]<<' ';cout<<'\n';
		}else break;
	}
}
