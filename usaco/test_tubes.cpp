#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef struct{
	int a;
	int b;
}op;

op nop(int x,int y){
	op t;t.a=x;t.b=y;
	return t;
}

typedef struct{
	int t[2];
	int l[2]={0,0};
	int loc[2]={0,0};
	int buc=0;
	queue<op> ops;
}conf;

int recur(conf *c){
	if(c->l[0]==1&&c->l[1]==1&&c->buc==0)return 0;
	int ret=0;
	if(!c->loc[0]){
		if(c->t[0]==c->t[1]){
			c->loc[2-c->t[0]]=3;
			if(c->l[0]%2==1)c->loc[c->t[0]-1]=2;
			else c->loc[c->t[0]-1]=1;
		}else{
			if(c->l[0]%2==0){
				c->loc[c->t[0]-1]=3;
				c->loc[2-c->t[0]]=2;
			}else{
				c->loc[c->t[1]-1]=3;
				c->loc[2-c->t[1]]=1;
			}
		}
	}
	int drain=6-c->loc[0]-c->loc[1];
	if(c->l[drain-1]==1){
		c->ops.push(nop(c->loc[c->t[drain-1]-1],drain));
		ret++;
		if(c->loc[c->t[drain-1]-1]<3){
			int r=c->loc[c->t[drain-1]-1];
			c->l[r-1]--;
			c->t[r-1]=3-c->t[r-1];
		}else c->buc=0;
		c->loc[c->t[drain-1]-1]=drain;
		c->loc[2-c->t[drain-1]]=3;
		if(c->l[6-c->loc[0]-c->loc[1]-1]==0){
			c->ops.push(nop(3,6-c->loc[0]-c->loc[1]));
			return ret+1;
		}
	}else{
		if(c->loc[c->t[drain-1]-1]==3)
			c->buc=c->t[drain-1];
		c->ops.push(nop(drain,c->loc[c->t[drain-1]-1]));
		ret++;
		c->t[drain-1]=3-(c->t[drain-1]);
		c->l[drain-1]--;
	}
//cout<<c->t[0]<<','<<c->t[1]<<','<<c->buc<<'\n'<<c->l[0]<<','<<c->l[1]<<'\n'<<c->loc[0]<<','<<c->loc[1]<<'\n'<<'\n';
	return ret+recur(c);
}

void test_case(){
	int n,p;cin>>n>>p;
	conf config;
	char c,lc='0';
	for(int i=0;i<n;i++){
		cin>>c;config.t[0]=c-'0';
		if(lc!=c)config.l[0]++;lc=c;
	}
	lc='0';
	for(int i=0;i<n;i++){
		cin>>c;config.t[1]=c-'0';
		if(lc!=c)config.l[1]++;lc=c;
	}
	if(p>1){
		int x=recur(&config);
		cout<<x<<'\n';
		while(!config.ops.empty()){
			op o=config.ops.front();config.ops.pop();
			cout<<o.a<<' '<<o.b<<'\n';
		}
	}else{
		if(config.t[0]==config.t[1]){
			if((config.l[0]%2)+(config.l[1]%2)==1)
				cout<<config.l[0]+config.l[1]-1<<'\n';
			else cout<<config.l[0]+config.l[1]<<'\n';
		}else{
			if((config.l[0]%2)*(config.l[1]%2))
				cout<<config.l[0]+config.l[1]<<'\n';
			else cout<<config.l[0]+config.l[1]-1<<'\n';
		}
	}
}

int main(){
	int n;cin>>n;
	while(n-->0)test_case();
}
