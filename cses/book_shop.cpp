#include <iostream>
using namespace std;

typedef struct book{
	int price;
	long long pages;
}book;

int main(){
	int n,x;cin>>n>>x;
	// best # of pages that can be bought with cost x
	long long best[x+1];
	// initialize
	for(int i=0;i<=x;i++)best[i]=0;
	book books[n];
	for(int i=0;i<n;++i)cin>>books[i].price;
	for(int i=0;i<n;++i)cin>>books[i].pages;
	// for every book:
	for(int i=0;i<n;++i)
		// for all possible places to add book, add it
		for(int j=x-books[i].price;j>=0;--j){
			// new price of this block of pages
			int k=j+books[i].price;
			if(best[k]<best[j]+books[i].pages)
				best[k]=best[j]+books[i].pages;
		}
	cout<<best[x]<<'\n';
}
