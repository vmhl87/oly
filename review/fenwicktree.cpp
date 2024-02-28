#include <iostream>
#include <vector>
using namespace std;

typedef struct fenwicktree{
	vector<int> tree;
	int n;
    int sum(int i){
        int ret=0;
        while(i>0){
            ret+=tree[i-1];
            i=(i&(i+1))-1;
        }
        return ret;
    }
    fenwicktree(vector<int> v):tree(v.size()),n(v.size()){
        for(int i=0;i<n;++i)tree[i]=v[i]+sum(i);
    }
    int range(int l,int r){
        return sum(r)-sum(l-1);
    }
}fenwicktree;

int main(){
    int n;cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;++i)
        cin>>v[i];
    fenwicktree m(v);
    for(;;){
        int t;cin>>t;
        if(!t)break;
        int b;cin>>b;
        cout<<m.range(t,b)<<'\n';
    }
}
