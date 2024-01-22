#include <fstream>
#include <algorithm>
using namespace std;

typedef struct{
    int i;
    bool add=0;
}e;

bool cmp(e a,e b){
    if(a.i==b.i)return a.add;
    return a.i<b.i;
}

int main(){
    ifstream cin("stacking.in");
    ofstream cout("stacking.out");
    int n,m;cin>>n>>m;
    e inst[m*2];
    for(int i=0;i<m;i++){
        cin>>inst[i*2].i>>inst[i*2+1].i;
        inst[i*2].add=1;
    }
    sort(inst,inst+m*2,cmp);
    int stacks[n],ce=0,add=0;
    for(int i=0;i<n;i++){
        while(inst[ce].i==i+1&&inst[ce].add){
            add++;ce++;
        }
        stacks[i]=add;
        while(inst[ce].i==i+1&&!inst[ce].add){
            add--;ce++;
        }
    }
    sort(stacks,stacks+n);
    cout<<stacks[n/2]<<'\n';
}

