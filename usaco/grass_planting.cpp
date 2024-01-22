#include <fstream>
using namespace std;

int main(){
	ifstream cin("planting.in");
	ofstream cout("planting.out");
	int n,a,b;
	cin>>n;
	int ne[n];
	for(int i=0;i<n;i++)ne[i]=1;
	for(int i=1;i<n;i++){
		cin>>a>>b;
		ne[a-1]++;ne[b-1]++;
	}
	int max=0;
	for(int i=0;i<n;i++)if(ne[i]>max)max=ne[i];
	cout<<max<<'\n';
}
