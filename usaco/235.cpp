#include <iostream>
using namespace std;

typedef struct ll* llptr;

struct ll{
	long long v;
	llptr next;
};

int main(){
	int N,n=0;
	cin>>N;
	int val[N];
	for(int i=0;i<N;i++){
		cin>>val[i];
		if(val[i]>n)n=val[i];
	}
	llptr head=new ll,s;
	head->v=1;
	llptr* cur=&head;
	for(int i=0;i<n;i++){
		long long f[3]={(*cur)->v*2,(*cur)->v*3,(*cur)->v*5};
		for(long long x:f){
			s=*cur;bool a=true;int in=i;
			while(s->next){
				if(++in>n){a=false;break;}
				if(x<=(s->next)->v){
					a=false;
					if(x==(s->next)->v)break;
					llptr tmp=s->next;
					s->next=new ll;
					(s->next)->v=x;
					(s->next)->next=tmp;
					break;
				}
				s=s->next;
			}
			if(a){
				s->next=new ll;
				(s->next)->v=x;
			}
		}
		cur=&(*cur)->next;
	}
	llptr p=head,vals[n];
	long long sum=0;int ct=0;
	while(p&&ct<n){
		vals[ct++]=p;
		p=p->next;	
	}
	for(int j=0;j<N;j++)sum+=vals[val[j]-1]->v;
	cout<<sum<<'\n';
	return 0;
}
