#include <iostream>
#include <vector>
using namespace std;

struct output{
	bool output;
	bool fixed = false;
	int working;
	vector<char> bits;
};

void solve_case(){
	long bits, outputs;
	cin >> bits >> outputs;
	output all[outputs];
	for(int i=0;i<outputs;i++){
		all[i].bits.resize(bits);
		for(int j=0;j<bits;j++){
			cin >> all[i].bits[j];
		}
		int b;
		cin >> b;
		if(b>0) all[i].output = true;
		else all[i].output = false;
		all[i].working = bits;
	}
	int place, invalid0, invalid1;
	bool added_new = true;
	while(added_new){
	    added_new = false;
	    for(int i=0;i<outputs;i++){
	        if(!all[i].fixed) all[i].working=bits;
	    }
	    place = -1; invalid0 = 0; invalid1 = 0;
	    while(place++ < bits-1){
		    bool if0, if1, valid0 = true, valid1 = true,
		    set0 = false, set1 = false;
		    for(int i=0;i<outputs;i++){
				if(all[i].fixed) continue;
				if(all[i].bits[place] == '0'){
					if(!set0){set0 = true; if0 = all[i].output;}
					else if(if0 != all[i].output) valid0 = false;
				}else{
					if(!set1){set1 = true; if1 = all[i].output;}
					else if(if1 != all[i].output) valid1 = false;
				}
			}
		    for(int i=0;i<outputs;i++){
			    if(all[i].fixed) continue;
			    if(all[i].bits[place] == '0'){
				    if(!valid0) all[i].working-=1;
			    }else{
				    if(!valid1) all[i].working-=1;
			    }
		    }
        }
        for(int i=0;i<outputs;i++){
            if(all[i].working > 0 && !all[i].fixed){
		        all[i].fixed = true;
		        added_new = true;
	        }
        }
    }
	place = -1;
	bool w_output, w_output_set = false;
	while(place++ < outputs-1){
		if(all[place].fixed)continue;
		if(all[place].working == 0){
			if(w_output_set){
				if(w_output != all[place].output){
					cout << "LIE" << endl;
					return;
				}
			}else{
				w_output_set = true; w_output = all[place].output;
			}
		}
	}
	cout << "OK" << endl;
	return;
}

int main(){
	int cases;
	cin >> cases;
	for(int i=0;i<cases;i++){
		solve_case();
	}
	return 1;
}
