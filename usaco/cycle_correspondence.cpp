#include <iostream>
#include <vector>
using namespace std;

typedef struct{
	bool used=0;
	int to[2]={-1,-1};
	bool could_be=0;
}barn;

typedef struct{
	int len;
	int pos;
}block;

int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	int n,k,last=0,t;cin>>n>>k;
	barn a[n],b[n];
	int first=-1;
	int first_a,first_b;
	for(int i=0;i<k;i++){
		cin>>t;if(first<0)first=t-1;
		a[t-1].used=1;
		a[last].to[1]=t-1;
		a[t-1].to[0]=last;
		last=t-1;
		if(!i)first_a=t-1;
	}
	a[first].to[0]=last;
	a[last].to[1]=first;
	first=-1;
	for(int i=0;i<k;i++){
		cin>>t;if(first<0)first=t-1;
		b[t-1].used=1;
		b[last].to[1]=t-1;
		b[t-1].to[0]=last;
		last=t-1;
		if(!i)first_b=t-1;
	}
	b[first].to[0]=last;
	b[last].to[1]=first;
/*
cout<<"---\n";
for(int i=0;i<n;i++){
	cout<<i+1<<": ";
	if(a[i].used){
		cout<<a[i].to[0]+1<<'.'<<a[i].to[1]+1;
	}else cout<<"   ";
	cout<<' ';
	if(b[i].used){
		cout<<b[i].to[0]+1<<'.'<<b[i].to[1]+1;
	}else cout<<"   ";
	cout<<'\n';
}
cout<<"---\n";
*/
	int ret=0,ter=0;
	for(int i=0;i<n;i++){
		if(!a[i].used&&!b[i].used)ter++;
		else if(a[i].used&&b[i].used){
			int c1=0,c2=0;
			for(int h=0;h<2;h++){
				if(b[a[i].to[h]].used)c1++;
				if(a[b[i].to[h]].used)c2++;
			}
			if(c1==c2){
				a[i].could_be=1;
				b[i].could_be=1;
			}
		}
	}

	for(int dir=0;dir<2;dir++){
		vector<block> cyc_a,cyc_b;
		int ptr=0,cur=first_a,buf=0;
		if(a[first_a].could_be&&a[a[first_a].to[1-dir]].could_be){
			while(a[cur].could_be){
				ptr++;cur=a[cur].to[dir];
				if(ptr>k){
					block tmp;
					tmp.len=k;
					tmp.pos=0;
					cyc_a.push_back(tmp);
					break;
				}
			}
		}
		while(ptr<k||buf>0){
			if(a[cur].could_be&&buf<k)buf++;
			else if(buf>0){
				block tmp;
				tmp.len=buf;
				tmp.pos=ptr-buf;
				cyc_a.push_back(tmp);
				buf=0;
			}
			cur=a[cur].to[dir];
			ptr++;
		}
		ptr=0;cur=first_b;buf=0;
		if(b[first_b].could_be&&b[b[first_b].to[1-dir]].could_be){
			while(b[cur].could_be){
				ptr++;cur=b[cur].to[dir];
				if(ptr>k){
					block tmp;
					tmp.len=k;
					tmp.pos=0;
					cyc_b.push_back(tmp);
					break;
				}
			}
		}
		while(ptr<k||buf>0){
			if(b[cur].could_be&&buf<k)buf++;
			else if(buf>0){
				block tmp;
				tmp.len=buf;
				tmp.pos=ptr-buf;
				cyc_b.push_back(tmp);
				buf=0;
			}
			cur=b[cur].to[1];
			ptr++;
		}
		if(cyc_a.size()!=cyc_b.size())ret=0;
		else for(int off=0;off<k;off++){
			int size=cyc_a.size(),tp=0;
			for(int i=0;i<size;i++)
				if(cyc_a[i].pos%k==(cyc_b[i].pos+off)%k)
					if(cyc_a[i].len==cyc_b[i].len)
						tp+=cyc_a[i].len;
			if(tp>ret)ret=tp;
		}
	}
	cout<<ret+ter<<'\n';
}
