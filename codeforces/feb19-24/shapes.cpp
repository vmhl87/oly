#include <iostream>
#include <string>
using namespace std;

void test_case(){
	int k;cin>>k;
	int min=-1,max=-1,oi=-1,oa=-1;
	char c;
	for(int i=0;i<k;i++){
		for(int j=0;j<k;j++){
			cin>>c;
			if(c&15){
				max=j;
				if(min<0)min=j;
			}
		}
		if(oi<0||oa<0||max<0||min<0){}else{
			if(max-min==oa-oi)cout<<"SQUARE\n";
			else cout<<"TRIANGLE\n";
			for(int j=i*k+k;j<k*k;j++)cin>>c;
			return;
		}
		oi=min;oa=max;
	}
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
