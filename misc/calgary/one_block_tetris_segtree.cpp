// Initially while reading the probmlem statement for
// this question, I did not realize that the barrels get
// rolled down once a row is filled. As such, I thought
// that the solution would need to efficiently find the
// lowest empty space for a barrel. So I made this impl
// which uses a segtree to find lowest viable space.
//
// Eventually after testing I realized where I misread, and
// wrote a different solution that didn't need a segtree.
//
// I like this solution better, though. It's elegant.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct segtree{
	vector<pair<int,int>> tree;
	int n,mp;
	int leaf(int i){
		int ret=i+mp;
		if(ret>=n*2)ret-=n;
		return ret;
	}
	int unleaf(int i){
		int ret=i-mp;
		if(ret<0)ret+=n;
		return ret;
	}
	segtree(int len):tree(len*2),n(len){
		mp=1;while(mp<len)mp<<=1;
		for(int i=0;i<len;++i){
			tree[i+len].first=0;
			tree[i+len].second=1;
		}
		for(int i=len-1;i>0;--i){
			tree[i].first=tree[i<<1].first+tree[i<<1|1].first;
			tree[i].second=tree[i<<1].second+tree[i<<1|1].second;
		}
	}
	bool full(){
		return tree[1].first==n;
	}
	// puts barrel in lowest possible empty space,
	// and returns which space
	int add(){
		int v=1;
		// search for lowest empty space
		while(v<n){
			if(tree[v<<1].first<tree[v<<1].second)
				v<<=1;
			else v=(v<<1|1);
		}
		// fallback
//		if(tree[v].first)cout<<"vincent you screwed up\n";
		int ret=unleaf(v);
		// set
		while(v){
			tree[v].first++;
			v>>=1;
		}
		return ret;
	}
	// erase barrel (used when clearing row)
	void erase(int i){
//		cout<<"erasing row "<<i;
		i=leaf(i);
//		cout<<" leaf "<<i<<'\n';
		// should be full but be careful
//		if(!tree[i].first)cout<<"already erased\n";
		while(i){
			tree[i].first--;
			i>>=1;
		}
	}
}segtree;

int main(){
	int w,h,n;cin>>w>>h>>n;
	vector<segtree> cols(w,segtree(h));
	int full[h];for(int i=0;i<h;++i)full[i]=0;
	queue<int> ops;int ret=0;
	int cyc=0,len=n;
	for(int i=0;i<n;++i){
		int loc;cin>>loc;
		ops.push(loc);
	}
	while(!ops.empty()){
		int loc=ops.front();
		ops.pop();
		if(cols[loc].full()){
			if(cyc>ops.size()*2){
				cout<<-1<<'\n';
				return 0;
			}
// cout<<"column "<<loc<<" is full, appending to back\n";
			ret++;
			ops.push(loc);
			cyc++;
			continue;
		}
		cyc=0;
		int row=cols[loc].add();
// cout<<"put barrel into row "<<row<<" of column "<<loc<<'\n';
		full[row]++;
		if(full[row]==w){
// cout<<"row is full, clearing\n";
			full[row]=0;
			for(int i=0;i<w;++i)
				cols[i].erase(row);
		}
	}
	cout<<ret<<'\n';
}
