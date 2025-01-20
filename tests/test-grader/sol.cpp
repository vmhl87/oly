#include <iostream>
using namespace std;

typedef struct{
	// store position and type
	int p;
	char t;
}com;

int main(){
	// input n,t
	int n,t;cin>>t>>n;
	// input targets and put in indexing array
	bool targets[n*2+1];for(int i=0;i<n*2+1;i++)targets[i]=0;
	for(int i=0;i<t;i++){
		int p;cin>>p;
		targets[p+n]=1;
	}
/*
cout<<"tr---\n";
for(int i:targets)cout<<i<<' ';cout<<'\n';
cout<<"-----\n";
*/
	// input commands
	com cmds[n];
	int curr=n,orig_hits=0;
	bool orig[n*2+1];int firstof[n*2+1];
	for(int i=0;i<n*2+1;i++){
		orig[i]=0;
		firstof[i]=-1;
	}
	for(int i=0;i<n;i++){
		cin>>cmds[i].t;
		// keep track of current position
		if(cmds[i].t=='L')curr--;
		else if(cmds[i].t=='R')curr++;
		// build originally hit list
		else if(targets[curr]){
			if(!orig[curr]){
				firstof[curr]=i;
				orig_hits++;
			}
			orig[curr]=1;
		}
	}
	// calculate running max
	int max_hits=orig_hits;
	// calculate all 5 offsets:
	int net_hits[5];
	for(int i=0;i<5;i++)net_hits[i]=orig_hits;
	bool new_targets[5][n*2+1];
	for(int i=0;i<5;i++)for(int j=0;j<n*2+1;j++)new_targets[i][j]=0;
	// iterate from the back of the command stack
	for(int c=n-1;c>=0;c--){
		// this needs to exec before the l/r/f computation
		if(cmds[c].t=='F'){
			// if this was the first contributor, remove from orig, and
			// update net counts
			if(orig[curr]&&firstof[curr]==c){
				orig[curr]=0;orig_hits--;
				// we need to check if there is an unlogged new hit
				for(int i=0;i<5;i++)if(i!=2&&!new_targets[i][curr])
					net_hits[i]--;
			}
		}
		// calculate what happens if left,right,fire is changed
		if(cmds[c].t=='F'){
			// result will either be orig+net[-1] or orig+net[1]
			if(net_hits[1]>max_hits)
				max_hits=net_hits[1];
			if(net_hits[3]>max_hits)
				max_hits=net_hits[3];
		}else if(cmds[c].t=='L'){
			// if L switches to R: result will be orig+net[2]
			if(net_hits[4]>max_hits)
				max_hits=net_hits[4];
			// if L switches to F:
			// check if this loc has already been hit, and if not,
			// is there a target
			if(!new_targets[3][curr+1]&&!orig[curr+1]&&targets[curr+1])
				if(net_hits[3]+1>max_hits)
					max_hits=net_hits[3]+1;
		}else{
			// if R switches to L: result will be orig+net[-2]
			if(net_hits[0]>max_hits)
				max_hits=net_hits[0];
			// if R switches to F:
			// check if this loc has already been hit, and if not,
			// is there a target
			if(!new_targets[1][curr-1]&&!orig[curr-1]&&targets[curr-1])
				if(net_hits[1]+1>max_hits)
					max_hits=net_hits[1]+1;
		}
		// if cmd is fire:
		if(cmds[c].t=='F'){
			// somehow handle merging of fires
			// maybe: keep a handling array of originally hit
			// fires, another array of newly hit fires, and update
			// net count when changes occur
			
			// update net counts (ignore center pos)
			for(int i=0;i<5;i++)if(i!=2){
				// if there is a new target, we want to increase net
				// count but only if there is not one on orig[]
				if(!new_targets[i][curr+i-2]&&targets[curr+i-2]){
					// if it is not present in orig, it is a new hit
					if(!orig[curr+i-2]){
						net_hits[i]++;
					}
					// we nevertheless want to mark it as newly hit
					new_targets[i][curr+i-2]=1;
				}
			}
		}
		// update net position (backwards)
		else if(cmds[c].t=='L')curr++;
		else curr--;
/*
cout<<c<<" ---\n";
cout<<"orig hits: "<<orig_hits<<'\n';
cout<<"max hits: "<<max_hits<<'\n';
cout<<"net hits:\n";
for(int i=0;i<5;i++)cout<<"   "<<net_hits[i]<<'\n';
cout<<"orig: ";for(int i=0;i<n*2+1;i++)if(orig[i])cout<<i-n<<' ';cout<<'\n';
for(int i=0;i<5;i++){
	cout<<"   "<<i<<": ";
	for(int j=0;j<n*2+1;j++)if(new_targets[i][j])cout<<j-n<<' ';cout<<'\n';
}
cout<<"-----\n";
*/
	}
	cout<<max_hits<<'\n';
}
