#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class segtree{
	private:
		struct node{
			int v;
			int next=-1;
			int pre1,pre2;
			int l;
			int u;
		};
		int len;
		vector<node> tree;
		void join(int i,int j){
			node t;t.v=tree[i].v;
			if(j!=i)t.v+=tree[j].v;
			t.l=tree[i].l;t.u=tree[j].u;
			t.pre1=i;t.pre2=j;
			tree[i].next=tree.size();
			tree[j].next=tree.size();
			tree.push_back(t);
		}
		bool on_range(int l1,int u1,int l2,int u2){
			return (u1<u2?u1:u2)>(l1>l2?l1:l2);
		}
		bool in_range(int l1,int u1,int l2,int u2){
			return l1>=l2&&u1<=u2;
		}
	public:
		segtree(vector<int> v){
			len=v.size();
			tree.reserve(len*2);
			for(int i=0;i<len;++i){
				node t;t.v=v[i];
				t.l=i;t.u=i+1;
				tree.push_back(t);
			}
			int l=0,u=len;
			while(l<u-1){
				for(int i=l;i<u;i+=2){
					int j=i+1;if(j==u)j=i;
					join(i,j);
				}
				l=u;u=tree.size();
			}
		}
		void update(int i,int v){
			tree[i].v=v;
			while(tree[i].next+1){
				i=tree[i].next;
				tree[i].v=tree[tree[i].pre1].v;
				if(tree[i].pre1!=tree[i].pre2)
					tree[i].v+=tree[tree[i].pre2].v;
			}
		}
		int range(int l,int u){
			int ret=0;
			queue<int> q;
			q.push(tree.size()-1);
			while(!q.empty()){
				int n=q.front();q.pop();
				if(in_range(tree[n].l,tree[n].u,l,u)){
					ret+=tree[n].v;
				}else if(on_range(tree[n].l,tree[n].u,l,u)){
					q.push(tree[n].pre1);
					q.push(tree[n].pre2);
				}
			}
			return ret;
		}
};

int main(){
	int n;cin>>n;
	vector<int> ns(n);
	for(int i=0;i<n;++i)cin>>ns[i];
	segtree m(ns);
	for(;;){
		int t;cin>>t;
		if(!t)break;
		if(t-1){
			int l,u;cin>>l>>u;
			cout<<m.range(l,u)<<'\n';
		}else{
			int i,v;cin>>i>>v;
			m.update(i,v);
		}
	}
}
