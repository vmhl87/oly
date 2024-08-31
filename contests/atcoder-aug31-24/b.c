#include <stdio.h>

int abs(int x) { if(x<0) return -x; return x; }

int main(){
	int n; scanf("%d", &n);
	int ans = 0, l = 0, r = 0, ls = 0, rs = 0;

	while(n--){
		int p; char c; scanf("%d %c", &p, &c);
		if(c=='L'){
			if(ls) ans += abs(l-p);
			l = p, ls = 1;
		}else{
			if(rs) ans += abs(r-p);
			r = p, rs = 1;
		}
	}

	printf("%d\n", ans);
}
