// codeforces round 935 problem B

#include <iostream>
using namespace std;

int rhu(int i){
	if(!i)return 0;
	return 1+(i-1)/2;
}

int ds(int i,int n){
	int r=n-i-i;
	if(r<0)r=-r;
	return r;
}

int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		bool h[n];
		int lh=0,rh=0;
		for(int i=0;i<n;++i){
			char c;cin>>c;
			h[i]=c-'0';
			if(h[i])rh++;
		}
		int best=0,d=n*3;
		if(rh>=rhu(n))d=ds(0,n);
		for(int i=0;i<n;++i){
			if(h[i])rh--;
			else lh++;
			if(lh>=rhu(i+1)&&rh>=rhu(n-i-1)){
				int dd=ds(i+1,n);
				if(dd<d){
					best=i+1;d=dd;
				}
			}
		}
		cout<<best<<'\n';
	}
}
