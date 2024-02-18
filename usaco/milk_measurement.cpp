#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

typedef struct{
	int day;
	int cow;
	int change;
}event;

bool comp_events(event a,event b){
	return a.day<b.day;
}

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
		
		int set(int oi,int v){
			int i=oi;
			int omax=tree[tree.size()-1].v,oct=tree[tree.size()-1].maxc;
			bool was_leader=(tree[i].v==omax);
			tree[i].v+=v;
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
			i=oi;
			if(was_leader){
				// leader steps down
				if(v<0){
					// if not only, always ret
					if(oct>1)return 1;
					// if was only:
					// if no longer leader: ret
					if(tree[i].v<tree[tree.size()-1].v)return 1;
					// if still leader, but not the only: ret
					if(tree[tree.size()-1].maxc>1)return 1;
					// otherwise it stays as leader
					return 0;
				// leader advances
				}else{
					// if not only, ret
					if(oct>1)return 1;
					// if only leader, still only leader
					return 0;
				}
			}
			// has to be non leader
			// non leader advances
			if(v>0){
				// if increased to old maximum level or past, ret
				if(tree[i].v>=omax)return 1;
				// otherwise no ret but implied
			}
			// non leader steps down
			return 0;
		}
		
		int min(){
			return tree[tree.size()-1].v;
		}
};

int main(){
	ifstream cin("measurement.in");
	ofstream cout("measurement.out");
	int n,g;cin>>n>>g;
	event events[n];
	map<int,int> indexmap;
	int index=0;
	for(int i=0;i<n;i++){
		int day,cow,change;
		char t;cin>>day>>cow>>t>>change;
		if(!indexmap.count(cow)){
			indexmap[cow]=index;
			index++;
		}
		events[i].day=day;events[i].cow=indexmap[cow];
		if(t=='-')events[i].change=-change;
		else events[i].change=change;
	}
	sort(events,events+n,comp_events);
	maxtree m(index+1,g);
	int ret=0;
	for(event e:events)
		ret+=m.set(e.cow,e.change);
	cout<<ret<<'\n';
}
