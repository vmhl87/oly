#include <iostream>
#include <algorithm>
using namespace std;

typedef struct{
	long long h;
	long long a;
	int t;
}plant;

bool sort_plants(plant a,plant b){
	return a.t>b.t;
}

typedef struct{
	int min=0;
	int max=-1;
}rng;

void merge_ranges(rng *a,rng *b){
	if(b->min==-2)return;
	if(b->min>a->min)a->min=b->min;
	if(a->max==-1)a->max=b->max;
	else if(b->max>-1&&b->max<a->max)a->max=b->max;
}

rng curr_range(plant lower,plant upper){
	rng ret;
	if(lower.h>upper.h){
		if(lower.a<upper.a){
			ret.min=1+(lower.h-upper.h)/(upper.a-lower.a);
		}else{
			ret.min=-2;
		}
	}else if(lower.h<upper.h){
		if(lower.a>upper.a){
			ret.min=0;
			ret.max=(upper.h-lower.h-1)/(lower.a-upper.a);
		}else{
			ret.min=0;
		}
	}else{
		if(lower.a>upper.a){
			ret.min=-2;
		}else if(lower.a<upper.a){
			ret.min=1;
		}else{
			ret.min=-2;
		}
	}
	return ret;
}

void test_case(){
	int n;cin>>n;
	plant plants[n];
	for(int i=0;i<n;i++)cin>>plants[i].h;
	for(int i=0;i<n;i++)cin>>plants[i].a;
	for(int i=0;i<n;i++)cin>>plants[i].t;
	sort(plants,plants+n,sort_plants);
	rng iter;
	for(int i=1;i<n;i++){
		rng curr=curr_range(plants[i-1],plants[i]);
		merge_ranges(&iter,&curr);
		if(curr.min==-2||(iter.max<iter.min&&iter.max>-1)){
			cout<<-1<<'\n';
			return;
		}
	}
	cout<<iter.min<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
