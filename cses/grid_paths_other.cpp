#include <iostream>
using namespace std;

int ret=0;
bool board[49];
short mask[48];

// UDLR > 1234
void recurse(int x,int y,short len){
	if(x<0||y<0||x>6||y>6)return;
	//cout<<len<<' ';
	if(len==48){
		if(x==0&&y==6)ret++;
		return;
	}
	short h=mask[len];
	if(h==1||!h){
		if(!board[x+y*7-7]){
			board[x+y*7-7]=1;
			recurse(x,y-1,len+1);
			board[x+y*7-7]=0;
		}
	}
	if(h==2||!h){
		if(!board[x+y*7+7]){
			board[x+y*7+7]=1;
			recurse(x,y+1,len+1);
			board[x+y*7+7]=0;
		}
	}
	if(h==3||!h){
		if(!board[x+y*7-1]){
			board[x+y*7-1]=1;
			recurse(x-1,y,len+1);
			board[x+y*7-1]=0;
		}
	}
	if(h==4||!h){
		if(!board[x+y*7+1]){
			board[x+y*7+1]=1;
			recurse(x+1,y,len+1);
			board[x+y*7+1]=0;
		}
	}
}

int main(){
	char t;
	for(short i=0;i<48;i++){
		cin>>t;
		if(t=='?')mask[i]=0;
		else if(t=='U')mask[i]=1;
		else if(t=='D')mask[i]=2;
		else if(t=='L')mask[i]=3;
		else mask[i]=4;
	}
	for(int i=0;i<49;i++)board[i]=0;
	board[0]=1;
	recurse(0,0,0);
	cout<<ret<<'\n';
}
