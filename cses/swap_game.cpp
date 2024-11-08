#include <unordered_set>
#include <iostream>

struct board{
	int v[9];
	int mov = 0, dist = 0;

	int distance() const{
		return dist + mov*2;
	}

	bool done() const{
		return dist == 0;
	}

	void set(){
		for(int i=0; i<9; ++i)
			if(v[i] != i+1) ++dist;
	}

	void swap(int x1, int y1, int x2, int y2){
		dist -= v[x1+y1*3] != x1+y1*3+1;
		dist -= v[x2+y2*3] != x2+y2*3+1;
		std::swap(v[x1+y1*3], v[x2+y2*3]);
		dist += v[x1+y1*3] != x1+y1*3+1;
		dist += v[x2+y2*3] != x2+y2*3+1;
	}

	const bool operator<(const board o) const{
		return distance() > o.distance();
	}
};

std::unordered_set<int> seen;
std::queue<board> ast;

void add(board x){
	int el = 0;
	for(int i=0; i<9; ++i) el = el*10 + x.v[i];

	if(seen.count(el)) return;

	seen.insert(el);
	ast.push(x);
}

int main(){
	board b;
	for(int i=0; i<9; ++i) std::cin >> b.v[i];
	b.set();

	ast.push(b);

	while(ast.size()){
		board x = ast.front(); ast.pop();

		if(x.done()) std::cout << x.mov << '\n', exit(0);

		++x.mov;

		for(int a=0; a<3; ++a)
			for(int b=0; b<3; ++b){
				if(a<2){
					x.swap(a, b, a+1, b);
					add(x);
					x.swap(a, b, a+1, b);
				}
				if(b<2){
					x.swap(a, b, a, b+1);
					add(x);
					x.swap(a, b, a, b+1);
				}
			}
	}
}
