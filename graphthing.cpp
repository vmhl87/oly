#include <iostream>
#include <stack>
using namespace std;

int edgelist[28][2];

void compute_edges(){
	int ptr=0;
	for(int i=0;i<8;i++)
		for(int j=i+1;j<8;j++){
			edgelist[ptr][0]=i;
			edgelist[ptr][1]=j;
			ptr++;
		}
	if(ptr!=28)cout<<"something went wrong\n";
}

stack<int> path;

void resolve(){
	
}

int found=0;

void permute(){
	if(path.size()==14){
		resolve();
		found++;
		if(found%1000000==0)cout<<found<<" found\n";
		return;
	}
	int start=0;
	if(!path.empty())start=path.top()+1;
	for(int i=start;i<28;i++){
		path.push(i);
		permute();
		path.pop();
	}
}

int main(){
	compute_edges();
	permute();
}

