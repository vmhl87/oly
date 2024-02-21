#include <iostream>
#include <vector>
using namespace std;

class segtree{
	private:
		struct node{
			int v=0;
			int i;
			int next=-1;
			int pre1,pre2;
		};
		vector<node> tree;

	public:
		segtree(int n){
			tree.reserve(n);
			for(int i=0;i<n;i++){
				node t;t.i=i;
				tree.push_back(t);
			}
			int min=0,max=n;
			while(min<max-1){
				for(int i=min;i<max;i+=2){
					int j=i+1;if(j>=max)j=i;
					node t;
					if(tree[i].v>tree[j].v){
						t.v=tree[i].v;
						t.i=tree[i].i;
					}else{
						t.v=tree[j].v;
						t.i=tree[j].i;
					}
					t.pre1=i;t.pre2=j;
					tree[i].next=tree.size();
					tree[j].next=tree.size();
					tree.push_back(t);
				}
				min=max;max=tree.size();
			}
		}

		void set(int i,int v){
			tree[i].v=v;
			while(tree[i].next+1){
				i=tree[i].next;
				if(tree[tree[i].pre1].v>tree[tree[i].pre2].v){
					tree[i].v=tree[tree[i].pre1].v;
					tree[i].i=tree[tree[i].pre1].i;
				}else{
					tree[i].v=tree[tree[i].pre2].v;
					tree[i].i=tree[tree[i].pre2].i;
				}
			}
		}

		int top(){
			return tree[tree.size()-1].i;
		}

		int get(int i){
			return tree[i].v;
		}
};

int main(){
	int n;cin>>n;
	int ret=0;
	segtree m(n);
	for(int i=0;i<n;i++){
		int c;
		cin>>c;
		if(c<m.get(m.top())){
cout<<"appending "<<c<<" to tower "<<m.top()<<" with value "<<m.get(m.top())<<'\n';
			m.set(m.top(),c);
		}else{
cout<<"making a new tower to hold "<<c<<'\n';
			m.set(i,c);
			ret++;
		}
	}
	cout<<ret<<'\n';
}
