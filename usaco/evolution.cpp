#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

typedef struct cow{
	short nt;
	short* t;
} cow;

int main(){
	ifstream cin("evolution.in");
	ofstream cout("evolution.out");
	int n;cin>>n;
	cow cows[n];
	map<string,short> traits;
	short count=0;
	while(n-->0){
		short k;cin>>k;
		cows[n].nt=k;cows[n].t=new short[k];
		while(k-->0){
			string s;cin>>s;
			if(traits.find(s)==traits.end()){
				traits[s]=count;
				count++;
			}
			cows[n].t[k]=traits[s];
		}
	}
	short mapping[count][count];
	for(short i=0;i<count;i++)
		for(short j=0;j<count;j++)
			mapping[i][j]=1;
	for(cow c:cows){
		bool in[count];for(short i=0;i<count;i++)in[i]=0;
		for(short t=0;t<c.nt;t++)in[c.t[t]]=1;
		for(short t=0;t<count;t++)if(in[t]){
			for(short i=0;i<count;i++){
				if(in[i]&&i!=t){
					if(mapping[t][i]>0)mapping[t][i]=2;
					else if(mapping[i][t]==0)goto failed;
				}else{
					if(mapping[t][i]==2&&mapping[i][t]==0)
						goto failed;
					mapping[t][i]=0;
				}
			}
		}
	}
	cout<<"yes\n";
	return 0;
failed:
	cout<<"no\n";
	return 0;
}
