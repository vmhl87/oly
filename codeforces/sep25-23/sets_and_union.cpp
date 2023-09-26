#include <iostream>
using namespace std;

void test_case(){
	int n,t;cin>>n;
	int len[n],count[50];
	for(int i=0;i<50;i++)count[i]=0;
	int sets[n][50];
	for(int i=0;i<n;i++){
		cin>>len[i];
		for(int j=0;j<len[i];j++){
			cin>>t;sets[i][j]=t;
			count[t]++;
		}
	}
	int total=0,best=50;
	for(int i=0;i<50;i++){
		if(count[i]==0)continue;
		int tmpcount[50];
		for(int j=0;j<50;j++)tmpcount[j]=count[j];
		for(int j=0;j<n;j++){
			bool a=false;
			for(int k=0;k<len[j];k++)
				if(sets[j][k]==i){a=true;break;}
			if(a)for(int k=0;k<len[j];k++)
				tmpcount[sets[j][k]]--;
		}
		t=0;
		for(int j=0;j<50;j++)if(count[j]>0&&tmpcount[j]<1)
			t++;
		if(t<best)best=t;
		total++;
	}
	cout<<total-best<<'\n';
}

int main(){
	int c;cin>>c;
	while(c-->0)test_case();
	return 0;
}

/*

* 1
*   3  6    10
*         9
* 1 3
*     5 8 9

6,10 unique

if exclude 6,10: 7-2=5

however, remove 1 is optimal

* 1 2 3 4
*   2     5 6
*     3   5 6
*       4 5 6

if remove 5:remove 6
if remove 4:remove 1
if remove 3:remove 1
if remove 2:remove 1
if remove 1: optimal

*/
