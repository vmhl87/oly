#pragma GCC optimize("O3,unroll-all-loops")
#pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")
#include <cstdio>
#define int long long
#define max(a,b) a>b?a:b
//  assume: _i is char buffer, _i0 is parse location when reading in \
	t is sign buffer
//  _o seems to be output buffer, _ and __ are for printing a whole integer
char _i[1 << 24], _o[1 << 24], _, __[16]; int _i0, _o0, t;
/*
	the &15 zeroes out all except the lower 4 bits, turning char into int -
	this is faster than subtracting char 48

	in(x){
		if current char is -: t starts at -1, else starts at 1
		for(x starting at char&15; char is number; append char to x)
		multiply x by sign bit
	}
*/
#define in(x) { if(_i[_i0] == '-'){ t = -1 ; _i0++; }else{ t = 1; } for (x = _i[_i0++] & 15; 47 < (_ = _i[_i0++]); x = x * 10 + (_ & 15)); x*=t;}
/*
	out(x){
		if x is negative: flip sign of x and print a '-' char
		while x has digits, append them to __
		while __ has digits, append them to _o
		write a newline to _o
	}
*/
#define out(x) { if(x<0){_o[_o0++]='-';x=-x;}_ = 0; do {__[_++] = x % 10 | '0'; } while ( x *= 0.1 ); while (_--) _o[_o0++] = __[_]; _o[_o0++] = '\n';}
main(){
    fread(_i, 1, 1 << 24, stdin);
    int N,curr,res,x;
    in(N);
    in(curr);res=curr;
    for(int i=1;i<N;++i){
        in(x);
        curr=max(curr+x,x);
        if(res<curr) res=curr;
    }
    out(res);
    fputs(_o, stdout);
	return 0;
}
