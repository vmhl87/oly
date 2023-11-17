#include <iostream>

int ret=0;
bool board[64];
int init[8]={0,1,2,3,4,5,6,7};

void permute(int d,int p[]){
	if(d==8){
		for(int h=0;h<8;h++)if(board[p[h]+h*8])return;
		for(int h=0;h<8;h++)
			for(int j=0;j<8;j++){
				if(j==h)continue;
				if(p[j]==p[h]+j-h)return;
				if(p[j]==p[h]+h-j)return;
			}
		ret++;
	}else{
		for(int i=d;i<8;i++){
			int ret[8];
			// 1 2 3 4 5 6 7 8
			// _ _ d _ i _ _ _
			for(int h=0;h<d;h++)ret[h]=p[h];
			// 1 2 _ _ i _ _ _
			ret[d]=p[i];
			// 1 2 5 _ i _ _ _
			for(int h=d;h<i;h++)ret[h+1]=p[h];
			// 1 2 5 3 4 _ _ _
			for(int h=i+1;h<8;h++)ret[h]=p[h];
			// 1 2 5 3 4 6 7 8
			permute(d+1,ret);
		}
	}
}

int main(){
	for(int i=0;i<64;i++){
		char c;std::cin>>c;
		board[i]=(c=='*');
	}
	permute(0,init);
	std::cout<<ret<<'\n';
}
