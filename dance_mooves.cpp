#include <iostream>

//#include <unordered_set>
#include <bitset>
#define N_BITS 2000

using namespace std;

int main(){
    int n_cows,moves,tmp,c1,c2;
    cin >> n_cows >> moves;
    int cows[n_cows], m_iter[n_cows];
    
    //unordered_set<int> visits[n_cows];
    bitset<N_BITS> visits[n_cows];
    //for(int i=0;i<n_cows;i++) visits[i].insert(i);
    for(int i=0;i<n_cows;i++) visits[i].set(i);
    
    for(int i=0;i<n_cows;i++) cows[i]=i;
    for(int i=0;i<n_cows;i++) m_iter[i]=0;
    for(int i=0;i<moves;i++){
        cin >> c1 >> c2;
        
        //visits[cows[c1-1]].insert(c2-1);
        //visits[cows[c2-1]].insert(c1-1);
        visits[cows[c1-1]].set(c2-1);
        visits[cows[c2-1]].set(c1-1);
        
        tmp = cows[c1-1];
        cows[c1-1] = cows[c2-1];
        cows[c2-1] = tmp;
    }
    //for(int i=0;i<n_cows;i++){
    //    for(int j:visits[i])cout<<j;
    //    cout<<'\n';
    //}
    //for(int i=0;i<n_cows;i++)cout<<cows[i]<<'\n';return 1;
    int bound=0;
    bool chosen[n_cows];
    while(bound<n_cows){
        for(int i=bound;i<=n_cows;i++){
            bound=i;
            if(m_iter[i]==0)break;
        }
        if(bound==n_cows)break;
        //cout<<"checking "<<bound<<'\n';
        //for(int i=0;i<n_cows;i++)cout<<m_iter[i]<<'\n';
        int cur=bound,ct=1;
        for(int i=0;i<n_cows;i++)chosen[i]=false;
        chosen[cur]=true;
        while(!chosen[cows[cur]]){
            chosen[cows[cur]]=true;
            cur=cows[cur];
            ct++;
        }
        for(int i=0;i<n_cows;i++){
            if(chosen[i]){
                m_iter[i]=ct;
            }
        }
    }
    //for(int i=0;i<n_cows;i++)cout<<m_iter[i]<<'\n';return 1;
    for(int i=0;i<n_cows;i++){
        
        //unordered_set<int> visited;
        bitset<N_BITS> visited;
        
        int idx=i;
        for(int j=0;j<m_iter[i];j++){
            
            //for(int k:visits[idx])visited.insert(k);
            visited |= visits[idx];
            
            idx=cows[idx];
        }
        cout << visited.count() << '\n';
    }
    return 1;
}
