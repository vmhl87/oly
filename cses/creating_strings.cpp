#include <iostream>
#include <string>
using namespace std;

int n,h,ret=0;
int *buf,*pr,*mask;
char *chr;
string str;

void r(int len){
	for(int i=0;i<n;i++)if(buf[i]>0){
		buf[n+len]=buf[i];
		buf[i]*=-1;
		r(len+1);
		buf[n+len]=0;
		buf[i]*=-1;
	}
	int state[h];
	for(int i=0;i<h;i++)state[i]=0;
	for(int i=0;i<n;i++)for(int j=0;j<h;j++)
		if(buf[i+n]==mask[j]+state[j])state[j]++;
	for(int i=0;i<h;i++)if(state[i]<pr[i])return;
	for(int i=0;i<n;i++)str+=chr[buf[i+n]-1];
	str+='\n';ret++;
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	string s;cin>>s;n=s.length();
	int ct[26],a=0,b=0;for(int i=0;i<26;i++)ct[i]=0;
	for(char c:s)ct[c-'a']++;
	h=0;for(int i:ct)if(i)h++;
	pr=new int[h];mask=new int[h];chr=new char[n];
	for(int i=0;i<26;i++)if(ct[i]){
		pr[a]=ct[i];mask[a]=b+1;
		for(int j=0;j<ct[i];j++)chr[b+j]=i+'a';
		a++;b+=ct[i];
	}
	buf=new int[n*2];for(int i=0;i<n;i++)buf[i]=i+1;
	r(0);
	cout<<ret<<'\n'<<str;
	delete[]buf;
	delete[]pr;
	delete[]mask;
	delete[]chr;
}
