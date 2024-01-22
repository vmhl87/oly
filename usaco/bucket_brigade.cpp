#include <fstream>
using namespace std;

int abs(int x){
	if(x<0)return -x;
	return x;
}

int main(){
	ifstream cin("buckets.in");
	ofstream cout("buckets.out");
	int x1,x2,x3,y1,y2,y3;
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++){
			char c;cin>>c;
			if(c=='B'){
				x1=i;y1=j;
			}
			if(c=='L'){
				x2=i;y2=j;
			}
			if(c=='R'){
				x3=i;y3=j;
			}
		}
	int xtr=0;
	if(x1==x2&&x2==x3&&y1<y3&&y3<y2)xtr=2;
	if(x1==x2&&x2==x3&&y1>y3&&y3>y2)xtr=2;
	if(y1==y2&&y2==y3&&x1<x3&&x3<x2)xtr=2;
	if(y1==y2&&y2==y3&&x1>x3&&x3>x2)xtr=2;
	cout<<abs(x1-x2)+abs(y1-y2)-1+xtr;
}
