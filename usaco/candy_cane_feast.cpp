#include <iostream>
using namespace std;

typedef struct{
	long long h;
	int next;
}cow;

int main(){
	int n,m;
	cin>>n>>m;
	cow cows[n];
	for(int i=0;i<n;i++){
		cin>>cows[i].h;
		cows[i].next=i+1;
	}
	long long canes[m];
	for(int i=0;i<m;i++){
		cin>>canes[i];
	}
	for(int i=0;i<m;i++){
		// initially, the "start cow" and "start height" are 0
		int curr_cow=0;
		long long curr_height=0;
		while(canes[i]>0&&curr_cow<n){
			// find difference in height between current cow and last
			long long diff=cows[curr_cow].h-curr_height;
			// clip to reasonable height
			if(diff>canes[i])diff=canes[i];
			// modify cane
			canes[i]-=diff;
			// propagate current height
			curr_height=cows[curr_cow].h;
			// find next cow:
			int next_cow=cows[curr_cow].next;
			// make sure next cow is not too short
			while(next_cow<n&&cows[next_cow].h<=curr_height)
				next_cow=cows[next_cow].next;
			// update this cow's "next cow"
			cows[curr_cow].next=next_cow;
			// grow
			cows[curr_cow].h+=diff;
			// update current cow
			curr_cow=next_cow;
		}
	}
	for(cow c:cows)cout<<c.h<<'\n';
}
