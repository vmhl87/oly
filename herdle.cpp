/*
pseudo init
*/

#include <iostream>
using namespace std;

int main(){
	char correct[3][3];
	char guess[3][3];
	int correct_count[26];
	int guess_count[26];
	int green = 0;
	for(int i=0;i<26;i++){
		correct_count[i] = 0;
		guess_count[i] = 0;
	}
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++){
			cin >> correct[i][j];
			correct_count[correct[i][j]-'A']++;
		}
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++){
			cin >> guess[i][j];
			if(guess[i][j]==correct[i][j]){
				green++;
				correct_count[correct[i][j]-'A']--;
			}else guess_count[guess[i][j]-'A']++;
		}
	cout << green << '\n';
	green = 0;
	for(int i=0;i<26;i++){
		green += min(correct_count[i], guess_count[i]);
	}
	cout << green << '\n';
	return 1;
}
