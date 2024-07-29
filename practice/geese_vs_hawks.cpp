#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n;cin>>n;
	bool wa[n],wb[n];
	int pa[n],pb[n];
	for(int i=0;i<n;++i){
		char c;cin>>c;
		if(c=='W')wa[i]=1;
		else wa[i]=0;
	}
	for(int i=0;i<n;++i)cin>>pa[i];
	for(int i=0;i<n;++i){
		char c;cin>>c;
		if(c=='W')wb[i]=1;
		else wb[i]=0;
	}
	for(int i=0;i<n;++i)cin>>pb[i];
	vector<int> al,aw,bl,bw;
	for(int i=0;i<n;++i){
		if(wa[i])aw.push_back(pa[i]);
		else al.push_back(pa[i]);
		if(wb[i])bw.push_back(pb[i]);
		else bl.push_back(pb[i]);
	}
	sort(al.begin(),al.end());
	sort(aw.begin(),aw.end());
	sort(bl.begin(),bl.end());
	sort(bw.begin(),bw.end());
	int ret=0;
	int p=0;
	if(bl.size())for(int x:aw){
		if(x>bl[p]){
			cout<<"a "<<x<<" vs "<<bl[p]<<'\n';
			ret+=x+bl[p];
			p++;
			if(p==bl.size())break;
		}
	}
	p=0;
	if(al.size())for(int x:bw){
		if(x>al[p]){
			cout<<"b "<<x<<" vs "<<al[p]<<'\n';
			ret+=x+al[p];
			p++;
			if(p==al.size())break;
		}
	}
	cout<<ret<<'\n';
}
