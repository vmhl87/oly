#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(){
	int n;cin>>n;
	int bessie[n],elsie[n],possible[n*2];
	for(int i=0;i<n*2;i++)possible[i]=i+1;
	string s;cin>>s;
	for(int i=3,buf=0,ptr=0;i<3+n+n;i++){
		buf+=s[i];
		if(i%2==1){
			elsie[ptr]=possible[buf%(n+n-ptr)+ptr];
			possible[buf%(n+n-ptr)+ptr]=-1;
			sort(possible,possible+n+n);
			buf=0;ptr++;
		}
	}
	cout<<"elsie ";for(int i:elsie)cout<<i<<' ';cout<<'\n';
	sort(elsie,elsie+n);
	for(int i=1,pt1=0,pt2=0;i<=n*2;i++){
		if(elsie[pt1]==i)pt1++;
		else{bessie[pt2]=i;pt2++;}
	}
	cout<<"bessie ";for(int i:bessie)cout<<i<<' ';cout<<'\n';
}
