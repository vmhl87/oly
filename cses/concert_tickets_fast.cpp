#include <algorithm>
#include <cstdio>
using namespace std;

#define min(a,b) a<b?a:b

int tree[400001][2];
int t[200000];
int n,ln=1;

inline void prop(int i){
	tree[i][0]=min(tree[i<<1][0],tree[i<<1|1][0]);
	tree[i][1]=min(tree[i<<1][1],tree[i<<1|1][1]);
}

int cmp(const void *a,const void *b){
	return *((int*)a)-*((int*)b);
}

int main(){
	int m;
	fread(n,sizeof(int),sizeof(m),stdin);
	fread(m,sizeof(int),sizeof(m),stdin);
	fread(t,sizeof(int),sizeof(t),stdin);
	sort(t,t+n);
	while(ln<n*2)ln<<=1;
	ln>>=1;
	for(int i=0;i<n;++i){
		int l=i+ln-(i+ln>=n*2)*n;
		tree[l][0]=t[i];
		tree[l][1]=t[i];
	}
	for(int i=n-1;i>0;--i)prop(i);
	int v[m];
	fread(v,sizeof(int),sizeof(v),stdin);
	for(int x=0;x<m;++x){
		if(v[x]<tree[1][0]){
			fwrite(
			printf("-1\n");
			continue;
		}
		int i=1;
		while(i<n){
			if(tree[i<<1|1][0]>v[x])i<<=1;
			else i=i<<1|1;
		}
		printf("%d\n",tree[i][1]);
		tree[i][0]=1<<30;
		tree[i][1]=-1;
		while(i){
			i>>=1;prop(i);
		}
	}
}
