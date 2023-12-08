#include <iostream>
#include <algorithm>
using namespace std;

typedef struct {
	long long v;
	int i;
} p;

bool comp_p(p a,p b){
	return a.v<b.v;
}

int main(){
	int n;cin>>n;
	p reg[n+1];reg[0].v=0;reg[0].i=-1;
	long long sum=0,t;
	for(int i=0;i<n;i++){
		cin>>t;
		sum+=t;
		reg[i+1].v=sum;
		reg[i+1].i=i;
	}
	sort(reg,reg+n+1,comp_p);
for(p p:reg)cout<<p.v<<' ';cout<<'\n';
for(p p:reg)cout<<p.i<<' ';cout<<'\n';
	int s=0,e=n;
	long long max=0;bool set=1;
	for(int i=0;i<=n;i++){
		for(int j=n;j>=0;j--){
			long long t=reg[j].v-reg[i].v;
			if(reg[j].i<reg[i].i)t*=-1;
			if(i!=j&&(t>max||set)){
				max=t;set=0;break;
			}
		}
	}
	cout<<max<<'\n';
}

/*
ns
-1 3 -2 5 3 -5 2 2
reg
-1 2 0 5 8 3 5 7
-1 -> 8 = 9
*/
