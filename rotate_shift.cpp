#include <iostream>
using namespace std;

int main(){
	int n,k,t,tmp;
	cin>>n>>k>>t;
	int map[n],cow_pos[n],B,reached[n];
	bool set[n];
	for(int i=0;i<n;i++){
		map[i]=i;
		set[i]=false;
	}
	cin>>B;tmp=B;
	for(int i=0;i<k-1;i++){
		int A;cin>>A;
		map[tmp]=A;tmp=A;
	}
	map[tmp]=B;
//for(int m:map)cout<<m;cout<<'\n';
	for(int i=0;i<n;i++){if(map[i]==0)map[i]=n-1;else map[i]--;}
	int g_offset=t%n;
//for(int m:map)cout<<m;cout<<'\n'<<g_offset<<'\n';
	for(int i=0;i<n;i++){
		if(set[i])continue;
		int cur=map[i],len=1,ct=1;
		reached[0]=i;
		while(cur!=i){
			reached[ct]=cur;ct++;
			cur=map[cur];len++;
		}
//cout<<"cyc ";for(int i=0;i<ct;i++)cout<<reached[i];cout<<'\n';
		for(int i=0;i<ct;i++){
			cow_pos[(reached[(i+t)%len]+g_offset)%n]=reached[i];
			set[reached[i]]=true;
		}
	}
	cout<<cow_pos[0];
	for(int i=1;i<n;i++)cout<<' '<<cow_pos[i];cout<<'\n';
	return 0;
}
