#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int find_lis(vector<int> a) {
	vector<int> dp;
	for (int i : a) {
		int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin();
		if (pos == dp.size()) {
			// we can have a new, longer increasing subsequence!
			dp.push_back(i);
			cout<<"appending "<<i<<'\n';
		} else {
			// oh ok, at least we can make the ending element smaller
			dp[pos] = i;
			cout<<"replacing elem "<<pos+1<<" with "<<i<<'\n';
		}
	}
	return dp.size();
}

int main(){
	vector<int> a = {2, 18, 7, 20, 18, 5, 19};
	
	int x = find_lis(a);
}
