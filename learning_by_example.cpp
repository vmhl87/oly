#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define DEBUG 0

struct cow{
	int w;
	bool s;
};

bool compCows(struct cow a,struct cow b){
	return a.w<b.w;
}

struct event{
	int start;
	int end;
};

vector<struct event> events;

void add_event(int start,int end){
	if(start>end)return;
	struct event tmp;
	tmp.start=start;tmp.end=end;
	events.push_back(tmp);
}

int main(){
	if(!DEBUG){
		freopen("learning.in","r",stdin);
		freopen("learning.out","w",stdout);
	}
	int N,A,B;
	scanf("%d %d %d",&N,&A,&B);
	struct cow cows[N];
	for(int i=0;i<N;i++){
		char s='\n';int w;
		while(s=='\n')scanf("%c",&s);
		if(s=='S'){
			cows[i].s=true;
			scanf(" %d",&w);
		}else{
			cows[i].s=false;
			scanf("%c",&s);
			scanf(" %d",&w);
		}
		cows[i].w=w;
	}
	sort(cows,cows+N,compCows);
	int count=0;
	if(cows[0].s)add_event(cows[0].w,cows[0].w);
	for(int i=0;i<N-1;i++){
		int cl=cows[i].w+cows[i+1].w;
		if(cl%2==0){
			cl/=2;
			if(cows[i].s)add_event(cows[i].w+1,cl-1);
			if(cows[i].s||cows[i+1].s)add_event(cl,cl);
			if(cows[i+1].s)add_event(cl+1,cows[i+1].w);
		}else{
			cl=(cl+1)/2;
			if(cows[i].s)add_event(cows[i].w+1,cl-1);
			if(cows[i+1].s)add_event(cl,cows[i+1].w);
		}
	}
if(DEBUG)for(struct event e:events)
cout<<' '<<e.start<<'-'<<e.end<<'\n';
	if(events[0].start>A)count+=events[0].start-A;
	int t=events.size()-1;
	if(events[t].end<B)count+=B-events[t].end;
	for(struct event e:events){
		if(e.start<A&&e.end<A)continue;
		if(e.start>B&&e.end>B)break;
		if(e.start<A&&e.end>=A){	
			count+=(e.end-A+1);
		}else if(e.start<=B&&e.end>B){
			count+=(B-e.start+1);
		}else{
			count+=(e.end-e.start+1);
		}
	}
	printf("%d\n",count);
	return 0;
}
