#include <iostream>
#include <string>
using namespace std;

void test_case(){
	int n,K;
	cin>>n>>K;
	bool traps[n][n];
	for(int i=0;i<n;i++)for(int j=0;j<n;j++){
		char c;cin>>c;
		if(c=='H')traps[j][i]=true;
		else traps[j][i]=false;
	}
	int count=0;
	for(int i=0;i<n;i++){
		if(traps[i][0])break;
		int q=1;if(i>0)q=0;
		for(int j=1;j<n;j++){
			if(traps[i][j])break;
			if(i==n-1&&j==n-1)count++;
			if(K>1-q)for(int k=i+1;k<n;k++){
				if(traps[k][j])break;
				if(k==n-1&&j==n-1)count++;
				if(K>(2-q))for(int l=j+1;l<n;l++){
					if(traps[k][l])break;
					if(k==n-1&&l==n-1)count++;
					if(K>3-q)for(int o=k+1;o<n;o++){
						if(traps[o][l])break;
						if(o==n-1&&l==n-1)count++;
					}
				}
			}
		}
	}
	cout<<count<<'\n';
}

int main(){
	int N;cin>>N;
	for(int i=0;i<N;i++)test_case();
}
