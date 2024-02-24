#include <iostream>
#include <cmath>
using namespace std;

double area(double w){
	return w*w*sqrt(3)/4;
}

void form(double w){
	w*=100;int r=round(w);
	int h=r/100;
	cout<<h<<'.';
	int t=(r/10)%10;
	cout<<t<<r%10;
	cout<<'\n';
}

void test_case(){
	double w,n;cin>>w>>n;
	cout<<pow(3.0,n)<<' ';
	form(area(w)*pow(.75,n));
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}

/*
import math

def area(v):
	return v*v*math.sqrt(3)/4

def fr(v):
	x = str(v)
	
	return x[:-2]+'.'+x[-2:]

def test_case():
	t = [int(i) for i in input().split(' ')]
	
	print(str(3**t[1]) + ' ' + fr(round(100*(area(t[0])*(.75**t[1])))))

t = int(input())

for i in range(t):
	test_case()
*/
