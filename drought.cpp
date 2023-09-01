#include <iostream>
using namespace std;

void test_case(){
	int n_cows;
	cin >> n_cows;
	long long cows[n_cows];
	for(int i=0;i<n_cows;i++) cin >> cows[i];
	/*
		define index as a bound such that all cows
		  before such index are at the same hunger level
		while index is not the last cow:
			look at the first pair of cows that differ
			in hunger level: if the first is smaller than
			the second, this is trivial
			if not, decrement all cows before index in a
			deterministic pattern
	*/
	long long count=0; //bags of corn used
	for(int index=0;index<n_cows-1;index++){
		if(cows[index]==cows[index+1]) continue;
		if(cows[index]<cows[index+1]){
			if(index<n_cows-2){
				count+=cows[index+1]-cows[index];
				cows[index+2]-=cows[index+1]-cows[index];
				if(cows[index+2]<0){
					cout << -1 << '\n';
					return;
				}
				cows[index+1]=cows[index];
			}else{
				cout << -1 << '\n';
				return;
			}
		}else{
			if(index>0 && index%2>0){
				//even = all can be decremented
				//(index+1)/2 pairings
				long long diff=cows[index]-cows[index+1];
				count+=diff*(index+1)/2;
				if(cows[0]<diff){
					cout << -1 << '\n';
					return;
				}
				for(int i=0;i<=index;i++) cows[i]-=diff;
			}else{
				cout << -1 << '\n';
				return;
			}
		}
	}
	cout << count*2 << '\n';
}

int main(){
	int cases;
	cin >> cases;
	for(int j=0;j<cases;j++){
		test_case();
	}
	return 1;
}
