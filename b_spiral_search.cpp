#include <iostream>
using namespace std;

#define INC if(x1>0&&y1>0&&x1<=w&&y1<=h)n++

int main(){
	int w,h;cin>>h>>w;
	int x1,x2,y1,y2;cin>>y1>>x1>>y2>>x2;
	int n=1,which_spiral=1,dir=0;
	int xbounds[2]={x1-1,x1+1},ybounds[2]={y1-1,y1+1};
	x1++;
	/*
	  dirs:
		23333
		2   0
		11110
	*/
	while(x1!=x2||y1!=y2){
		if(dir==0){
			INC;y1++;
			if(y1>ybounds[1]){
				y1--;x1--;dir=1;
			}
		}else if(dir==1){
			INC;x1--;
			if(x1<xbounds[0]){
				x1++;y1--;dir=2;
			}
		}else if(dir==2){
			INC;y1--;
			if(y1<ybounds[0]){
				y1++;x1++;dir=3;
			}
		}else{
			INC;x1++;
			if(x1>xbounds[1]){
				xbounds[0]--;xbounds[1]++;
				ybounds[0]--;ybounds[1]++;
				dir=0;
			}
		}
	}
	cout<<n+1<<'\n';
	return 0;
}
