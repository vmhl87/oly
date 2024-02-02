#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	long long m[n],min=-1,mod;
	for(int i=0;i<n;i++){
		cin>>m[i];
		if(m[i]<min||min<0)min=m[i];
	}
	long long ret=6;
	for(int l=min/4;l>3;l--){
		int n1=-1,n2=-1,n3=-1;
		for(int i=0;i<n;i++){
			mod=m[i]%l;
			if(mod!=n1){
				if(n1<0)n1=mod;
				else{
					if(mod!=n2){
						if(n2<0)n2=mod;
						else{
							if(mod!=n3){
								if(n3<0)n3=mod;
								else goto failed;
							}
						}
					}
				}
			}
		}
		ret+=l;
		failed:
		continue;
	}
	cout<<ret<<'\n';
}
