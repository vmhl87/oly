#include <iostream>
#include <vector>
using namespace std;

namespace leg{
	vector<int> tree;
	vector<int> lazy;
	int n;
	void prop(int i){
		tree[i]=max(tree[i<<1]+lazy[i<<1],tree[i<<1|1]+lazy[i<<1|1]);
	}
	void push(int i){
		if(i<1)return;
		push(i>>1);
		if(i<n){
			lazy[i<<1]+=lazy[i];
			lazy[i<<1|1]+=lazy[i];
		}
		tree[i]+=lazy[i];
		lazy[i]=0;
		if(i<n)prop(i);
	}
	void init(vector<int> v){
		n=v.size();
		tree.resize(n<<1);
		lazy.resize(n<<1);
		for(int i=0;i<n;++i)tree[i+n]=v[i];
		for(int i=n-1;i>0;--i)prop(i);
	}
	void set(int l,int r,int i){
		l+=n;r+=n;
		while(l<r){
			if(l&1){
				lazy[l++]+=i;
				prop(l>>1);
			}
			if(r&1){
				lazy[--r]+=i;
				prop(r>>1);
			}
			l>>=1;r>>=1;
		}
		while(l){
			l>>=1;
			prop(l);
		}
	}
	int at(int i){
		i+=n;
		push(i);
		return tree[i];
	}
	int range(int l,int r){
		l+=n;r+=n;
		int ret=0;
		while(l<r){
			if(l&1){
				push(l);
				ret=max(ret,tree[l++]);
			}
			if(r&1){
				push(--r);
				ret=max(ret,tree[r]);
			}
			l>>=1;r>>=1;
		}
		return ret;
	}
}

int main(){
	int n,q;cin>>n>>q;
	int a[n];for(int i=0;i<n;++i)cin>>a[i];
	vector<int> v(n+1);v[0]=0;
	for(int i=0;i<n;++i){
		v[i+1]=v[i]+a[i];
	}
	for(int i:v)cout<<i<<' ';cout<<'\n';
	leg::init(v);
	while(q--){
		int t,b,c;cin>>t>>b>>c;
		if(t&1){
			b--;c-=a[b];a[b]+=c;
			leg::set(b+1,n+1,c);
//			for(int i=0;i<n+1;++i)cout<<leg::at(i)<<' ';cout<<'\n';
		}else{
			c++;
			cout<<max(0,leg::range(b,c)-leg::at(b-1))<<'\n';
			for(int i=0;i<n+1;++i)cout<<leg::tree[i+n+1]<<' ';cout<<'\n';
		}
	}
}
