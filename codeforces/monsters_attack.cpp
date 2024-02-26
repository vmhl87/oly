#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

typedef struct monster{
	int x;
	int a;
	bool operator<(const monster o)const{
		return x<o.x;
	}
}monster;

void test_case(){
	int n,k;cin>>n>>k;
	monster m[n];
	for(int i=0;i<n;++i)
		cin>>m[i].a;
	for(int i=0;i<n;++i)
		cin>>m[i].x;
	sort(m,m+n);
	stack<monster> left;
	queue<monster> right;
	for(int i=0;i<n;++i){
		if(m[i].x<0){
			m[i].x=-m[i].x;
			left.push(m[i]);
		}else right.push(m[i]);
	}
	int time=0;
	while(!left.empty()||!right.empty()){
		if(!left.empty()&&left.top().x<=time)goto lose;
		if(!right.empty()&&right.front().x<=time)goto lose;
		int nk=k;
		while(nk){
			if(left.empty()){
				if(!right.empty()){
					if(right.front().a>nk){
						right.front().a-=nk;
						nk=0;
					}else{
						nk-=right.front().a;
						right.pop();
					}
				}else nk=0;
			}else if(right.empty()){
				if(!left.empty()){
					if(left.top().a>nk){
						left.top().a-=nk;
						nk=0;
					}else{
						nk-=left.top().a;
						left.pop();
					}
				}else nk=0;
			}else{
				if(left.top().x<right.front().x){
					if(left.top().a>nk){
						left.top().a-=nk;
						nk=0;
					}else{
						nk-=left.top().a;
						left.pop();
					}
				}else{
					if(right.front().a>nk){
						right.front().a-=nk;
						nk=0;
					}else{
						nk-=right.front().a;
						right.pop();
					}
				}
			}
		}
		time++;
	}
	cout<<"YES\n";
	return;
lose:
	cout<<"NO\n";
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
