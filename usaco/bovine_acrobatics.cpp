#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct{
	int weight;
	int count;
	int height=1;
}cowstack;

bool comp_weights(cowstack a,cowstack b){
	return a.weight>b.weight;
}

bool comp_heights(cowstack a,cowstack b){
	return a.height>b.height;
}

int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);
	int n,m,k;cin>>n>>m>>k;
	cowstack stacks[n];
	for(int i=0;i<n;i++){
		cin>>stacks[i].weight>>stacks[i].count;
	}
	sort(stacks,stacks+n,comp_weights);
	for(int i=0;i<n;i++){
		for(int next_stack=i+1;next_stack<n;next_stack++){
			if(stacks[next_stack].count==0)continue;
			if(stacks[next_stack].weight+k>stacks[i].weight)continue;
			if(stacks[next_stack].count<stacks[i].count){
				stacks[i].count=stacks[next_stack].count;
				int t=stacks[i].weight;
				stacks[i].weight=stacks[next_stack].weight;
				stacks[i].height++;
				stacks[next_stack].weight=t;
				stacks[next_stack].count-=stacks[i].count;
			}else{
				stacks[next_stack].count-=stacks[i].count;
				stacks[i].weight=stacks[next_stack].weight;
				stacks[i].height++;
			}
		}
	}
	sort(stacks,stacks+n,comp_heights);
	int ret=0;
	for(int i=0;i<n;i++){
		if(m<stacks[i].count){
			ret+=m*stacks[i].height;
			break;
		}else{
			ret+=stacks[i].count*stacks[i].height;
			m-=stacks[i].count;
		}
	}
	cout<<ret<<'\n';
}
