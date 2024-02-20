#include <algorithm>
#include <iostream>
using namespace std;

using book=struct book;
struct book{
	int price;
	int pages;
	bool operator<(const book o)const{
		return price<o.price;
	}
};

int main(){
	int n,x;cin>>n>>x;
	int best[x+1];
	for(int i=0;i<x;i++)best[i+1]=-1;
	best[0]=0;
	book books[n];
	for(int i=0;i<n;i++)cin>>books[i].price;
	for(int i=0;i<n;i++)cin>>books[i].pages;
	sort(books,books+n);
	for(int i=0;i<n;i++)
		for(int j=x-books[i].price;j>=0;j--)if(best[j]>-1){
			int k=j+books[i].price;
			if(best[k]<best[j]+books[i].pages)
				best[k]=best[j]+books[i].pages;
		}
	while(best[x]<0)x--;
	cout<<best[x]<<'\n';
}
