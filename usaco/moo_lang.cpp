#include <iostream>
#include <string>
using namespace std;

#define DEBUG false

void test_case(){
	int N,m,p,i=0,t=0,n=0,c=0;cin>>N>>m>>p;
	string is[N],ts[N],ns[N],cs[N];
	for(int j=0;j<N;j++){
		string h,w;cin>>h>>w;
		if(w[0]=='n'){
			ns[n]=h;n++;
		}else if(w[0]=='t'){
			ts[t]=h;t++;
		}else if(w[0]=='i'){
			is[i]=h;i++;
		}else{
			cs[c]=h;c++;
		}
	}
	int on=n,ot=t,oi=i;
	/* how does this even work again
		limited by # of sentences (periods)
		n i n i n i VS
		n t n n t n n t n - i is more efficient in terms
		of pairing with n
		
		first fill in all nouns, and match i's to them
		n   n   n   n   n   n   n
		n i n i n i n   n   n   n
		then fill in t's on empty spaces
		n i n i n i n t n   n t n
		i is always more efficient than t when taking n's as
		a baseline
		what if odd empty n?
		n i n i n i n   n   n
		n i n i n i n t n  _n VS
		n i n i n t n   n t n
		
		how to deal with bounds on sentence #?
		start with empty arr
		_ _ _ _ _ _ (6 sent)
		fill with ni
		n=7 i=3 t=3
		ni ni ni _ _ _
		fill with ntn
		ni ni ni ntn ntn _
		
		what if only 4 sent
		ni ni ni _
		ni ni ni ntn
		in this case, we have enough nt to add another ntn
		we could also pile more n's
		ni ni ntn ntn
		ni ni ni ntnn
		we still have enough nt
		ni ntn ntn ntn
		this is probably optimal
		
		what if n8 i3 t3  s6
		ni ni ni _ _ _
		fill ntn
		ni ni ni _ _ ntn
		ni ni ni _ ntn ntn
		ni ni ni n ntn ntn - what to do
		pile n on some ntn
		ni ni ni ntn ntnn _
		
		max sentences: min(periods * 2, periods + conjunc)
		
		ni ni ntn
	*/
	int ms=min(p+p,p+c);
	int sent[ms];//0=none 1=ni 2=ntn 3=ntnn etc
	for(int h=0;h<ms;h++)sent[h]=0;
	// fill ni
	for(int h=0;h<ms;h++){
		if(oi==0||on==0)break;
		sent[h]=1;oi--;on--;
	}
	// fill ntn (from back)
	for(int h=ms-1;h>-1;h--){
		if(ot==0)break;
		if(sent[h]>0){
			if(on==0)break;on++;oi++;
		}else if(on<2)break;
		sent[h]=2;on-=2;ot--;
	}
	// weird edge case
	if(ot>0&&on>0&&sent[0]==1){
		sent[0]=2;ot--;on--;
	}
	// fill n
	if(sent[ms-1]==2){
		sent[ms-1]+=min(on,p);
	}else if(sent[0]==2){
		sent[0]+=min(on,p);
	}else{// no t added
		if(sent[0]==1&&on>0){
			sent[0]=2+min(on-1,p);
		}
	}
	int sn=0,st=0;
	for(int h=0;h<ms;h++){
		if(sent[h]==1)sn+=2;
		else if(sent[h]>1)sn+=sent[h]+1;
		if(sent[h]>0)st++;
		if(!DEBUG)continue;
		if(sent[h]==0)cout<<'_';
		else if(sent[h]==1)cout<<"ni";
		else{
			cout<<"ntn";for(int j=2;j<sent[h];j++)cout<<'n';
		}
		cout<<' ';if(h==ms-1)cout<<'\n';
	}
	sn+=min(c,st/2);
	cout<<sn<<'\n';i--;n--;t--;c--;
	for(int h=0;h<ms;h++){
		if(sent[h]==0)continue;
		if(h>0)cout<<' ';
		if(sent[h]==1){
			cout<<ns[n]<<' '<<is[i];
			n--;i--;
		}else{
			cout<<ns[n]<<' '<<ts[t]<<' '<<ns[n-1];
			for(int j=2;j<sent[h];j++)cout<<", "<<ns[n-j];
			n-=sent[h];t--;
		}
		if(c<0||h%2==1||h==ms-1)cout<<'.';
		else{
			cout<<' '<<cs[c];
			c--;
		}
	}cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
	return 0;
}
