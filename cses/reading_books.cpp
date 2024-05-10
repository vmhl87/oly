// Reading Books  -  https://cses.fi/problemset/task/1631
// The key realization here is that a greedy algorithm exists:
// Alice reads books 1 - n in order, while Bob reads boox n - 1
// in order, where the books are sorted in increasing order of
// length. There will be overlap if and only if at some point
// Alice and Bob are reading book N at the same time, i.e. the
// amount of time necessary to read all the books combined
// is less than twice the amount of time necessary to read book N.

#include <algorithm>
#include <iostream>
using namespace std;

int main(){
	int n; cin >> n;
	long long books[n];
	long long sum = 0;
	for(int i=0; i<n; ++i)
		cin>>books[i], sum += books[i];
	sort(books, books+n);
	cout << max(sum, books[n-1]*2) << '\n';
}
