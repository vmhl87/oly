#include <bits/stdc++.h>
using namespace std;

typedef struct segtree{
	vector<pair<int,int>> tree;
	int n;
	void prop(int i){
		if(tree[i<<1].first>tree[i<<1|1].first){
			tree[i].first=tree[i<<1].first;
			tree[i].second=tree[i<<1].second;
		}else{
			tree[i].first=tree[i<<1|1].first;
			tree[i].second=tree[i<<1].second;
		}
	}
	segtree(vector<int> v):tree(v.size()*2),n(v.size()){
		for(int i=0;i<n;++i){
			tree[i+n].second=i;
			tree[i+n].first=v[i];
		}
		for(int i=n-1;i>0;--i)prop(i);
	}
	int top(){
		int ret=tree[1].second,
			i=tree[1].second;
		tree[i+n].first=0;i>>=1;
		while(i){
			prop(i);
			i>>=1;
		}
		return ret;
	}
	void decrease(int i){
		i+=n;tree[i].first--;i>>=1;
		while(i){
			prop(i);
			i>>=1;
		}
	}
}segtree;

int n;
pair<int, int> pts[301];
set<int> deg[301];
vector<vector<int>> tri;
vector<bool> done;

double slope(pair<int, int> p, pair<int, int> q){
    if(p.first == q.first){
        return DBL_MAX;
    }
    return (q.second - p.second)/(q.first - p.first);
}

int main(){
    cin >> n;

    for(int i = 0; i < n; i++)
        cin >> pts[i].first >> pts[i].second;

	int ptr = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                if(i != j && j != k && i != k){
                    if(slope(pts[i], pts[j]) == slope(pts[j], pts[k])){
                        deg[i].insert(ptr);
						deg[j].insert(ptr);
						deg[k].insert(ptr);
						vector<int> tr={i,j,k};
						tri.push_back(tr);
						done.push_back(0);
						ptr++;
                    }
                }
            }
        }
    }

	vector<int> v(n);
	for(int i=0;i<n;++i)v[i]=deg[i].size();

	segtree m(v);

	int ret;
	
	for(ret=0;;++ret){
		int a=m.top(), b=m.top(), c=m.top();
		if(deg[a].size()==0||deg[b].size()==0||deg[c].size()==0)break;
		for(int i:deg[a]){
			if(!done[i]){
				for(int j:tri[i])if(j!=a){
					if(deg[j].count(i)){
						m.decrease(j);
						deg[j].erase(i);
					}
				}
				done[i]=1;
			}
		}
		deg[a].clear();
		for(int i:deg[b]){
			if(!done[i]){
				for(int j:tri[i])if(j!=b){
					if(deg[j].count(i)){
						m.decrease(j);
						deg[j].erase(i);
					}
				}
				done[i]=1;
			}
		}
		deg[b].clear();
		for(int i:deg[c]){
			if(!done[i]){
				for(int j:tri[i])if(j!=c){
					if(deg[j].count(i)){
						m.decrease(j);
						deg[j].erase(i);
					}
				}
				done[i]=1;
			}
		}
		deg[c].clear();
	}

	cout<<ret<<'\n';
}
