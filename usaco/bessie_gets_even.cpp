/*

input values

calculate b_even, b_odd, i_even, i_odd, etc.

totalWays = (b_even + b_odd) * (i_even + i_odd) * etc.

bi_is_odd = (b_odd * i_even) + (b_even * i_odd) // either b is odd and i is even, or other way around

goes_is_odd = (g_odd * o_even * e_even * s_even) + (g_even * o_odd * e_even * s_even) + // 1 odd 3 even
			  (g_even * o_even * e_odd * s_even) + (g_even * o_even * e_even * s_odd) +
			  (g_odd * o_odd * e_odd * s_even) + (g_odd * o_odd * e_even * s_odd) +     // 3 odd 1 even
			  (g_odd * o_even * e_odd * s_odd) + (g_even * o_odd * e_odd * s_odd)

all_are_odd = bi_is_odd * goes_is_odd * m_is_odd

print totalWays - all_are_odd

*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main(){
	ifstream cin("geteven.in");
	ofstream cout("geteven.out");
	int n;cin>>n;
	long long b_even=0,b_odd=0,
		i_even=0,i_odd=0,
		g_even=0,g_odd=0,
		o_even=0,o_odd=0,
		e_even=0,e_odd=0,
		s_even=0,s_odd=0,
		m_even=0,m_odd=0;
	while(n-->0){
		char c;cin>>c;
		int t;cin>>t;
		if(c=='B'){
			if(t%2==0)b_even++;
			else b_odd++;
		}else if(c=='I'){
			if(t%2==0)i_even++;
			else i_odd++;
		}else if(c=='G'){
			if(t%2==0)g_even++;
			else g_odd++;
		}else if(c=='O'){
			if(t%2==0)o_even++;
			else o_odd++;
		}else if(c=='E'){
			if(t%2==0)e_even++;
			else e_odd++;
		}else if(c=='S'){
			if(t%2==0)s_even++;
			else s_odd++;
		}else{
			if(t%2==0)m_even++;
			else m_odd++;
		}
	}
	/*
		cout<<b_even<<' '<<b_odd<<'\n';
		cout<<i_even<<' '<<i_odd<<'\n';
		cout<<g_even<<' '<<g_odd<<'\n';
		cout<<o_even<<' '<<o_odd<<'\n';
		cout<<e_even<<' '<<e_odd<<'\n';
		cout<<s_even<<' '<<s_odd<<'\n';
		cout<<m_even<<' '<<m_odd<<'\n';
	*/
	long long total=(b_even+b_odd)*(i_even+i_odd)*(g_even+g_odd)*(o_even+o_odd)*
			(e_even+e_odd)*(s_even+s_odd)*(m_even+m_odd),
		bi=b_even*i_odd+b_odd*i_even,
		goes=(g_odd*o_even*e_even*s_even)+(g_even*o_odd*e_even*s_even)+
			(g_even*o_even*e_odd*s_even)+(g_even*o_even*e_even*s_odd)+
			(g_odd*o_odd*e_odd*s_even)+(g_odd*o_odd*e_even*s_odd)+
			(g_odd*o_even*e_odd*s_odd)+(g_even*o_odd*e_odd*s_odd);
	long long odd=bi*goes*m_odd;
	cout<<total-odd<<'\n';
	return 0;
}
