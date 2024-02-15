#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
	int x;
	int y;
}cow;

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

void push(ll **l,int v){
	if((*l)->head==NULL){
		(*l)->head=malloc(sizeof(node));
		(*l)->end=(*l)->head;
	}else{
		(*l)->end->next=malloc(sizeof(node));
		(*l)->end=(*l)->end->next;
	}
	(*l)->end->v=v;
	(*l)->end->next=NULL;
}

int pop(ll **l){
	if((*l)->head==NULL)return 0;
	int ret=(*l)->head->v;
	if((*l)->head==(*l)->end)(*l)->end=NULL;
	node *next=(*l)->head->next;
	free((*l)->head);
	(*l)->head=next;
	return ret;
}

int main(){
	FILE *in=fopen("fenceplan.in","r"),
		*out=fopen("fenceplan.out","w");
	int n,m;fscanf(in,"%d %d",&n,&m);
	cow cows[n];
	for(int i=0;i<n;i++)
		fscanf(in,"%d %d",&cows[i].x,&cows[i].y);
	ll *rel[n];for(int i=0;i<n;i++)init(&rel[i]);
	for(int i=0;i<m;i++){
		int a,b;fscanf(in,"%d %d",&a,&b);
		a--;b--;
		push(&rel[a],b);
		push(&rel[b],a);
	}
	int ptr=0;
	bool vis[n];
	ll *q;init(&q);
	for(int i=0;i<n;i++)vis[i]=0;
	int ret=-1;
	while(ptr<n){
		push(&q,ptr);
		int mix=-1,max=-1,miy=-1,may=-1;
		while(q->head!=NULL){
			int n=pop(&q);
			if(cows[n].x>max)max=cows[n].x;
			if(cows[n].y>may)may=cows[n].y;
			if(cows[n].x<mix||mix<0)mix=cows[n].x;
			if(cows[n].y<miy||miy<0)miy=cows[n].y;
			vis[n]=1;
			for(node *i=rel[n]->head;i!=NULL;i=i->next)
				if(!vis[i->v])push(&q,i->v);
		}
		max-=mix;may-=miy;
		max+=may;max*=2;
		if(max<ret||ret<0)ret=max;
		while(vis[ptr]&&ptr<n)ptr++;
	}
	fprintf(out,"%d\n",ret);
}
