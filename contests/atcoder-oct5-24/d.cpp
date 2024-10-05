#include <iostream>
#include <iomanip>
#include <array>
#include <cmath>

using ll = long long;

std::array<int, 4> p[6];
double s, t;
int n;

bool use[6];
double opt = -1;

void permute(int d, ll x, ll y, double sum){
	if(d == 6){
		if(opt < 0 || sum < opt) opt = sum;
	}else{
		for(int i=0; i<6; ++i) if(!use[i]){
			use[i] = 1;
			double cost = sqrt((x-p[i][0])*(x-p[i][0]) + (y-p[i][1])*(y-p[i][1]))/s +
				sqrt((p[i][0]-p[i][2])*(p[i][0]-p[i][2]) + (p[i][1]-p[i][3])*(p[i][1]-p[i][3]))/t;
			permute(d+1, p[i][2], p[i][3], sum+cost);
			cost = sqrt((x-p[i][2])*(x-p[i][2]) + (y-p[i][3])*(y-p[i][3]))/s +
				sqrt((p[i][0]-p[i][2])*(p[i][0]-p[i][2]) + (p[i][1]-p[i][3])*(p[i][1]-p[i][3]))/t;
			permute(d+1, p[i][0], p[i][1], sum+cost);
			use[i] = 0;
		}
	}
}

int main(){
	std::cout << std::setprecision(20);
	std::cin >> n >> s >> t;
	for(int i=0; i<n; ++i)
		std::cin >> p[i][0] >> p[i][1] >> p[i][2] >> p[i][3];

	permute(0, 0, 0, 0);

	std::cout << opt << '\n';
}
