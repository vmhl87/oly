#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class segtree{
	private:
		struct node{
			int count;
			int next=-1;
			int p1,p2,p3,p4;
			int l1,l2,u1,u2;
		};
		int len;
		vector<node> tree;
		void merge(int l,int rows,int i,int j,int i2,int j2){
			int ids[4]={
				l+i*rows+j,
				l+i*rows+j2,
				l+i2*rows+j,
				l+i2*rows+j2
			};
			node t;
			t.l1=tree[ids[0]].l1;t.l2=tree[ids[0]].l2;
			t.u1=tree[ids[3]].u1;t.u2=tree[ids[3]].u2;
			t.count=tree[ids[0]].count;
			if(j2!=j)t.count+=tree[ids[1]].count;
			if(i2!=i){
				t.count+=tree[ids[2]].count;
				if(j2!=j)t.count+=tree[ids[3]].count;
			}
			for(int i:ids)tree[i].next=tree.size();
			t.p1=ids[0];t.p2=ids[1];t.p3=ids[2];t.p4=ids[3];
			tree.push_back(t);
		}
		bool in_range(int n,int l1,int l2,int u1,int u2){
			return tree[n].l1>=l1&&tree[n].l2>=l2
				&&tree[n].u1<=u1&&tree[n].u2<=u2;
		}
		bool on_range(int n,int l1,int l2,int u1,int u2){
			return tree[n].u1>l1&&tree[n].u2>l2
				&&tree[n].l1<u1&&tree[n].l2<u2;
		}
	public:
		segtree(int n){
			len=n*n;
			tree.reserve((len*4)/3);
			for(int i=0;i<n;++i)
				for(int j=0;j<n;++j){
					node t;
					t.l1=i;t.u1=i+1;
					t.l2=j;t.u2=j+1;
					char c;cin>>c;
					t.count=(c=='*');
					tree.push_back(t);
				}
			int l=0,u=len,rows=n;
			while(l<u-1){
				for(int i=0;i<rows;i+=2)
					for(int j=0;j<rows;j+=2){
						int i2=i+1,j2=j+1;
						if(i2==rows)i2=i;
						if(j2==rows)j2=j;
						merge(l,rows,i,j,i2,j2);
					}
				l=u;u=tree.size();rows=(rows+1)/2;
			}
			len=n;
		}
		void flip(int x,int y){
			int ptr=x+y*len;
			tree[ptr].count^=1;
			while(tree[ptr].next+1){
				ptr=tree[ptr].next;
				tree[ptr].count=tree[tree[ptr].p1].count;
				if(tree[ptr].p1!=tree[ptr].p2)
					tree[ptr].count+=tree[tree[ptr].p2].count;
				if(tree[ptr].p1!=tree[ptr].p3){
					tree[ptr].count+=tree[tree[ptr].p3].count;
					if(tree[ptr].p1!=tree[ptr].p2)
						tree[ptr].count+=tree[tree[ptr].p4].count;
				}
			}
		}
		int range(int l1,int l2,int u1,int u2){
			int ret=0;
			queue<int> q;
			q.push(tree.size()-1);
			while(!q.empty()){
				int n=q.front();q.pop();
				if(in_range(n,l1,l2,u1,u2)){
					ret+=tree[n].count;
				}else if(on_range(n,l1,l2,u1,u2)){
					q.push(tree[n].p1);
					q.push(tree[n].p2);
					q.push(tree[n].p3);
					q.push(tree[n].p4);
				}
			}
			return ret;
		}
};

int main(){
	int n,q;cin>>n>>q;
	segtree m(n);
	while(q-->0){
		int t;cin>>t;
		if(t-1){
			int x1,y1,x2,y2;cin>>y1>>x1>>y2>>x2;
			cout<<m.range(y1-1,x1-1,y2,x2)<<'\n';
		}else{
			int x,y;cin>>y>>x;
			m.flip(x-1,y-1);
		}
	}
}
