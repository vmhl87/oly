/*

input x0,y0,r0,x1,y1,etc.

total_points = 0

for i between x0-r0 and x0+r0: (all columns that are part of the circle)
	offset = x0 - i
	height = Math.floor(Math.sqrt(r0*r0 - offset*offset)) ("height" of the circle in this column)
	
	min_point = y1 - height
	max_point = y1 + height
	
	total_points += (max_point - min_point + 1)
	
	if column i intersects rectangle:
		account for bounds idk

ex:
10 10 2
9 7 12 10

*/

#include <iostream>
#include <cmath>
using namespace std;

int main(){
	long long x0,y0,r,x1,y1,x2,y2;
	cin>>x0>>y0>>r>>x1>>y1>>x2>>y2;
	long long total=0,rsq=r*r;
	for(long long i=0;i<=r;i++){
		long long h=floor(sqrt(rsq-i*i)),r=h*2+1;
		if(i>0){
			r*=2;
			if(x0-i>x1&&x0-i<x2)r-=min(y0+h+1,max(y0-h,y2))-min(y0+h+1,max(y0-h,y1+1));
		}
		if(x0+i>x1&&x0+i<x2)r-=min(y0+h+1,max(y0-h,y2))-min(y0+h+1,max(y0-h,y1+1));
//cout<<i<<' '<<min(y0+h+1,max(y0-h,y2))<<','<<min(y0+h+1,max(y0-h,y1+1))<<'\n';
		total+=r;
	}
	cout<<total<<'\n';
	return 0;
}
