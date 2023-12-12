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
	sort(reg,reg+n,comp_p);
//for(p p:reg)cout<<p.v<<' ';cout<<'\n';
//for(p p:reg)cout<<p.i<<' ';cout<<'\n';
	int s=0,e=n;
	long long max=0;bool set=1;
	if(reg[0].i<reg[e].i){
		max=reg[e].v-reg[0].v;
		set=0;
	}
	while(s<n&&e>0){
		bool c=0;
		if(e==0){s++;c=1;}
		else if(s==n)e--;
		else if((reg[s+1].v-reg[s].v)<(reg[e].v-reg[e-1].v)){s++;c=1;}
		else e--;
		if(reg[s].i<reg[e].i){
			if(max<(reg[e].v-reg[s].v)||set){
				max=reg[e].v-reg[s].v;
				set=0;
			}
		}else if(reg[s].i>reg[e].i){
			if(max<(reg[s].v-reg[e].v)||set){
				max=reg[s].v-reg[e].v;
				set=0;
			}
		}
		int r=e;if(c)r=s-1;
		if(reg[r].i<reg[r+1].i){
			if(max<(reg[r+1].v-reg[r].v)||set){
				max=reg[r+1].v-reg[r].v;
				set=0;
			}
		}else{
			if(max<(reg[r].v-reg[r+1].v)||set){
				max=reg[r].v-reg[r+1].v;
				set=0;
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
