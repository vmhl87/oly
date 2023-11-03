#include <iostream>
using namespace std;

int main(){
	int h[4][2];
	for(int i=0;i<4;i++)
		cin>>h[i][0]>>h[i][1];
	int d1=-1,d2=-1,c1=0,c2=0;
	for(int i=0;i<4;i++)
		for(int j=i+1;j<4;j++){
			int d=(h[i][0]-h[j][0])*(h[i][0]-h[j][0])+
				(h[i][1]-h[j][1])*(h[i][1]-h[j][1]);
			if(d1<0){d1=d;c1=1;}
			else if(d1==d)c1++;
			else if(d2<0){d2=d;c2=1;}
			else if(d2==d)c2++;
			else{
				cout<<0<<'\n';
				return 0;
			}
		}
	if(c1==4||c1==2||c1==6)cout<<1<<'\n';
	else cout<<0<<'\n';
	return 0;
}
