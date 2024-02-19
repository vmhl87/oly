#pragma GCC optimize("O3,unroll-all-loops")
#pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt")
#include <cstdio>
#define int long long
#define max(a,b) a>b?a:b
char _i[1 << 24], _o[1 << 24], _, __[16]; int _i0, _o0, t;
#define in(x) { if(_i[_i0] == '-'){ t = -1 ; _i0++; }else{ t = 1; } for (x = _i[_i0++] & 15; 47 < (_ = _i[_i0++]); x = x * 10 + (_ & 15)); x*=t;}
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
