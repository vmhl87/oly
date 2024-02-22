/*  Room allocations
	
	I took inspiration from how zalloc(), a real-world
	memory allocator and deallocator used in C, handles
	memory allocations. Of course, I didn't have to deal
	with needing to mantain long contiguous open ranges
	like zalloc() does in real life.
	
	Essentially, we need to approach this situation where
	time is the variable. To do this, we split up each guest
	into two "events", one for when they enter, and one when
	they leave. We sort these based on time.
	
	Then, to "simulate" the operation of this hotel, we simply
	need to iterate through the sorted events, and process
	them as we go, and they're guaranteed to be in the correct
	logical order.
	
	To process an event, I kept a count of how many rooms were
	currently in use, because the hotel will never need more
	than the is number. This was increased and decreased trivially
	when guests entered and left.
	
	Matching guest to room was a bit more complex - I
	realized that I could break it down into two cases:
	the hotel is already full and we need to allocate a
	new room for the guest, or we can use an existing free
	room to put the guest in.
	
	To manage this, I used a stack datastructure, because
	it could store all of the free rooms, and have efficient
	ways to add, remove, and find the top free rooms.
*/

#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;

// event struct - stores time (t), id (i), and whether
// a guest entered or left (y)
typedef struct e{
	int t;
	int i;
	bool y=0;
	// sort on time
	bool operator<(const e o)const{
		if(t==o.t&&y)return 1;
		return t<o.t;
	}
}e;

int main(){
	int n;cin>>n;
	// because each guest will enter and leave, they will
	// need two events
	e ev[n*2];
	// input event times
	for(int i=0;i<n;i++)cin>>ev[i].t>>ev[i+n].t;
	// set all beginning events to enter events
	for(int i=0;i<n;i++)ev[i].y=1;
	// set ids of events
	for(int i=0;i<n;i++)for(int j=0;j<2;j++)ev[i+n*j].i=i;
	// sort
	sort(ev,ev+2*n);
	// keep track of current active rooms and maximum ever
	int cur=0,max=0;
	// room storage to print
	int rooms[n];
	// freed rooms storage - once a guest leaves, push to
	// this stack, and when new guest comes, and there is
	// an available room in the stack, use it
	stack<int> rs;
	// otherwise, nx stores the (n)ext inde(x) to use when
	// a new room is needed (this happens when stack is
	// empty)
	int nx=0;
	// loop through sorted events
	for(int i=0;i<n*2;i++){
		// if a guest entered, increase current used rooms
		if(ev[i].y){
			cur++;
			// find an available room in the stack, or if
			// none, allocate a new one
			if(rs.empty())rooms[ev[i].i]=nx++;
			else{
				rooms[ev[i].i]=rs.top();
				// once room is reallocated pop off stack
				rs.pop();
			}
		// otherwise, decrease currently used rooms count
		// and put on stack
		}else{
			cur--;
			rs.push(rooms[ev[i].i]);
		}
		// update maximum
		if(cur>max)max=cur;
	}
	// output
	cout<<max<<'\n';
	for(int i=0;i<n;i++){
		if(i)cout<<' ';
		cout<<rooms[i]+1;
	}
	cout<<'\n';
}
