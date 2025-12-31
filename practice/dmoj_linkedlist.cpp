// https://dmoj.ca/problem/linked
// memory management for this problem is really annoying
// array uses 8mb & syslibs use another couple of megabytes
// switching to cstdio was necessary to get my sol to pass

#include <stdio.h>

// the idea is to use the following two optimizations:
// 1. store pointers as array indices (20 bits)
// 2. instead of storing both the left and right pointers,
// store their xor. then as long as you keep explicit track
// of the index, left index, and right index it is possible
// to move left and right easily

// instead of implementing generic garbage collection I found
// it easier to treat the far end of the list as a stack of
// unused nodes; this necessitated storing a second set of
// [left index, index, right index]

constexpr int n = 1e6 + 10;
long long a[n];
int p1 = 0, l1 = 0, r1 = 1;
int p2 = n-1, l2 = n-2, r2 = n;

void set(int p, int l, long long v, int r){
	a[p] = (v<<20) | (l^r);
}

long long get(int p, int i){
	if(i == 0) return a[p] >> 20;
	return a[p] & ((1<<20) - 1);
}

int main(){
	set(0, 0, -1, 1);
	for(int i=1; i<n; ++i) set(i, i-1, -1, i+1);

	int m; scanf("%d", &m);

	while(m--){
		char c; scanf("%c", &c);
		while(c == ' ' || c == '\n') scanf("%c", &c);

		if(c == '>'){
			r1 = p1, p1 = l1;
			l1 = get(p1, 1)^r1;

		}else if(c == '<'){
			l1 = p1, p1 = r1;
			r1 = get(p1, 1)^l1;

		}else if(c == '='){
			long long v; scanf("%lld", &v), set(p1, l1, v, r1);

		}else if(c == '+'){
			long long v; scanf("%lld", &v);

			int next = p2;
			
			r2 = p2, p2 = l2;
			l2 = get(p2, 1)^r2;

			set(p1, l1, get(p1, 0), next);
			set(next, p1, v, r1);
			set(r1, next, get(r1, 0), get(r1, 1)^p1);

			l1 = p1, p1 = next;

		}else if(c == '-'){
			int old = p1;

			set(l1, get(l1, 1)^p1, get(l1, 0), r1);
			set(r1, l1, get(r1, 0), get(r1, 1)^p1);
			
			p1 = l1, l1 = get(l1, 1)^r1;

			set(p2, l2, -1, old);
			set(old, p2, -1, old);
			l2 = p2, p2 = old, r2 = old;

		}else if(c == '!') printf("%lld\n", get(p1, 0));
	}
}

constexpr int n = 1e6 + 10;
long long a[n];
int p1 = 0, l1 = 0, r1 = 1;
int p2 = n-1, l2 = n-2, r2 = n;

void set(int p, int l, long long v, int r){
	a[p] = (v<<20) | (l^r);
}

long long get(int p, int i){
	if(i == 0) return a[p] >> 20;
	return a[p] & ((1<<20) - 1);
}

int main(){
	set(0, 0, -1, 1);
	for(int i=1; i<n; ++i) set(i, i-1, -1, i+1);

	int m; scanf("%d", &m);

	while(m--){
		char c; scanf("%c", &c);
		while(c == ' ' || c == '\n') scanf("%c", &c);

		if(c == '>'){
			r1 = p1, p1 = l1;
			l1 = get(p1, 1)^r1;

		}else if(c == '<'){
			l1 = p1, p1 = r1;
			r1 = get(p1, 1)^l1;

		}else if(c == '='){
			long long v; scanf("%lld", &v), set(p1, l1, v, r1);

		}else if(c == '+'){
			long long v; scanf("%lld", &v);

			int next = p2;
			
			r2 = p2, p2 = l2;
			l2 = get(p2, 1)^r2;

			set(p1, l1, get(p1, 0), next);
			set(next, p1, v, r1);
			set(r1, next, get(r1, 0), get(r1, 1)^p1);

			l1 = p1, p1 = next;

		}else if(c == '-'){
			int old = p1;

			set(l1, get(l1, 1)^p1, get(l1, 0), r1);
			set(r1, l1, get(r1, 0), get(r1, 1)^p1);
			
			p1 = l1, l1 = get(l1, 1)^r1;

			set(p2, l2, -1, old);
			set(old, p2, -1, old);
			l2 = p2, p2 = old, r2 = old;

		}else if(c == '!') printf("%lld\n", get(p1, 0));
	}
}
