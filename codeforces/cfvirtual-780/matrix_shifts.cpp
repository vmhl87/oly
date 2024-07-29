#include <iostream>
using namespace std;

void test_case(){
	int n;cin>>n;
	int counts[n];
	for(int i=0;i<n;++i)counts[i]=0;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			char c;cin>>c;
			if(c=='1')++counts[(i-j+n)%n];
		}
	}
	int best=counts[0];
	for(int i=1;i<n;++i)
		best=(counts[i]>best?counts[i]:best);
	int sum=0;
	for(int i=0;i<n;++i)sum+=counts[i];
	cout<<sum-best-best+n<<'\n';
}

int main(){
	int t;cin>>t;
	while(t--)test_case();
}
