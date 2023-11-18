#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int n;

struct piece{
	bool h[64];
	int n;
};

int main(){
	ifstream cin("bcs.in");
	ofstream cout("bcs.out");
	int k;cin>>n>>k;
	bool target[n][n];
	bool pieces[k][n][n];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			char c;cin>>c;
			target[i][j]=c=='#';
		}
	for(int h=0;h<k;h++)
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				char c;cin>>c;
				pieces[h][i][j]=c=='#';
			}
	vector<struct piece> comp;
	for(int h=0;h<k;h++){
		int xmin=n,ymin=n,xmax=0,ymax=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(pieces[h][i][j]){
					if(i<xmin)xmin=i;
					if(j<ymin)ymin=j;
					if(i>xmax)xmax=i;
					if(j>ymax)ymax=j;
				}
		for(int xoff=0;xoff<n-(xmax-xmin);xoff++)
			for(int yoff=0;yoff<n-(ymax-ymin);yoff++){
				struct piece tmp;
				for(int i=xmin;i<=xmax;i++)
					for(int j=ymin;j<=ymax;j++){
						if(pieces[h][i][j]&&
							!target[i-xmin+xoff][j-ymin+yoff])
							goto failed;
					}
				tmp.n=h+1;
				for(int i=0;i<n;i++)for(int j=0;j<n;j++)tmp.h[i*n+j]=0;
				for(int i=xmin;i<=xmax;i++)
					for(int j=ymin;j<=ymax;j++)
						if(pieces[h][i][j])
							tmp.h[n*(i-xmin+xoff)+j-ymin+yoff]=1;
				comp.push_back(tmp);
				failed: continue;
			}
	}
	int len=comp.size();
	for(int p1=0;p1<len;p1++)
		for(int p2=p1+1;p2<len;p2++){
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(target[i][j]){
						if(!(comp[p1].h[i*n+j]^comp[p2].h[i*n+j]))goto fail;
					}else{
						if(comp[p1].h[i*n+j]||comp[p2].h[i*n+j])goto fail;
					}
			cout<<comp[p1].n<<' '<<comp[p2].n<<'\n';
			goto works;
			fail: continue;
		}
	works: return 0;
}

/*
4 3
####
#..#
#.##
....
.#..
.#..
##..
....
####
##..
#..#
####
....
.###
.#..
.#..
*/
