/*

5 6
2 5     y,x
4 3

sector partitions:
  233333333
  2       0
  2   +   0
  2       0
  211111110

    | | | | |
- - - - - - |
- - - - + - |
- - - - - - |
- - + - - - |
- - - - - -

turning order:
  down
  right
  up
  left

*/

#include <iostream>
using namespace std;

#define SIG dx>0?(dy>0?dx>=dy:dx>=-dy):(dy>0?-dx>=dy:-dx>=-dy)
#define DLOG if(DEBUG)cout<<"- "<<ret<<'\n';
#define DEBUG 0

int max(int a,int b){
	if(a>b)return a;
	return b;
}

int min(int a,int b){
	if(a>b)return b;
	return a;
}

int main(){
	int w,h;cin>>h>>w;
	int x1,y1,x2,y2;
	cin>>y1>>x1>>y2>>x2;
	int dx=x2-x1,dy=y2-y1; //differences in x,y
	int dist=dy>0?dy:-dy; //distance to center (max side)
	if(SIG)dist=dx>0?dx:-dx;
	int sector=0;
	//sector
	if(SIG){
		if(dx>0)sector=0;
		else sector=2;
	}else{
		if(dy>0)sector=1;
		else sector=3;
	}
	if(dx>0&&dx==-dy)sector=3;
if(DEBUG){
	if(SIG)cout<<"XSIG\n";
	else cout<<"YSIG\n";
	cout<<dist<<' '<<sector<<'\n';
}
	int ret=0;
	//add core - width=(dist*2-1) - bounds=x+-(dist-1)
	ret+=(min(w,x1+dist-1)-max(1,x1-dist+1)+1)*
		 (min(h,y1+dist-1)-max(1,y1-dist+1)+1);
	//move through sectors
	if(sector==0){
		ret+=y2-max(1,y1-dist+1)+1;DLOG
	}else{
		if(w>=x1+dist)ret+=min(h,y1+dist)-max(1,y1-dist+1)+1;DLOG
		if(sector==1){
			ret+=min(w,x1+dist-1)-x2+1;DLOG
		}else{
			if(h>=y1+dist)ret+=min(w,x1+dist-1)-max(1,x1-dist+1)+1;DLOG
			if(sector==2){
				ret+=min(h,y1+dist)-y2+1;DLOG
			}else{ //clearly sector is 3
				if(x1>dist)ret+=min(h,y1+dist)-max(1,y1-dist)+1;DLOG
				ret+=x2-max(1,x1-dist+1)+1;DLOG
			}
		}
	}
	cout<<ret<<'\n';
	return 0;
}
