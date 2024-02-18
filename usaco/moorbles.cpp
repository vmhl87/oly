#include <iostream>
#include <stack>
using namespace std;

void test_case(){
	// input vars
	int n,m,k;
	cin>>n>>m>>k;
	// create penalty bindings
	int pen[m][2];
	for(int i=0;i<m;i++){
		// input first value
		int s;cin>>s;
		// if s is even, even has no penalty
		if(s%2==0){
			pen[i][0]=s;
			pen[i][1]=-s;
		// otherwise it does
		}else{
			pen[i][0]=-s;
			pen[i][1]=s;
		}
		// input all the rest
		for(int j=1;j<k;j++){
			cin>>s;
			// if s is odd, invert (has penalty on even)
			if(s%2==1)s*=-1;
			if(pen[i][0]>s)pen[i][0]=s;
			// whatever penalty it had for even is opposite
			s*=-1;
			if(pen[i][1]>s)pen[i][1]=s;
		}
	}
	// check if possible
	int max=0;
	for(int i=0;i<m;i++){
		if(pen[i][0]>pen[i][1])max+=pen[i][0];
		else max+=pen[i][1];
	}
	if(n+max<1){
		cout<<-1<<'\n';
		return;
	}
	// create dfs stack
	stack<int> s;
	// depth count thing
	int c=0;
	// crude "visited"
	int to[m];for(int i=0;i<m;i++)to[i]=0;
	// iterate until reached end
	while(c<m){
		// if all the possibilities are tried, backtrack by one
		if(to[c]>1){
			// also reset visited thing
			n-=pen[c][s.top()];to[c]=0;
			s.pop();c--;
		// otherwise check if next possibility is workable
		}else if(n>-pen[c][to[c]]){
			n+=pen[c][to[c]];
			s.push(to[c]);
			to[c]++;c++;
		// if not advance the visited thing
		}else to[c]++;
		// if we looped back to start, it is impossible
		if(c==0)break;
	}
	if(c==0){
		cout<<-1<<'\n';
		return;
	}
	int moves[m];
	for(int i=0;i<m;i++){
		moves[m-i-1]=s.top();
		s.pop();
	}
	for(int i=0;i<m;i++){
		if(i)cout<<' ';
		if(moves[i])cout<<"Odd";
		else cout<<"Even";
	}
	cout<<'\n';
}

int main(){
	int t;cin>>t;
	while(t-->0)test_case();
}
