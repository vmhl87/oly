#include <iostream>
using namespace std;

long long max(long long a, long long b){
    if(a>b) return a;
    return b;
}

int main(){
    //self explanatory
    long long n_cows,count=1;
    cin >> n_cows;
    char cows[n_cows];
    long long lists[n_cows];
    long long h_leader=-1,g_leader=-1;
    long long h_start=-1,h_end=-1,g_start=-1,g_end=-1;
    for(long long i=0;i<n_cows;i++){
        cin >> cows[i];
        //input the cows, and update the start and end indexes accordingly
        if(cows[i]=='G'){
            g_end=i+1;
            if(g_start<0) g_start=i+1;
        }else{
            h_end=i+1;
            if(h_start<0) h_start=i+1;
        }
    }
    for(long long i=0;i<n_cows;i++) cin >> lists[i];
    //if the first cow of the flock can see the end, this cow is the true leader
    //we cannot have multiple true leaders
    if(g_start>0&&lists[g_start-1]>=g_end) g_leader=g_start;
    if(h_start>0&&lists[h_start-1]>=h_end) h_leader=h_start;
    //determine if both flocks have a true leader
    if((g_leader<0&&g_start>0)||(h_leader<0&&h_start>0)) count=0;
    for(long long i=0;i<max(h_leader,g_leader)-1;i++){
        //loop through all cows up until the last leader, and check if said cow is
        //a) not a leader, and b) has the other flock's leader in its list
        if(i+1<h_leader&&cows[i]=='G'&&g_leader!=i+1&&lists[i]>=h_leader) count++;
        if(i+1<g_leader&&cows[i]=='H'&&h_leader!=i+1&&lists[i]>=g_leader) count++;
    }
    cout << count << endl;
	return 1;
}
