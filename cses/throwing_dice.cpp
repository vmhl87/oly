#include <iostream>
#include <vector>
using namespace std;

#define M 1000000007

vector<long long> base={
	1, 1, 2, 4, 6, 12,
	1, 2, 3, 6, 12, 24,
	1, 2, 4, 7, 14, 28,
	1, 2, 4, 8, 15, 30,
	1, 2, 4, 8, 16, 31,
	1, 2, 4, 8, 16, 32
},id={
	1, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0,
	0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 1
};

vector<long long> vmul(vector<long long> v,vector<long long>mat){
	vector<long long> ret(6);
	for(int i=0;i<6;++i)
		for(int j=0;j<6;++j)
			ret[i]+=(v[j]*mat[j*6+i])%M;
	for(int i=0;i<6;++i)ret[i]%=M;
	return ret;
}

vector<long long> mmul(vector<long long> m1,vector<long long> m2){
	vector<long long> ret(36);
	for(int i=0;i<6;++i)
		for(int j=0;j<6;++j)
			for(int a=0;a<6;++a)
				ret[i*6+j]+=(m1[i*6+a]*m2[a*6+j])%M;
	for(int i=0;i<36;++i)ret[i]%=M;
	return ret;
}

vector<long long> vexp(vector<long long> v,vector<long long> mat,long long iter){
	for(long long i=0;i<iter;++i)v=vmul(v,mat);
	return v;
}

vector<long long> bexp(vector<long long> v,vector<long long> mat,long long iter){
	long long p=1;
	while(p<=iter){
		if(p&iter)v=vmul(v,mat);
		mat=mmul(mat,mat);
		p<<=1;
	}
	return v;
}

long long bfr(long long n){
	long long val[6]={0,0,0,0,0,1};
	for(long long i=0;i<n;++i){
		long long next=0;
		for(long long x:val)next+=x;
		next%=M;
		for(long long i=0;i<5;++i)
			val[i]=val[i+1];
		val[5]=next;
	}
	return val[5];
}

int main(){
	long long n;cin>>n;
	vector<long long> v={0,0,0,0,0,1};
	v=bexp(v,base,1+(n-1)/6);
	cout<<v[(n-1)%6]<<'\n';
	vector<long long> r={0,0,0,0,0,1};
	r=vexp(r,base,1+(n-1)/6);
	cout<<r[(n-1)%6]<<'\n';
	cout<<bfr(n)<<'\n';
}
