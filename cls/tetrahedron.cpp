#include <iostream>
using namespace std;

int main(){
	long long a,b,c,ret=0;cin>>a>>b>>c;
	long long ab=a*b;
	for(long long x=0;x<=ab;x+=b)
		for(long long y=0;y<=ab;y+=a){
			// if exits tetrahedron break
			if(x+y>ab)break;
			//   bcx + acy + abz = abc
			//   max z = (abc - bcx - acy)/ab
			// we then add this amount +1 to the total
			// because all valid z values range from 0
			// to maximum z
			ret+=(c*(ab-x-y))/ab;ret++;
		}
	cout<<ret<<'\n';
}
