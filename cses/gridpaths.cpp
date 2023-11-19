#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MOD 1000000007

typedef struct xy{
	int xy;
	int id;
} xy;

vector<xy> xs,ys;
long long ret;

bool compxy(xy a,xy b){
	return a.xy<b.xy;
}

int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int t,r;cin>>t>>r;
		xy x,y;x.id=i;y.id=i;x.xy=t;y.xy=r;
		xs.push_back(x);ys.push_back(y);
	}
	sort(xs.begin(),xs.end(),compxy);
	sort(ys.begin(),ys.end(),compxy);
	ret=1;
	for(int i=n*2;i>n;i--){
		ret*=(long long)i;
		if(ret>=MOD)ret%=MOD;
	}
	int c2=1,c2i=1;
	for(int i=n;i>1;i--){
		c2*=(long long)i;
		if(c2>=MOD)c2%=MOD;
	}
	for(int i=0;i<MOD;i++){
		if((c2*(long long)i)%MOD==1){
			c2i=i;break;
		}
	}
	ret=(ret*(long long)c2i)%MOD;
	cout<<ret<<'\n';
}
