#include <iostream>

int d[1<<20], n, t, x, y, i, j, m, w[8][2] = {
	{1, 2}, {2, 1}, {-1, 2}, {-2, 1},
	{1, -2}, {2, -1}, {-1, -2}, {-2, -1}
}, r[1<<20], *q = r, *z = r;

bool b(int x, int y){
	return x>=0 && y>=0 && x<n && y<n;
}

main(){
	std::cin >> n;

	d[0] = 1; *z++ = 0;

	while(q<z){
		t = *q++;
		x = t%n; y=t/n;

		for(i=0; i<8; ++i) if(b(x+w[i][0], y+w[i][1])){
			m = x+w[i][0]+(y+w[i][1])*n;
			if(!d[m]) d[m] = d[t]+1, *z++ = m;
		}
	}

	for(i=0; i<n; ++i) for(j=0; j<n; ++j)
		std::cout << d[i*n+j]-1 << " \n"[j==n-1];
}
