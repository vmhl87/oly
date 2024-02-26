#include <iostream>
using namespace std;

void test_case(){
	long long x1,y1,x2,y2,x3,y3,x4,y4;
	cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
	x2-=x1;x3-=x1;x4-=x1;x1=0;
	y2-=y1;y3-=y1;y4-=y1;y1=0;
	long long lx1,ly1,lx2,ly2;
	lx1=y3*y2+x3*x2;
	ly1=y3*x2-x3*y2;
	lx2=y4*y2+x4*x2;
	ly2=y4*x2-x4*y2;
	x2=x2*x2+y2*y2;y2=0;
	if((ly1>0&&ly2>0)||(ly1<0&&ly2<0)){
		cout<<"NO\n";
		return;
	}
	if(x2<0){
		x2=-x2;
		lx1=-lx1;
		lx2=-lx2;
	}
	if(ly1==0){
		if(lx1>=0&&lx1<=x2)cout<<"YES\n";
		else cout<<"NO\n";
		return;
	}
	if(ly2==0){
		if(lx2>=0&&lx2<=x2)cout<<"YES\n";
		else cout<<"NO\n";
		return;
	}
	if(ly1<0)ly1=-ly1;
	if(ly2<0)ly2=-ly2;
	long long r=lx1*ly2+lx2*ly1;
	if(r<0){
		cout<<"NO\n";
		return;
	}
	if(r>x2*(ly2+ly1)){
		cout<<"NO\n";
		return;
	}
	cout<<"YES\n";
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
