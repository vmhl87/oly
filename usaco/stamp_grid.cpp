#include <iostream>
using namespace std;

void test_case(){
	int n,m;cin>>n;
	bool out[n][n];
	char t;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			cin>>t;out[i][j]=(t=='*');
		}
	cin>>m;
	bool stamp[m][m];
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++){
			cin>>t;stamp[i][j]=(t=='*');
		}
	bool tar[n][n];
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)tar[i][j]=0;
	for(int h=0;h<4;h++){
		for(int i=0;i<=n-m;i++)
			for(int j=0;j<=n-m;j++){
				bool works=1;
				for(int a=0;a<m;a++)
					for(int b=0;b<m;b++)
						if(stamp[a][b]&&!out[a+i][b+j])works=0;
				if(works){
					for(int a=0;a<m;a++)
						for(int b=0;b<m;b++)
							if(stamp[a][b])tar[a+i][b+j]=1;
				}
			}
		//rotate stamp
		bool next[m][m];
		for(int i=0;i<m;i++)
			for(int j=0;j<m;j++)
				next[i][j]=stamp[j][m-i-1];
		for(int i=0;i<m;i++)
			for(int j=0;j<m;j++)
				stamp[i][j]=next[i][j];
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(tar[i][j]!=out[i][j]){
				cout<<"NO\n";
				return;
			}
	cout<<"YES\n";
}

int main(){
	int n;cin>>n;
	while(n-->0)test_case();
}
