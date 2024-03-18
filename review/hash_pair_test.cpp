#include <unordered_map>
#include <iostream>
using namespace std;

struct hash_pair{
	template<class t1,class t2>
	size_t operator()(const pair<t1,t2> &p)const{
		auto h1=hash<t1>{}(p.first),
			 h2=hash<t2>{}(p.second);
		if(h1==h2)return h1;
		return h1^h2;
	}
};

int main(){
	unordered_map<pair<int,int>,int,hash_pair> m;
	m[make_pair(1,1)]=3;
	m[make_pair(2,3)]=4;
	cout<<m[make_pair(2,3)]<<'\n';
}
