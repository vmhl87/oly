#include <iostream>
using namespace std;

int main(){
    int n_cows,moves,tmp,c1,c2;
    cin >> n_cows >> moves;
    int cows[n_cows],positions[n_cows];
    for(int i=0;i<n_cows;i++) cows[i]=i;
    for(int i=0;i<moves;i++){
        cin >> c1 >> c2;
        tmp = cows[c1];
        cows[c1] = cows[c2];
        cows[c2] = tmp;
    }
    for(int i=0;i<n_cows;i++)cout << cows[i] << '\n';
    cout << '\n';
    int bound=0;
    bool chosen[n_cows];
    while(bound<n_cows){
        for(int i=bound;i<=n_cows;i++){
            bound=i;
            if(cows[i]!=-1)break;
        }
        if(bound==n_cows)break;
        int cur=bound,ct=1;
        for(int i=0;i<n_cows;i++)chosen[i]=false;
        chosen[cur]=true;
        while(cows[cur]!=-1){
            chosen[cows[cur]]=true;
            tmp=cows[cur];
            cows[cur]=-1;
            cur=tmp;
            ct++;
        }
        for(int i=0;i<n_cows;i++){
            if(chosen[i]){
                positions[i]=ct;
            }
        }
    }
    for(int i=0;i<n_cows;i++){
        cout << positions[i] << '\n';
    }
    return 1;
}
