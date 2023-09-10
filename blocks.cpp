#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int N;
	char blocks[4][6];
	cin>>N;
	for(int i=0;i<4;i++)
		for(int j=0;j<6;j++)
			cin>>blocks[i][j];
	for(int i=0;i<N;i++){
		string str;
		cin>>str;
		int l=str.length();
		bool valid=true,pos[l][4];
		for(int a=0;a<l;a++)
			for(int b=0;b<4;b++)
				pos[a][b]=false;
		for(int j=0;j<4;j++)
			for(int a=0;a<6;a++)
				for(int b=0;b<l;b++)
					if(blocks[j][a]==str[b])
						pos[b][j]=true;
		for(int j=0;j<l;j++){
			bool w=false;
			for(int a=0;a<4;a++)if(pos[j][a])w=true;
			if(!w){valid=false;break;}
		}
		if(valid){
			short us[4];
			for(int j=0;j<4;j++)us[j]=0;
			for(int a=0;a<l;a++)
				for(int b=0;b<4;b++)
					if(pos[a][b])us[b]++;
//for(int j=0;j<4;j++)cout<<us[j];cout<<endl;
			bool res[l];
			for(int j=0;j<l;j++)res[j]=false;
			for(int j=0;j<4;j++)
				if(us[j]==1)
					for(int a=0;a<l;a++)
						if(pos[a][j])res[a]=true;
//for(int j=0;j<l;j++)if(res[j]){cout<<1;}else{cout<<0;}cout<<'\n';
			bool used[4];
			for(int j=0;j<4;j++)used[j]=false;
			for(int a=0;a<l;a++)
				if(!res[a])
					for(int b=0;b<4;b++)
						if(pos[a][b])used[b]=true;
//for(int j=0;j<4;j++)if(used[j]){cout<<1;}else{cout<<0;}cout<<'\n';
			int c1=0,c2=0;
			for(int j=0;j<l;j++)if(!res[j])c1++;
			for(int j=0;j<4;j++)if(used[j])c2++;
			if(c2<c1)valid=false;
		}
		if(valid)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
