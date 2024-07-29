#include <iostream>
using namespace std;

typedef struct fract{
	int num,den;
	bool operator>(const fract o)const{
		return num*o.den>o.num*den;
	}
	void operator=(const fract o){
		num=o.num;den=o.den;
	}
	fract():num(0),den(0){}
	fract(int n):num(n),den(0){}
	fract(int n,int d):num(n),den(d){}
}fract;

int main(){
	int n;cin>>n;
	int str[n];
	for(int i=0;i<n;++i){
		char c;cin>>c;
		str[i]=c-'a';
	}
	int st[26];for(int i=0;i<26;++i)st[i]=0;
	int l=0,r=0,cl=0;
	fract best(2,1);
	fract cur(0,0);
	fract last;
	for(int i=0;i<n;++i){
		last=cur;
		cur.den++;
		if(!st[str[i]])cur.num++;
		st[str[i]]++;
		if(best>cur){
			best=cur;
			l=cl;r=i;
		}
		if(cur>last){
			cur.num=0;cur.den=0;
			for(int i=0;i<26;++i)st[i]=0;
			cl=i;
		}
	}
	cout<<l+1<<' '<<r+1<<'\n';
}
