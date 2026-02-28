#include <iostream>
#include <cmath>

void test(){
	double x0, y0, v0, th0, x1, y1, v1, th1;
	std::cin >> x0 >> y0 >> v0 >> th0 >> x1 >> y1 >> v1 >> th1;

	th0 *= M_PI / 180.0;
	th1 *= M_PI / 180.0;

	double vx0 = v0 * std::cos(th0),
		   vy0 = v0 * std::sin(th0);

	double vx1 = v1 * std::cos(th1),
		   vy1 = v1 * std::sin(th1);

	if(x0 > x1) vx0 *= -1;
	if(x1 > x0) vx1 *= -1;

	double g = -9.8;

	double a = (0.5*g/vx0/vx0 - 0.5*g/vx1/vx1);
	double b = (vy0/vx0 - x0*g/vx0/vx0 - vy1/vx1 + x1*g/vx1/vx1);
	double c = x0*x0*0.5*g/vx0/vx0 - x0*vy0/vx0 + y0 - x1*x1*0.5*g/vx1/vx1 + x1*vy1/vx1 - y1;

	if(b*b < 4.0*a*c) { std::cout << "TAKE COVER\n"; return; }

	double cx0 = -0.5*b/a + std::sqrt(b*b - 4.0*a*c)/2.0/a;
	double cx1 = -0.5*b/a - std::sqrt(b*b - 4.0*a*c)/2.0/a;

	if(cx0 >= std::min(x0, x1) && cx0 <= std::max(x0, x1)){
		if(0.5*g*(cx0-x0)*(cx0-x0)/vx0/vx0 + vy0*(cx0-x0)/vx0 + y0 >= 0.0){
			double lt = (cx0-x1)/vx1 - (cx0-x0)/vx0;
			if(lt >= 0.0){
				int v = std::round(lt*10.0);
				std::cout << v/10 << '.' << v%10 << '\n';
				return;
			}
		}
	}
	
	cx0 = cx1;

	if(cx0 >= std::min(x0, x1) && cx0 <= std::max(x0, x1)){
		if(0.5*g*(cx0-x0)*(cx0-x0)/vx0/vx0 + vy0*(cx0-x0)/vx0 + y0 >= 0.0){
			double lt = (cx0-x1)/vx1 - (cx0-x0)/vx0;
			if(lt >= 0.0){
				int v = std::round(lt*10.0);
				std::cout << v/10 << '.' << v%10 << '\n';
				return;
			}
		}
	}

	std::cout << "TAKE COVER\n";
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
