#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct day{
	int price;
	int i;
	bool operator<(const day o)const{
		if(o.price==price)return o.i<i;
		return price<o.price;
	}
};

struct ev{
	int day;
	int count;
	ev(int d,int c):day(d),count(c){}
	bool operator<(const ev o)const{
		return day<o.day;
	}
};

void test_case(){
	int n,m,k;cin>>n>>m>>k;
	// store price and index of days
	day days[n];int pr[n];
	for(int i=0;i<n;++i){
		cin>>days[i].price;
		days[i].i=i;pr[i]=days[i].price;
	}
	// sort on price
	sort(days,days+n);
	int p=0;
	vector<ev> v;
	// while we still have to buy tickets, pick from the cheapest
	// possible day
	while(k){
		if(k<m){
			v.emplace_back(days[p].i,k);
			k=0;
		}else{
			v.emplace_back(days[p].i,m);
			k-=m;
		}
		++p;
	}
	// sort purchases by day to account properly for price increases
	sort(v.begin(),v.end());
	// count final
	long long ret=0,extra=0;
	for(ev i:v){
		ret+=(extra+(long long)pr[i.day])*(long long)i.count;
		extra+=(long long)i.count;
	}
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
