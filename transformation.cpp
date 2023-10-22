#include <iostream>
using namespace std;

int len;
bool tmp[100];

bool* rotate(bool* a){
	bool t[len*len];
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++){
			t[i+j*len]=a[j+(len-i-1)*len];
		}
	for(int i=0;i<len*len;i++)tmp[i]=t[i];
	return tmp;
}

bool* reflect(bool* a){
	bool t[len*len];
	for(int i=0;i<len;i++)
		for(int j=0;j<len;j++){
			t[i+j*len]=a[len-i-1+j*len];
		}
	for(int i=0;i<len*len;i++)tmp[i]=t[i];
	return tmp;
}

bool is_equal(bool* a,bool* b){
	for(int i=0;i<len*len;i++)if(a[i]!=b[i])return false;
	return true;
}

int main(){
	cin>>len;
	bool a[len*len],b[len*len];char c;
	for(int i=0;i<len*len;i++){cin>>c;a[i]=(c=='@');}
	for(int i=0;i<len*len;i++){cin>>c;b[i]=(c=='@');}
	if(is_equal(rotate(a),b))cout<<1;
	else if(is_equal(a,b))cout<<6;
	else if(is_equal(rotate(rotate(a)),b))cout<<2;
	else if(is_equal(rotate(rotate(rotate(a))),b))cout<<3;
	else if(is_equal(reflect(a),b))cout<<4;
	else if(
		is_equal(reflect(a),rotate(b))||
		is_equal(reflect(a),rotate(rotate(b)))||
		is_equal(reflect(a),rotate(rotate(rotate(b))))
	)cout<<5;
	else cout<<7;
	cout<<'\n';return 0;
}

/*

3
@-@
---
@@-
@-@
@--
--@

3
@-@
---
@@-
-@@
---
@-@

3
@-@
---
@@-
@--
--@
@-@

*/
