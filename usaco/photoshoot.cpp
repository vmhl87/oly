#include <iostream>
using namespace std;

int main(){
	int n;cin>>n;
	bool cows[n];
	char c;
	for(int i=0;i<n;i++){
		cin>>c;cows[i]=(c=='G');
	}
	
}


/*
ex:

-   -   -
G G G H G H H G H H H G H G
  -           -       -   -

efficient computation for:
	gain(start, end) -> # of G in even spots gained btw s,e
	lose(start, end) -> same but for lose instead of gain

    both can be efficiently implemented by storing a register of gain,loss up to
    cell n from 0 and subtractions

then use greedy alg and iteratively find best s,e such that
gain(s,e) - lose(s,e) is maximized
*/
