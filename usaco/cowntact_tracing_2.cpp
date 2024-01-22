#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n,buf=0,minblock;cin>>n;
	char t;minblock=n;
	vector<int> blocks;
	blocks.reserve(n);
	bool is_start=1;
	bool h_start=0,h_end=0;
	for(int i=0;i<n;i++){
		cin>>t;
		if(t=='0'){
			if(buf>0){
				if(is_start){h_start=1;is_start=0;}
				else if(minblock>buf)minblock=buf;
				blocks.push_back(buf);
				buf=0;
			}
		}else{
			buf++;
		}
	}
	if(buf>0){
		h_end=1;
		blocks.push_back(buf);
	}
	int days,ret=0,n_blocks=blocks.size();
	if(minblock%2==0)days=minblock/2-1;
	else days=(minblock-1)/2;
	if(h_start&&days>=blocks[0])days=blocks[0]-1;
	if(h_end&&days>=blocks[n_blocks-1])days=blocks[n_blocks-1]-1;
	days=days+days+1;
	for(int b:blocks){
		ret+=1+(b-1)/days;
	}
	cout<<ret<<'\n';
}
