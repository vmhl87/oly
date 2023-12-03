#include <iostream>
using namespace std;

int main(){
	long long a,b,c;cin>>a>>b>>c;
	long long ret=0,abc=a*b*c,ab=a*b,bc=b*c,ac=a*c;
	for(long long x=0;x<=a;x++)
		for(long long y=0;y<=b;y++){
			// if exits tetrahedron break
			if(b*x+a*y>ab)break;
			//   bcx + acy + abz = abc
			//   max z = (abc - bcx - acy)/ab
			// we then add this amount +1 to the total
			// because all valid z values range from 0
			// to maximum z
			ret += 1+(abc-bc*x-ac*y)/ab;
		}
	cout<<ret<<'\n';
}
