#include <iostream>
#include <string>
using namespace std;

int main(){
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
		bool valid=false;
		for(int a=0;a<6;a++)
			for(int b=0;b<6;b++)
				for(int c=0;c<6;c++)
					for(int d=0;d<6;d++){
						char cr[4]={
								blocks[0][a],blocks[1][b],
								blocks[2][c],blocks[3][d]
							};
						bool used[4]={false,false,false,false},w=true;
						for(int j=0;j<l;j++){
							bool t=false;
							for(int k=0;k<4;k++)
								if(!used[k]&&str[j]==cr[k]){
									t=true;used[k]=true;
									break;
								}
							if(!t){w=false;break;}
						}
						if(w)valid=true;
					}
		if(valid)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
