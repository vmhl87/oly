#include <unordered_set>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using usi=unordered_set<int>;

class segtree{
	private:
		struct node{
			usi dist;
			int val;
			int next=-1;
			int pre1,pre2;
			int l,u;
		};
		int len;
		vector<node> tree;
		bool in_range(int i,int l,int u){
			return tree[i].l>=l&&tree[i].u<=u;
		}
		bool on_range(int i,int l,int u){
			return tree[i].u>l&&tree[i].l<u
				&&u>tree[i].l&&l<tree[i].u;
		}
	public:
		segtree(int n){
			len=n;
			tree.reserve(n*2);
			for(int i=0;i<n;++i){
				node t;cin>>t.val;
				t.l=i;t.u=i+1;
				t.dist.insert(t.val);
				tree.push_back(t);
			}
			int l=0,u=n;
			while(l<u-1){
				for(int i=l;i<u;i+=2){
					int j=i+1;if(j==u)j=i;
					node t;t.pre1=i;t.pre2=j;
					t.l=tree[i].l;t.u=tree[j].u;
					for(int x:tree[i].dist)t.dist.insert(x);
					for(int x:tree[j].dist)t.dist.insert(x);
					tree[i].next=tree.size();
					tree[j].next=tree.size();
					tree.push_back(t);
				}
				l=u;u=tree.size();
			}
		}
		/*
		void rem(int i,int v){
			tree[i].dist.erase(v);
			while(tree[i].next+1){
				i=tree[i].next;
				if(!tree[tree[i].pre1].dist.count(v)&&
					!tree[tree[i].pre2].dist.count(v))
					tree[i].dist.erase(v);
			}
		}
		void add(int i,int v){
			tree[i].dist.insert(v);
			while(tree[i].next+1){
				i=tree[i].next;
				tree[i].dist.insert(v);
			}
		}
		void set(int i,int v){
			rem(i,tree[i].val);
			tree[i].val=v;
			add(i,v);
		}
		*/
		int range(int l,int u){
			usi ret;
			queue<int> q;
			q.push(tree.size()-1);
			while(!q.empty()){
				int n=q.front();q.pop();
				if(in_range(n,l,u)){
					for(int x:tree[n].dist)
						ret.insert(x);
				}else if(on_range(n,l,u)){
					q.push(tree[n].pre1);
					q.push(tree[n].pre2);
				}
			}
			return ret.size();
		}
};

int main(){
	int n,q;cin>>n>>q;
	segtree m(n);
	while(q-->0){
		int a,b;cin>>a>>b;
		cout<<m.range(a-1,b)<<'\n';
	}
}
