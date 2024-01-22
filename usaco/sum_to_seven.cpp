#include <fstream>
using namespace std;

int main(){
    ifstream cin("div7.in");
    ofstream cout("div7.out");
    int n;cin>>n;
    int max[7],min[7];
    for(int i=0;i<7;i++){
        max[i]=-1;
        min[i]=-1;
    }
    int sum=0;
    while(n-->0){
        int a;cin>>a;
        sum=(sum+a)%7;
        max[sum]=n;
        if(min[sum]<0)min[sum]=n;
    }
    int mx=0;
    for(int i=0;i<7;i++)
        if(min[i]-max[i]>mx)
            mx=min[i]-max[i];
    cout<<mx<<'\n';
}

