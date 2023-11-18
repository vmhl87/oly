#include <stdio.h>
using namespace std;

int main(){
	freopen("taming.in","r",stdin);
	freopen("taming.out","w",stdout);
	int n;
	scanf("%d",&n);
	int run=0,t,last=0,max=1,min=1;
	scanf("%d",&last);
	for(int i=1;i<n;i++){
		scanf("%d",&t);
		if(t==-1){
			run++;
		}else{
			if(run>0){
				min++;max++;
				if(t==1+run+last){min--;max+=run;}
				else max+=(run-t);
			}else if(t==0){min++;max++;}
			run=0;last=t;
		}
	}
	printf("%d %d\n",min,max);
}
