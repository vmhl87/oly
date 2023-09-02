#include <iostream>
#include <unordered_set>
#define X *n_cows+
using namespace std;

int main(){
    long long n_cows,moves,tmp,c1,c2;
    cin >> n_cows >> moves;
    long long* cows = new long long[n_cows];
    long long* move_map = new long long[moves*2];
    bool* pos = new bool[n_cows*n_cows];
    // unordered_set<long long>* pos = new unordered_set<long long>[n_cows];
    bool* fin = new bool[n_cows];
    for(long long i=0;i<n_cows;i++){
    	fin[i]=false;
        cows[i]=i;
        // pos[i].insert(i);
        for(int j=0;j<n_cows;j++)pos[i X j]=false;
        pos[i X i]=true;
    }
    for(long long i=0;i<moves;i++){
        cin >> c1 >> c2;
        fin[c1-1]=true;
        fin[c2-1]=true;
        move_map[i*2]=c1-1;
        move_map[i*2+1]=c2-1;
    }
    bool a=true;
    while(a){
    	a=false;
    	for(long long i=0;i<moves;i++){
    		// pos[cows[move_map[i*2]]].insert(move_map[i*2+1]);
    		// pos[cows[move_map[i*2+1]]].insert(move_map[i*2]);
    		pos[cows[move_map[i*2]] X move_map[i*2+1]]=true;
    		pos[cows[move_map[i*2+1]] X move_map[i*2]]=true;
    		tmp=cows[move_map[i*2]];
    		cows[move_map[i*2]]=cows[move_map[i*2+1]];
    		cows[move_map[i*2+1]]=tmp;
    	}
    	for(long long i=0;i<n_cows;i++){
    		if(cows[i]==i)fin[cows[i]]=false;
    	}
    	tmp=0;
    	while(tmp<n_cows){
    		tmp++;
    		if(fin[tmp]){
    			a=true;
    			tmp=n_cows;
    		}
    	}
    }
    delete[] fin;
    delete[] cows;
    delete[] move_map;
    for(long long i=0;i<n_cows;i++){
		tmp=0;
		for(int j=0;j<n_cows;j++)if(pos[i X j])tmp++;
		cout << tmp << '\n';
		// cout << pos[i].size() << '\n';
    }
    delete[] pos;
    return 1;
}
