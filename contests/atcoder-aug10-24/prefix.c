#include <stdio.h>

int psum[101][101][101], a[100][100][100];
int part[101][101];

int main(){
	int n; scanf("%d", &n);

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			for(int k=0; k<n; ++k)
				scanf("%d", a[i][j]+k);

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j)
			for(int k=0; k<n; ++k){
				part[j+1][k+1] = a[i][j][k] +
					part[j][k+1] + part[j+1][k] -
					part[j][k];
				psum[i+1][j+1][k+1] = psum[i][j+1][k+1] + part[j+1][k+1];
			}
	}

	int q; scanf("%d", &q);

	while(q--){
		int lx, rx, ly, ry, lz, rz;
		scanf("%d %d %d %d %d %d", &lx, &rx, &ly, &ry, &lz, &rz);
		--lx, --ly, --lz;
		int ret = psum[rx][ry][rz] -
			(psum[rx][ry][lz] + psum[rx][ly][rz] + psum[lx][ry][rz]) +
			(psum[rx][ly][lz] + psum[lx][ry][lz] + psum[lx][ly][rz]) -
			psum[lx][ly][lz];
		printf("%d\n", ret);
	}
}
