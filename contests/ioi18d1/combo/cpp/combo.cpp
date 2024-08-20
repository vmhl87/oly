#include "combo.h"

// should be linear now
std::string guess_sequence(int N) {
	char init;
	std::string s;

	if(press("AB")){
		if(press("B")) init = 'B';
		else init = 'A';
	}else{
		if(press("X")) init = 'X';
		else init = 'Y';
	}

	s += init;

	std::string can[3], *p = can;
	for(char i : {'A', 'B', 'X', 'Y'}) if(i != init)
		(p++)[0] += i;

	while(s.length() < (uint)N){
		if(s.length() == (uint)N - 1){
			if((uint)press(s + can[0]) > s.length()) s += can[0][0];
			else if((uint)press(s + can[1]) > s.length()) s += can[1][0];
			else s += can[2][0];

			break;
		}

		// guess AA, AB, BB
		uint guess = press(s + can[0] + can[0] +
						  s + can[0] + can[1] +
						  s + can[1] + can[1]);

		// starts with X
		if(guess == s.length()){
			s += can[2][0];

		// any of AX, BA, BX
		}else if(guess == s.length() + 1){
			// guess BX
			guess = press(s + can[1] + can[2]);
			
			// is AX
			if(guess == s.length())
				s += can[0][0], s += can[2][0];

			// is BA
			else if(guess == s.length() + 1)
				s += can[1][0], s += can[0][0];

			// is BX
			else s += can[1][0], s += can[2][0];

		// any of AA, AB, BB
		}else{
			// guess AA
			guess = press(s + can[0] + can[0]);

			// is BB
			if(guess == s.length())
				s += can[1][0], s += can[1][0];

			// is AB
			else if(guess == s.length() + 1)
				s += can[0][0], s += can[1][0];

			// is AA
			else s += can[0][0], s += can[0][0];
		}
	}

	return s;
}
