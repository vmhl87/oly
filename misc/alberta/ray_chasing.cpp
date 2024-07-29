#include <iostream>
using namespace std;

int main(){
	int x1,y1,x2,y2;
	cin>>x1>>x2>>y1>>y2;
	int xs,ys,xr,yr;
	cin>>xs>>ys>>xr>>yr;
	// bottom top left right
	bool hits[4]={0,0,0,0};
	if(xr<xs){
		if(yr<ys){
			int s=(ys-y1)*(xs-xr),
				i=(ys-yr)*(xs-x1);
			if(s>i)hits[2]=1;
			else if(s==i){
				hits[2]=1;
				hits[0]=1;
			}else hits[0]=1;
		}else{
			int s=(y2-ys)*(xs-xr),
				i=(yr-ys)*(xs-x1);
			if(s>i)hits[2]=1;
			else if(s==i){
				hits[2]=1;
				hits[1]=1;
			}else hits[1]=1;
		}
	}else if(xr>xs){
		if(yr<ys){
			int s=(ys-y1)*(xr-xs),
				i=(ys-yr)*(x2-xs);
			if(s>i)hits[3]=1;
			else if(s==i){
				hits[3]=1;
				hits[0]=1;
			}else hits[0]=1;
		}else{
			int s=(y2-ys)*(xr-xs),
				i=(yr-ys)*(x2-xs);
			if(s>i)hits[3]=1;
			else if(s==i){
				hits[3]=1;
				hits[1]=1;
			}else hits[1]=1;
		}
	}else{
		if(yr<ys)hits[0]=1;
		else hits[1]=1;
	}
	bool p=0;
	for(int i=0;i<4;++i){
		if(hits[i]){
			if(p)cout<<'-';
			if(i==0)cout<<"bottom";
			if(i==1)cout<<"top";
			if(i==2)cout<<"left";
			if(i==3)cout<<"right";
			p=1;
		}
	}
	cout<<'\n';
}
