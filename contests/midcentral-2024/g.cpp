#include <iostream>
#include <array>
#include <queue>

char a[10][10];
int r, c;

bool vis[160000];

std::array<int, 2> mov[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int pack2(int x1, int y1, int x2, int y2, int w, int x, int y, int z){
	return x1 + y1*10 + x2*100 + y2*1000 + w*10000 + x*20000 + y*40000 + z*80000;
}

struct S{
	int x1, y1, x2, y2, A, B, C, D;
};

int pack(S s){
	return pack2(s.x1, s.y1, s.x2, s.y2, s.A, s.B, s.C, s.D);
}

S unpack(int state){
	return {state%10, (state/=10)%10, (state/=10)%10, (state/=10)%10,
		(state/=10)&1, (state/=2)&1, (state/=2)&1, (state/=2)&1};
}

bool win(S s){
	return a[s.x1][s.y1] == 'E' && a[s.x2][s.y2] == 'E';
}

char get(int i, int j){
	if(i >= 0 && i < r && j >= 0 && j < c)
		return a[i][j];
	else return '*';
}

bool go1(S s, std::array<int, 2> m){
	char c = get(s.x1 + m[0], s.y1 + m[1]);

	if(c == '#') return 0;
	if(c == 'a' && s.A) return 0;
	if(c == 'b' && s.B) return 0;
	if(c == 'c' && s.C) return 0;
	if(c == 'd' && s.D) return 0;
	if(c == 'A' && !s.A) return 0;
	if(c == 'B' && !s.B) return 0;
	if(c == 'C' && !s.C) return 0;
	if(c == 'D' && !s.D) return 0;

	return 1;
}

bool go2(S s, std::array<int, 2> m){
	char c = get(s.x2 + m[0], s.y2 + m[1]);

	if(c == '#') return 0;
	if(c == 'a' && s.A) return 0;
	if(c == 'b' && s.B) return 0;
	if(c == 'c' && s.C) return 0;
	if(c == 'd' && s.D) return 0;
	if(c == 'A' && !s.A) return 0;
	if(c == 'B' && !s.B) return 0;
	if(c == 'C' && !s.C) return 0;
	if(c == 'D' && !s.D) return 0;

	return 1;
}

S move(S s, std::array<int, 2> m){
	S res = s;
	if(go1(s, m)){
		res.x1 += m[0], res.y1 += m[1];
		if(get(res.x1, res.y1) == '1') res.A ^= 1;
		if(get(res.x1, res.y1) == '2') res.B ^= 1;
		if(get(res.x1, res.y1) == '3') res.C ^= 1;
		if(get(res.x1, res.y1) == '4') res.D ^= 1;
	}
	if(go2(s, m)){
		res.x2 += m[0], res.y2 += m[1];
		if(get(res.x2, res.y2) == '1') res.A ^= 1;
		if(get(res.x2, res.y2) == '2') res.B ^= 1;
		if(get(res.x2, res.y2) == '3') res.C ^= 1;
		if(get(res.x2, res.y2) == '4') res.D ^= 1;
	}
	return res;
}

bool valid(S s){
	return (s.x1 != s.x2 || s.y1 != s.y2) &&
		get(s.x1, s.y1) != '*' && get(s.x2, s.y2) != '*' &&
		go1(s, {0, 0}) && go2(s, {0, 0});
}

int main(){
	std::cin >> r >> c;

	for(int i=0; i<r; ++i)
		for(int j=0; j<c; ++j)
			std::cin >> a[i][j];

	std::vector<std::array<int, 2>> p;

	for(int i=0; i<r; ++i)
		for(int j=0; j<c; ++j)
			if(a[i][j] == 'S')
				p.push_back({i, j});

	std::queue<std::array<int, 2>> q;

	q.push({pack2(p[0][0], p[0][1], p[1][0], p[1][1], 0, 0, 0, 0), 0});

	while(q.size()){
		int state = q.front()[0],
			r = q.front()[1];
		
		q.pop();

		if(vis[state]) continue;
		vis[state] = 1;

		S s = unpack(state);

		if(win(s)) std::cout << r << '\n', exit(0);

		for(auto x : mov){
			S next = move(s, x);
			if(valid(next)) q.push({pack(next), r+1});
		}
	}
}
