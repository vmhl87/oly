#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;cin>>s;
	int count[26];for(int i=0;i<26;i++)count[i]=0;
	for(char c:s)count[c-'A']++;
	int mid=-1;
	for(int i=0;i<26;i++)if(count[i]%2==1)if(mid<0){mid=i;}else{goto failed;}
	for(int i=0;i<26;i++)if(mid!=i)
		for(int j=0;j<count[i]/2;j++)cout<<(char)('A'+i);
	if(mid>-1)for(int i=0;i<count[mid];i++)cout<<(char)('A'+mid);
	for(int i=25;i>-1;i--)if(mid!=i)
		for(int j=0;j<count[i]/2;j++)cout<<(char)('A'+i);
	cout<<'\n';
	return 0;
failed:
	cout<<"NO SOLUTION\n";
}
