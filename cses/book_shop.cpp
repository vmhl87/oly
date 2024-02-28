#include <algorithm>
#include <iostream>
using namespace std;

typedef struct book{
	int price;
	long long pages;
	bool operator<(const book o)const{
		if(price==o.price)return pages<o.pages;
		return price<o.price;
	}
}book;

int main(){
	int n,x;cin>>n>>x;
	long long best[x+1];
	for(int i=0;i<x;i++)best[i+1]=-1;
	best[0]=0;
	book books[n];
	for(int i=0;i<n;++i)cin>>books[i].price;
	for(int i=0;i<n;++i)cin>>books[i].pages;
	sort(books,books+n);
	for(int i=0;i<n;++i)
		for(int j=x-books[i].price;j>=0;--j)if(best[j]>-1){
			int k=j+books[i].price;
			if(best[k]<best[j]+books[i].pages)
				best[k]=best[j]+books[i].pages;
		}
	while(best[x]<0)x--;
	cout<<best[x]<<'\n';
}
