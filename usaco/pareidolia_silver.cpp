#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;cin>>s;
	long long clef=s.length(),ret=0,
		x=0,b=0,e=0,s1=0,s2=0,i=0;
	for(char c:s){
		if(c=='b'){
			b+=x+1;x=0;
		}else if(c=='e'){
			e+=b;b=0;
			ret+=i*clef;
			x+=i+1;i=0;
		}else if(c=='s'){
			s2+=s1;s1=0;s1+=e;e=0;
			x++;
		}else if(c=='i'){
			i+=s2;s2=0;
			x++;
		}else x++;
		clef--;
	}
	cout<<ret<<'\n';
}
