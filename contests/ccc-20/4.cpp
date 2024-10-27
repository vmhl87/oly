#include <iostream>
#include <string>
#include <array>

std::string s;
int map[3][3], n;

void out(){
	for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j)
			std::cout << map[i][j] << " \n"[j==2];
}

void rem(int p, int v){
	if(p >= n) p -= n;
	--map[s[p]-'A'][v];
}

void add(int p, int v){
	if(p >= n) p -= n;
	++map[s[p]-'A'][v];
}

int cost(){
	int m[3][3];
	for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j)
			m[i][j] = map[i][j];

	int res = 0, com;

	com = std::min(m[0][1], m[1][0]);
	res += com, m[0][1] -= com, m[1][0] -= com;

	com = std::min(m[1][2], m[2][1]);
	res += com, m[1][2] -= com, m[2][1] -= com;

	com = std::min(m[2][0], m[0][2]);
	res += com, m[2][0] -= com, m[0][2] -= com;

	res += m[0][1]*2 + m[1][0]*2;

	return res;
}

std::array<int, 3> maps[2] = {{0, 1, 2}, {2, 1, 0}};

int main(){
	std::cin >> s, n = s.length();

	int ct[3] = {}, best;
	for(char x : s) ++ct[x-'A'];

	bool nset = 1;

	for(auto r : maps){
		for(int i=0; i<3; ++i)
			for(int j=0; j<3; ++j)
				map[i][j] = 0;

		for(int i=0; i<ct[r[0]]; ++i)
			++map[s[i]-'A'][r[0]];

		for(int i=0; i<ct[r[1]]; ++i)
			++map[s[ct[r[0]]+i]-'A'][r[1]];

		for(int i=0; i<ct[r[2]]; ++i)
			++map[s[ct[r[0]]+ct[r[1]]+i]-'A'][r[2]];

		//out();

		best = (nset ? cost() : std::min(best, cost()));
		nset = 0;

		for(int i=0; i<n; ++i){
			rem(i, r[0]);
			rem(i+ct[r[0]], r[1]);
			rem(i+ct[r[0]]+ct[r[1]], r[2]);
			
			add(i, r[2]);
			add(i+ct[r[0]], r[0]);
			add(i+ct[r[0]]+ct[r[1]], r[1]);

			best = std::min(best, cost());

			//std::cout << "index " << i << ' ' << cost() << '\n';
			//out();
		}
	}

	std::cout << best << '\n';
}
