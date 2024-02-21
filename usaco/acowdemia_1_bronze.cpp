#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	int n,l;
    cin>>n>>l;
    
    int c[n];
    
    for(int i=0;i<n;i++){
        cin>>c[i];
    }

    sort(c,c+n);
    
    int h=0;

    int last=-1,count=1;

    // try possible h values
    for(int i=n-1;i>=0;i--){
        if(c[i]!=last){
            last=c[i];count=1;
        }else count++;
        int hv=n-i;
        // if current c-value cannot satisfy hv, we are finished
        if(c[i]+1<hv)break;
        // if current c-value needs extra citation, see if possible
        if(c[i]<hv){
            // all papers higher in count than c[i] should be fine, \
               so we only need to check if current count works
            if(l<count)break;
        }
        h=hv;
    }

    cout << h << '\n';
}
