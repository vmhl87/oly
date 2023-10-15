#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

struct cow{
	short k;
	vector<short> traits;
};

int main(){
	ifstream cin("evolution.in");
	ofstream cout("evolution.out");
	int n;cin>>n;
	struct cow cows[n];
	map<string,short> traits;
	short count=0;
	while(n-->0){
		short k;cin>>k;
		cows[n].k=k;
		while(k-->0){
			string s;cin>>s;
			if(traits.find(s)==traits.end()){
				traits[s]=count;
				count++;
			}
			cows[n].traits.push_back(traits[s]);
		}
	}
	short mapping[count][count];
	for(short i=0;i<count;i++)
		for(short j=0;j<count;j++)
			mapping[i][j]=0;
	for(struct cow c:cows){
		int tr=c.traits.size();
		for(int i=0;i<tr;i++){
			bool en[count];for(short j=0;j<count;j++)en[j]=1;
			for(int j=i+1;j<tr;j++){
				short r=0;en[c.traits[j]]=0;
				if(mapping[c.traits[i]][c.traits[j]]==0){
					mapping[c.traits[i]][c.traits[j]]=1;r++;
				}
				if(mapping[c.traits[j]][c.traits[i]]==0){
					mapping[c.traits[j]][c.traits[i]]=1;r++;
				}
				if(r==0) goto failed;
			}
			for(short j=0;j<count;j++){
				if(en[j]){
					if(mapping[c.traits[i]][j]==1&&mapping[j][c.traits[i]]==2) goto failed;
					mapping[c.traits[i]][j]=2;
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
