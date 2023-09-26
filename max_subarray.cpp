#include <iostream>
#include <algorithm>
using namespace std;

bool search(int v,int* B,int start,int end){
	if(start==end){
		if(B[start]==v)return true;
		return false;
	}else if(start+1==end){
		if(B[start]==v||B[end]==v)return true;
		return false;
	}else{
		int center=(start+end)/2;
		if(B[center]==v)return true;
		if(B[center]>v)return search(v,B,start,center);
		return search(v,B,center,end);
	}
}

int main(){
	int n,m;
	cin>>n>>m;
	int A[n],B[m];
	for(int i=0;i<n;i++)cin>>A[i];
	for(int i=0;i<m;i++)cin>>B[i];
	sort(B,B+m);
	int max=0,c=0;
	for(int i=0;i<n;i++){
		if(search(A[i],B,0,m))c=0;
		else c++;
		if(c>max)max=c;
	}
	cout<<max<<'\n';
	return 0;
}
