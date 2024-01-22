/*
	input points into array
	put into map and sort
	compute range sums for each point in map
	iterate over all points and multiply their range sums for x and y
*/

#include <fstream>
#include <algorithm>
using namespace std;

typedef struct{
	int x;
	int y;
	long long xsum;
	long long ysum;
}point;

typedef struct{
	int a;
	int b;
	int i;
}sorter;

bool comp_sorters(sorter a,sorter b){
	if(a.a==b.a)return a.b<b.b;
	return a.a<b.a;
}

int main(){
	ifstream cin("triangles.in");
	ofstream cout("triangles.out");
	int n;cin>>n;
	point points[n];
	for(int i=0;i<n;i++)
		cin>>points[i].x>>points[i].y;
	sorter xs[n],ys[n];
	for(int i=0;i<n;i++){
		xs[i].a=points[i].x;xs[i].b=points[i].y;xs[i].i=i;
		ys[i].a=points[i].y;ys[i].b=points[i].x;ys[i].i=i;
	}
	sort(xs,xs+n,comp_sorters);
	sort(ys,ys+n,comp_sorters);
//for(int i=0;i<n;i++)cout<<points[xs[i].i].x<<','<<points[xs[i].i].y<<' ';cout<<'\n';
//for(int i=0;i<n;i++)cout<<points[ys[i].i].x<<','<<points[ys[i].i].y<<' ';cout<<'\n';
	for(int i=0;i<n;){
		int start=i;
		while(xs[i].a==xs[start].a&&i<n)i++;
		int u_sum=0,d_sum=0;
		for(int j=start+1;j<i;j++)u_sum+=xs[j].b-xs[start].b;
		for(int j=start;j<i;j++){
			points[xs[j].i].xsum=u_sum+d_sum;
			u_sum-=(xs[j+1].b-xs[j].b)*(i-j-1);
			d_sum+=(xs[j+1].b-xs[j].b)*(j-start+1);
		}
	}
	for(int i=0;i<n;){
		int start=i;
		while(ys[i].a==ys[start].a&&i<n)i++;
		int u_sum=0,d_sum=0;
		for(int j=start+1;j<i;j++)u_sum+=ys[j].b-ys[start].b;
		for(int j=start;j<i;j++){
			points[ys[j].i].ysum=u_sum+d_sum;
			u_sum-=(ys[j+1].b-ys[j].b)*(i-j-1);
			d_sum+=(ys[j+1].b-ys[j].b)*(j-start+1);
		}
	}
//for(int i=0;i<n;i++)cout<<points[i].x<<','<<points[i].y<<','<<points[i].xsum<<','<<points[i].ysum<<'\n';
	long long ret=0,MOD=1000000007;
	for(int i=0;i<n;i++){
		ret+=points[i].xsum*points[i].ysum;
		ret%=MOD;
	}
	cout<<ret<<'\n';
}
