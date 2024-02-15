#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node node;
struct node{
	int v;
	node *next;
};

typedef struct{
	node *head;
	node *end;
}ll;

void init(ll **l){
	(*l)=malloc(sizeof(ll));
}

void push(ll **x,int v){
	ll *l=*x;
	if(l->head==NULL){
		l->head=malloc(sizeof(node));
		l->end=l->head;
	}else{
		l->end->next=malloc(sizeof(node));
		l->end=l->end->next;
	}
	l->end->v=v;
	l->end->next=NULL;
}

int pop(ll **x){
	ll *l=*x;
	if(l->head==NULL)return 0;
	int ret=l->head->v;
	if(l->head==l->end)l->end=NULL;
	node *next=l->head->next;
	free(l->head);
	l->head=next;
	return ret;
}

int main(){
	int n;scanf("%d",&n);
	int metals[n];
	for(int i=0;i<n;i++)scanf("%d",&metals[i]);
	int k;scanf("%d",&k);
	ll *rec[n];for(int i=0;i<n;i++)init(&rec[i]);
	for(int i=0;i<k;i++){
		int l,m,t;scanf("%d %d",&l,&m);
		while(m-->0){
			scanf("%d",&t);push(&rec[l-1],t-1);
		}
	}
	int r[n];for(int i=1;i<n;i++)r[i-1]=0;
	r[n-1]=1;
	int ret=0;
	for(;;){
		int can=0;bool b=1;
		for(int i=0;i<n;i++)if(r[i]>0){
			int t=metals[i]/r[i];
			if(t<can||b){can=t;b=0;}
		}
		ret+=can;
		for(int i=0;i<n;i++)metals[i]-=can*r[i];
		for(int i=0;i<n;i++)if(r[i]>metals[i]){
			if(rec[i]->head!=NULL){
				for(node *h=rec[i]->head;h!=NULL;h=h->next)
					r[h->v]+=r[i]-metals[i];
				r[i]=metals[i];
			}else goto done;
		}
	}
	done:
	printf("%d\n",ret);
}
