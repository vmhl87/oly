#include <iostream>
#include <queue>
using namespace std;

typedef struct student{
	int p,s,k,t;
	bool operator>(const student &o)const{
		if(o.p<p)return 1;
		if(o.t==t&&s<o.s)return 1;
		return 0;
	}
}student;

int main(){
	priority_queue<student> q;
	q.emplace(
}
