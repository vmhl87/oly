#include <iostream>

const int N = 1e3;

double x[N], y[N], s[N];
bool r[N];

void test(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i){
		std::cin >> x[i] >> y[i] >> s[i];
		std::string R; std::cin >> R;
		r[i] = R[0] == 'a';
	}

	for(int _X=-50; _X<50; ++_X){
		for(int _Y=-50; _Y<50; ++_Y){
			float X = _X+0.5, Y = _Y+0.5;

			double _l = 1, _r = 1e6;

			for(int i=0; i<n; ++i){
				double mid = s[i]
					*((x[i]-X)*(x[i]-X) + (y[i]-Y)*(y[i]-Y));

				if(r[i]) _l = std::max(_l, mid);
				else _r = std::min(_r, mid);

				if(_l > _r) break;
			}

			if(_l <= _r){
				std::cout << _X << ' ' << _Y << ' '
					<< _X+1 << ' ' << _Y+1 << '\n';
				return;
			}
		}
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
