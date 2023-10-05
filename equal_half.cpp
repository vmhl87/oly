#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	long long sum=n,end=((long long)n*(n+1))/2;
	if(end%2>0&&cout<<"-1\n")return 0;
	end/=2;cout<<" Attempt to sum to: "<<end<<'\n';
	for(int i=n;i>0;sum+=(--i)){
		if(sum<end)continue;
		cout<<n+1-i<<'\n'<<end-sum+i;
		while(i<n)cout<<' '<<++i;
		cout<<'\n';
		break;
	}
	return 0;
}


/*

Essentially this works because:
say that n = 8

8 7 6 5 4 3 2 1

We traverse this list of values and add them to the sum until the sum
is greater than target sum (8*9/4 = 18)

8 7 6
---->

8+7+6 is bigger than 18, and its previous sum (8+7) is less than 18.
To achieve the target sum from here, we must replace 6 with 3, as 15+3 = 18.

It is trivial to show that such a number can always be found:
We have only added the numbers 8 and 7, meaning that all the numbers between
1 and 6 are free to be added. We can now do a bound analysis:
Because our current sum (8+7+6) is too big, we know that the difference between
our past sum (8+7) and the target sum must be less than 6. We also know that
it is greater than 0, because our past sum was too small.

We can see that this intermediate number must exist in the range 1-6. And because
these numbers will all be unused, we will always have a solution.

*/
