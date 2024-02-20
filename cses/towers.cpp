#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	int cubes[n];
	for(int i=0;i<n;i++)cin>>cubes[i];
	int next[n];
	for(int i=0;i<n;i++)next[i]=i+1;
	int prev[n];
	for(int i=0;i<n;i++)prev[i]=i-1;
	bool fin[n];
	for(int i=0;i<n;i++)fin[i]=1;
	next[n-1]=-1;
	prev[0]=-1;
	int ret=0;
	for(int f=0;f<n;f++)
		if(fin[f]){
			int ptr=f,h=cubes[f];
//cout<<"run: "<<ptr<<','<<h;
			while(next[ptr]+1){
				ptr=next[ptr];
				if(cubes[ptr]<h){
					fin[ptr]=0;
//cout<<' '<<ptr<<','<<cubes[ptr];
					if(prev[ptr]+1)
						next[prev[ptr]]=next[ptr];
					if(next[ptr]+1)
						prev[next[ptr]]=prev[ptr];
					h=cubes[ptr];
				}
//else cout<<" x"<<ptr<<','<<cubes[ptr];
			}
//cout<<'\n';
			ret++;
		}
	cout<<ret<<'\n';
}
