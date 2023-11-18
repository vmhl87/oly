#include <iostream>
#include <string>
#include <vector>

int main(){
	std::string l;
	while(getline(std::cin,l)){
		if(l.length()<3)break;
		int n=0,b=0,e=0;
		for(char c:l){
			if(e){
				if(c==' ')break;
				else b=(10*b)+(int)(c-'0');
			}else{
				if(c==' ')e++;
				else n=(10*n)+(int)(c-'0');
			}
		}
		int ct=0;
		std::vector<int> cur;
		for(int i=l.length()-1;i>0;i--){
			if(l[i]==' ')break;
			if(l[i]<'0'||l[i]>'9')continue;
			cur.push_back((int)(l[i]-'0'));
		}
		while(n-->0){
			for(int i:cur)if(i==b-1)ct++;
			bool push=1;int d=0;
			while(push){
				push=0;
				cur[d]++;
				if(cur[d]==b){
					cur[d]=0;push=1;d++;
					if(d==cur.size()){
						cur.push_back(1);break;
					}
				}
			}
		}
		std::cout<<ct<<'\n';
	}
}
