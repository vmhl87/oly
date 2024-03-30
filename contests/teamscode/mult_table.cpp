#include <iostream>
using namespace std;

int main(){
  int x;cin>>x;
  int y=x+1;
  for(;;){
    bool w=1;
    for(int i=2;i<=x;++i)
      if(y%i==0){
        w=0;break;
      }
    if(w){
      cout<<y<<'\n';
      break;
    }
	y++;
  }
}
