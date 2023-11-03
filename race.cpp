/*
K = 3

  #
 ##
### (graph of speed vs time)
total distance traveled = number of #'s

  # #
 ## #
### # <- adds 3 distance 3+(3.5*0)

    #
  # ##
 ## ##
### ## <- adds 4+3 distance (3.5*2)

    ##
  # ###
 ## ###
### ### <- adds 4+4+3 distance 3+(4*2)

     #
    ###
  # ####
 ## ####
### #### <- adds 4+5+4+3 distance (4*4)

     ##
    ####
  # #####
 ## #####
### ##### <- adds 4+5+5+4+3 distance 3+(4.5*4)

      #
     ###
    #####
  # ######
 ## ######
### ###### <- adds 4+5+6+5+4+3 distance (4.5*6)

init=6, total=10
if odd: x+((x+(a+1)/4)*(a-1)) = x + x*(a-1) + (a*a-1)/4
if even: (x+a/4)*a
*/
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	ifstream cin("race.in");
	ofstream cout("race.out");
	long long k,N;cin>>k>>N;
	while(N-->0){
		long long x;cin>>x;
		// static distance: x(x+1)/2
		long long target=k-((x*(x+1))/2),moves=x;
		if(target<0){
			long long sum=0;
			for(long long i=1;i<k;i++){
				sum+=i;
				if(sum>=k){
					cout<<i<<'\n';
					break;
				}
			}
			continue;
		}else if(target==0){
			cout<<x<<'\n';
			continue;
		}
		for(long long i=1;i<k;i++){
			long long dist;
			if(i%2==0){
				dist=x*i+(i*i)/4;
			}else{
				dist=x+x*(i-1)+(i*i-1)/4;
			}
			if(dist==target){
				moves+=i;break;
			}else if(dist>target){
				moves+=i;break;
			}
		}
		cout<<moves<<'\n';
	}
	return 0;
}
