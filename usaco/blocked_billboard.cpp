#include <fstream>
using namespace std;

int main(){
	ifstream cin("billboard.in");
	ofstream cout("billboard.out");
	int b1[4],b2[4],truck[4];
	for(int i=0;i<4;i++)cin>>b1[i];
	for(int i=0;i<4;i++)cin>>b2[i];
	for(int i=0;i<4;i++)cin>>truck[i];
	int area=(b1[2]-b1[0])*(b1[3]-b1[1])+(b2[2]-b2[0])*(b2[3]-b2[1]);
	area-=max(0,min(b1[2],truck[2])-max(b1[0],truck[0]))*
		max(0,min(b1[3],truck[3])-max(b1[1],truck[1]));
	area-=max(0,min(b2[2],truck[2])-max(b2[0],truck[0]))*
		max(0,min(b2[3],truck[3])-max(b2[1],truck[1]));
	cout<<area<<'\n';
}
