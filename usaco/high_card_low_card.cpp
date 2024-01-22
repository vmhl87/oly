#include <fstream>
#include <algorithm>
using namespace std;

bool sort_reverse(int a,int b){
	return a>b;
}

// returns an index - 0 is start, n is end
int binary_search(int start,int end,int target,int *arr){
	if(start==end){
		if(target>arr[start])return start+1;
		return start;
	}
	if(start>end)return end;
	int split=(start+end)/2;
	if(target>arr[split])return binary_search(split+1,end,target,arr);
	return binary_search(start,split,target,arr);
}

int main(){
	ifstream cin("cardgame.in");
	ofstream cout("cardgame.out");
	// inputs
	int n,half_n,points=0;cin>>n;half_n=n/2;
	int bessie[n],elsie[n];
	for(int i=0;i<n;i++)cin>>elsie[i];
	// compute bessie cards (auto sorted)
	int elsie_s[n];for(int i=0;i<n;i++)elsie_s[i]=elsie[i];
	sort(elsie_s,elsie_s+n);
	for(int i=1,pt1=0,pt2=0;i<=n*2;i++){
		if(elsie_s[pt1]==i)pt1++;
		else{bessie[pt2]=i;pt2++;}
	}
	// presort
	sort(elsie,elsie+half_n);
	sort(elsie+half_n,elsie+n,sort_reverse);
	// double everything
	for(int &i:bessie)i*=2;
	for(int &i:elsie)i*=2;
	// stage 1
	for(int i=0,search_start=half_n;i<half_n;i++){
		int index=binary_search(search_start,n,elsie[i]+1,bessie);
		if(index>=n)break;
		search_start=index+1;
		points++;
	}
	// stage 2
	for(int i=half_n,search_start=half_n;i<n;i++){
		int index=binary_search(0,search_start,elsie[i]-1,bessie);
		if(index<=0)break;
		search_start=index-2;
		points++;
	}
	// end
	cout<<points<<'\n';
}
