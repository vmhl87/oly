#include <iostream>
#include <vector>

int h, w, res;

std::vector<int> rowtrees[400000], coltrees[400000];
std::vector<std::vector<int>> has;

int rowsum(int r, int c1, int c2){
	int res = 0;
	for(c1+=w+10,c2+=w+10; c1<c2; c1/=2, c2/=2){
		if(c1&1) res += rowtrees[r][c1++];
		if(c2&1) res += rowtrees[r][--c2];
	}
	return res;
}

int colsum(int r1, int r2, int c){
	int res = 0;
	for(r1+=h+10,r2+=h+10; r1<r2; r1/=2,r2/=2){
		if(r1&1) res += coltrees[c][r1++];
		if(r2&1) res += coltrees[c][--r2];
	}
	return res;
}

void rowsub(int r, int c){
	for(c+=w+10; c; c/=2) --rowtrees[r][c];
}

void colsub(int r, int c){
	for(r+=h+10; r; r/=2) --coltrees[c][r];
}

int samerow(int r1, int c1, int r2, int c2){
	if(r2<0 || r2>=h) return 0;
	if(c2<0 || c2>=w) return 0;
	if(c1<c2) return rowsum(r1, c1, c2+1) == 0;
	return rowsum(r1, c2, c1+1) == 0;
}

int samecol(int r1, int c1, int r2, int c2){
	if(r2<0 || r2>=h) return 0;
	if(c2<0 || c2>=w) return 0;
	if(r1<r2) return colsum(r1, r2+1, c1) == 0;
	return colsum(r2, r1+1, c1) == 0;
}

void set(int r, int c){
	if(r<0 || c<0 || r>=h || c>=w) return;
	if(has[r][c]) --res;
	rowsub(r, c), colsub(r, c);
	has[r][c] = 0;
}

int main(){
	int q; std::cin >> h >> w >> q;
	res = h*w;

	has.resize(h, std::vector(w, 1));

	for(int i=0; i!=h; ++i){
		rowtrees[i].resize(w*2+14, 1);
		for(int j=w+7; j; --j) rowtrees[i][j] = rowtrees[i][j*2] + rowtrees[i][j*2+1];
	}
	for(int i=0; i!=w; ++i){
		coltrees[i].resize(h*2+14, 1);
		for(int j=h+7; j; --j) coltrees[i][j] = coltrees[i][j*2] + coltrees[i][j*2+1];
	}

	while(q--){
		int r, c; std::cin >> r >> c, --r, --c;
		if(has[r][c]) set(r, c);
		else{
			int p = r;
			for(int i=19; i>=0; --i)
				if(samecol(r, c, p+(1<<i), c)) p += 1<<i;
			set(p+1, c);
			p = r;
			for(int i=19; i>=0; --i)
				if(samecol(r, c, p-(1<<i), c)) p -= 1<<i;
			set(p-1, c);
			p = c;
			for(int i=19; i>=0; --i)
				if(samerow(r, c, r, p+(1<<i))) p += 1<<i;
			set(r, p+1);
			p = c;
			for(int i=19; i>=0; --i)
				if(samerow(r, c, r, p-(1<<i))) p -= 1<<i;
			set(r, p-1);
		}
	}

	std::cout << res << '\n';
}
