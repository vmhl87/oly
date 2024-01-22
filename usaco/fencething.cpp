#include <fstream>
using namespace std;

// min and max
int mx(int a,int b){
	if(a>b)return a;
	return b;
}

int mn(int a,int b){
	if(a<b)return a;
	return b;
}

int main(){
	ifstream cin("paint.in");
	ofstream cout("paint.out");
	// input values
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	/*
		lower bounds are a and c, upper bounds are b and d
		to find the bounds of our intersecting region, we must
		take the maximum lower bound and the minimum upper bound
		so to do this we use mx() and mn() and store to l,u
		sum is the sum of the ranges individually, not accounting
		for overlapping (which is u-l)
		
		case 1: overlap
		          ----
		 #############
		          ###########
		we can clearly see that the total length his the sum of
		the two ranges subtracting 3 (for the central region)
		
		case 2: no overlap
		        ------
		 #######
		              #######
		we just sum up the two ranges - we can see that the start
		and end positions for the overlap are in the wrong order
		(upper lower than lower) so we handle that with case
	*/
	int l=mx(a,c),u=mn(b,d),sum=b+d-a-c;
	// probably self explanatory
	if(l>u)cout<<sum;
	else cout<<sum-u+l;
	cout<<'\n';
}
