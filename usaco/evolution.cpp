#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main(){
	ifstream cin("evolution.in");
	ofstream cout("evolution.out");
	int n;cin>>n;
	vector<short> cows[n];
	map<string,short> traits;
	short count=0;
	while(n-->0){
		short k;cin>>k;
		while(k-->0){
			string s;cin>>s;
			if(traits.find(s)==traits.end()){
				traits[s]=count;
				count++;
			}
			cows[n].push_back(traits[s]);
		}
	}
	short mapping[count][count];
	for(short i=0;i<count;i++)
		for(short j=0;j<count;j++)
			mapping[i][j]=0;
	for(vector<short> c:cows){
		short tr=c.size();
		for(short i=0;i<tr;i++){
			bool en[count];for(short j=0;j<count;j++)en[j]=1;
			for(short j=i+1;j<tr;j++){
				short r=0;en[c[j]]=0;
				if(mapping[c[i]][c[j]]==0){
					mapping[c[i]][c[j]]=1;r++;
				}
				if(mapping[c[j]][c[i]]==0){
					mapping[c[j]][c[i]]=1;r++;
				}
				if(r==0) goto failed;
			}
			for(short j=0;j<count;j++){
				if(en[j]){
					if(mapping[c[i]][j]==1&&mapping[j][c[i]]==2)
						goto failed;
					mapping[c[i]][j]=2;
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
