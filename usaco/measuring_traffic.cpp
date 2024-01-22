#include <fstream>
#include <string>
using namespace std;

typedef struct{
	int min;
	int max;
	short t=0;
	bool ni=0;
	bool xi=0;
}rn;

void ur(rn *r,rn s){
	if(s.t-1==r->t){
		r->min+=s.min;
		r->max+=s.max;
	}else if(2-s.t==r->t){
		r->min-=s.max;
		r->max-=s.min;
	}else{
		if(r->ni){r->min=s.min;r->ni=0;}
		else if(s.min>r->min)r->min=s.min;
		if(r->xi){r->max=s.max;r->xi=0;}
		else if(s.max<r->max)r->max=s.max;
	}
	if(r->min<0)r->min=0;
	if(r->max<0)r->max=0;
}

int main(){
	ifstream cin("traffic.in");
	ofstream cout("traffic.out");
	int n,a,b;
	cin>>n;
	string c;
	rn s[n];
	for(int i=0;i<n;i++){
		cin>>c>>a>>b;
		if(c[1]=='n')s[i].t=1;
		else if(c[1]=='f')s[i].t=2;
		s[i].min=a;s[i].max=b;
	}
	rn r;
	r.ni=1;r.xi=1;r.t=1;
	for(int i=n-1;i>=0;i--)ur(&r,s[i]);
	cout<<r.min<<' '<<r.max<<'\n';
	r.ni=1;r.xi=1;r.t=0;
	for(int i=0;i<n;i++)ur(&r,s[i]);
	cout<<r.min<<' '<<r.max<<'\n';
}
