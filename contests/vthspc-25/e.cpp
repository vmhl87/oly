#include <iostream>

void test(){
	int hour, min; char c, d;
	std::cin >> hour >> c >> min;// >> c;
	int hour_off, min_off, dst1, dst2;
	// std::cin >> hour_off >> d >> min_off >> dst1 >> dst2;
	float off;
	std::cin >> off >> dst1 >> dst2;

	int time = hour*60 + min
		// + (c == '+' ? 1 : -1)*(hour_off*60 + (min_off*3)/5)
		+ off*60
		+ 60*(dst2-dst1);

	while(time >= 24*60) time -= 24*60;
	while(time < 0) time += 24*60;

	std::cout << time/600 << (time/60)%10 << ':'
		<< (time%60)/10 << time%10 << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
