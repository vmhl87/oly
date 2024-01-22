#include <iostream>
using namespace std;

int main(){
	int n,m;cin>>m>>n;
	int cows[n];
	char c;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			cin>>c;if(c=='G')cows[i]+=(1<<j);
		}
	int max[n];
	for(int i=0;i<n;i++)max[i]=0;
	for(int i=n-1;i>0;i--){
		for(int j=0;j<i;j++){
			cows[j]^=cows[j+1];
			int count=0;
			for(int h=0;h<m;h++)
				if(cows[j]&(1<<h))count++;
			if(max[j]<count)max[j]=count;
			if(max[j+n-i]<count)max[j+n-i]=count;
		}
	}
	for(int i=0;i<n;i++){
		cout<<max[i]<<'\n';
	}
}

/*
000
001
010
011
100
101
110
111

000 100
001 101
010 110
011 111

000 100 110
001 101 111
010
011

000 100 *110
001 101  111
010
011

000 *100 *110
001  101  111
010
011

000 *100
001  101
010  110
011  111
*/
