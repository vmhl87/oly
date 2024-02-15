#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	while(n-->0){
		double v,x;char c;
		cin>>v>>c>>x;
		double t=x/v;
		if(t<=1)
			cout<<"SWERVE\n";
		else if(t<=5)
			cout<<"BRAKE\n";
		else cout<<"SAFE\n";
	}
}
