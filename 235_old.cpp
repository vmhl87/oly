#include <iostream>
#include <vector>
using namespace std;

int main(){
	int N,n=0;
	cin>>N;
	int val[N];
	for(int i=0;i<N;i++){
		cin>>val[i];
		if(val[i]>n)n=val[i];
	}
	n+=3;
	vector<long long> values;
	values.push_back(1);
	int i=0;
	while(i<n){
		long long f[3]={2,3,5};
		for(long long v:f){
			bool a=true;
			for(int j=i+1;j<values.size();j++){
				if(values[j]==values[i]*v||j>n){
					a=false;break;
				}
				if(values[j]>values[i]*v){
					a=false;
					values.insert(values.begin()+j,values[i]*v);
					break;
				}
			}
			if(a)values.push_back(values[i]*v);
		}
		i++;
	}
//for(long long i:values)cout<<i<<' ';cout<<'\n';
	long long s=0;
	for(long long i=0;i<N;i++)s+=values[val[i]-1];
	cout<<s<<'\n';
	return 0;
}
