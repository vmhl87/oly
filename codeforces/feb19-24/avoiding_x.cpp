#include <unordered_set>
#include <iostream>
using namespace std;

int mp(int x,int y){
	return x*7+y;
}

typedef struct{
	int v;
	int l;
	int next=-1;
	int prev1,prev2;
}p;

void test_case(){
	bool board[7][7];
	char c;
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++){
			cin>>c;
			if(c=='B')board[i][j]=1;
			else board[i][j]=0;
		}
	unordered_set<int> cells[49];
	unordered_set<int> ops[49];
	for(int i=1;i<6;i++)
		for(int j=1;j<6;j++)
			if(board[i][j]&&board[i-1][j-1]&&board[i-1][j+1]&&
			board[i+1][j-1]&&board[i+1][j+1]){
				for(int a=-1;a<2;a+=2)
					for(int b=-1;b<2;b+=2){
						// cell is dependent on one of corners
						cells[mp(i,j)].insert(mp(i+a,j+b));
						// corners are dependent on cell
						ops[mp(i+a,j+b)].insert(mp(i,j));
					}
				cells[mp(i,j)].insert(mp(i,j));
				ops[mp(i,j)].insert(mp(i,j));
			}
	p tree[101];
	for(int i=0;i<49;i++){
		tree[i].v=i;tree[i].l=ops[i].size();
	}
	int lbound=0,ubound=49,end=49;
	while(lbound<ubound-1){
		for(int i=lbound;i<ubound;i+=2){
			int j=i+1>ubound-1?ubound-1:i+1;
			if(tree[i].l>tree[j].l){
				tree[end].l=tree[i].l;
				tree[end].v=tree[i].v;
			}else{
				tree[end].l=tree[j].l;
				tree[end].v=tree[j].v;
			}
			tree[i].next=end;tree[j].next=end;
			tree[end].prev1=i;tree[end].prev2=j;
			end++;
		}
		lbound=ubound;ubound=end;
	}
	int ret=0;
	while(tree[100].l){
		ret++;
		// i = fixed cell
		int tofix=tree[100].v;
		for(int i:ops[tofix]){
//			cout<<"fix "<<i<<'\n';
			// j = updated op
			for(int j:cells[i]){
				if(j==tofix)continue;
//				cout<<"  up op "<<j<<'\n';
				ops[j].erase(i);
				tree[j].l=ops[j].size();
//				cout<<"    er\n";
				// update rest of tree
				int p=j;
				while(tree[p].next!=-1){
					p=tree[p].next;
//					cout<<"   jto "<<p<<'\n';
					if(tree[tree[p].prev1].l>tree[tree[p].prev2].l){
						tree[p].v=tree[tree[p].prev1].v;
						tree[p].l=tree[tree[p].prev1].l;
					}else{
						tree[p].v=tree[tree[p].prev2].v;
						tree[p].l=tree[tree[p].prev2].l;
					}
				}
			}
//			cout<<"fin\n";
		}
//		cout<<"clr "<<tofix<<'\n';
		ops[tofix].clear();
		tree[tofix].l=0;
		while(tree[tofix].next!=-1){
			tofix=tree[tofix].next;
			if(tree[tree[tofix].prev1].l>tree[tree[tofix].prev2].l){
				tree[tofix].v=tree[tree[tofix].prev1].v;
				tree[tofix].l=tree[tree[tofix].prev1].l;
			}else{
				tree[tofix].v=tree[tree[tofix].prev2].v;
				tree[tofix].l=tree[tree[tofix].prev2].l;
			}
		}
	}
	cout<<ret<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}

/*
1
WWWWWWW
WBBBBWW
WBBBBWW
WBBBBWW
WBBBBWW
WWWWWWW
WWWWWWW
*/
