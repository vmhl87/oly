#include <iostream>
#include <vector>
using namespace std;

class maxtree{
	private:
		struct node{
			int v;
			int next=-1;
			int maxc=1;
			int prev1,prev2;
		};
		
		int max(int a,int b){
			if(a<b)return b;
			return a;
		}
		
		int min(int a,int b){
			if(a>b)return b;
			return a;
		}
		
		node nn(int v){
			node t;t.v=v;
			return t;
		}
	
		int len;
		vector<node> tree;
	
	public:
		maxtree(int l,int g){
			len=l;
			tree.reserve(l*2);
			for(int i=0;i<l;i++)tree.push_back(nn(g));
		}
		
		void init(){
			int rmin=0,rmax=len;
			while(rmin<rmax-1){
				for(int i=rmin;i<rmax;i+=2){
					// add node linking i, i+1
					// if i == rmax-1: singly linked node 
					node t;
					if(i+1==rmax){
						t.v=tree[i].v;t.maxc=tree[i].maxc;
					}else{
						if(tree[i].v>tree[i+1].v){
							t.v=tree[i].v;t.maxc=tree[i].maxc;
						}else if(tree[i].v<tree[i+1].v){
							t.v=tree[i+1].v;t.maxc=tree[i+1].maxc;
						}else{
							t.v=tree[i].v;t.maxc=tree[i].maxc+tree[i+1].maxc;
						}
					}
					t.prev1=i;t.prev2=min(i+1,rmax-1);
					tree[i].next=tree.size();
					if(i+1<rmax)tree[i+1].next=tree.size();
					tree.push_back(t);
				}
				rmin=rmax;
				rmax=tree.size();
			}
		}
		
		int set(int i,int v){
			int omax=tree[tree.size()-1].v,oct=tree[tree.size()-1].maxc;
			tree[i].v=v;
			while(tree[i].next!=-1){
				i=tree[i].next;
				if(tree[i].prev1==tree[i].prev2){
					tree[i].v=tree[tree[i].prev1].v;
					tree[i].maxc=tree[tree[i].prev1].maxc;
				}else{
					int diff=tree[tree[i].prev1].v-tree[tree[i].prev2].v;
					if(diff>0){
						tree[i].v=tree[tree[i].prev1].v;
						tree[i].maxc=tree[tree[i].prev1].maxc;
					}else if(diff<0){
						tree[i].v=tree[tree[i].prev2].v;
						tree[i].maxc=tree[tree[i].prev2].maxc;
					}else{
						tree[i].v=tree[tree[i].prev1].v;
						tree[i].maxc=tree[tree[i].prev1].maxc
							+tree[tree[i].prev2].maxc;
					}
				}
			}
			return 0;
		}
		
		int min(){
			return tree[tree.size()-1].v;
		}
		
		int minc(){
			return tree[tree.size()-1].maxc;
		}
};

int main(){
	int n;cin>>n;
	maxtree m(n,0);
	m.init();
	for(int i=0;i<n;i++){
		int t;cin>>t;
		m.set(i,t);
	}
	cout<<m.min()<<' '<<m.minc()<<'\n';
	int i,d;cin>>i>>d;
	m.set(i,d);
	cout<<m.min()<<' '<<m.minc()<<'\n';
}
