#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct rect{
	int h=1;
	int w=1;
	bool operator==(const struct rect &o) const{
		return h==o.h&&w==o.w;
	}
	bool operator<(const struct rect &o) const{
		return h<o.h||(h==o.h&&w<o.w);
	}
};

int main(){
	map<struct rect,int> rects;
	vector<struct rect> all;
	int n;cin>>n;
	while(n-->0){
		int w,h;cin>>w>>h;
		if(h>w){int t=h-w;h-=t;w+=t;}
		struct rect tmp;
		tmp.w=w;tmp.h=h;
		while(h>0){
			int t=w%h;
			w=h;h=t;
		}
		tmp.w/=w;tmp.h/=w;
		if(rects.find(tmp)==rects.end()){
			rects[tmp]=1;
			all.push_back(tmp);
		}else rects[tmp]++;
	}
	int ret=0;
	for(struct rect h:all)
		ret+=(rects[h]*(rects[h]-1))/2;
	cout<<ret<<'\n';
	return 0;
}
