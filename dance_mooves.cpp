#include <iostream>
#include <set>
using namespace std;

int main(){
    int n,moves,tmp,c1,c2;
    cin >> n >> moves;
    int cows[n], ret[n];
    set<int> visits[n];
    for(int i=0;i<n;i++){
        visits[i].insert(i);
        cows[i]=i;
        ret[i]=0;
    }
    for(int i=0;i<moves;i++){
        cin >> c1 >> c2;
        visits[cows[c1-1]].insert(c2-1);
        visits[cows[c2-1]].insert(c1-1);
        swap(cows[c1-1], cows[c2-1]);
    }
    int bound=0;
    bool chosen[n];
    while(bound<n){
        for(int i=bound;i<=n;i++){
            bound=i;
            if(ret[i]==0)break;
        }
        if(bound==n)break;
        //cout<<"checking "<<bound<<'\n';
        //for(int i=0;i<n;i++)cout<<m_iter[i]<<'\n';
        int cur=bound,ct=0;
        for(int i=0;i<n;i++)chosen[i]=false;
        chosen[cur]=true;
        while(!chosen[cows[cur]]){
            chosen[cows[cur]]=true;
            cur=cows[cur];
        }
        set<int> all_pos;
        for(int i=0;i<n;i++)
        	if(chosen[i])
        		for(int c:visits[i])all_pos.insert(c);
		ct=all_pos.size();
        for(int i=0;i<n;i++)
            if(chosen[i])ret[i]=ct;
    }
    for(int i=0;i<n;i++)cout<<ret[i]<<'\n';
    return 1;
}
