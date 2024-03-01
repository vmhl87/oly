#include <iostream>

using namespace std;

int n,s['   '],h['   '],a,i,M=1<<18,t;

#include <ctype.h>
#include <stdio.h>
#define BUFSIZE 0x20000

int rpos;
char rbuf[BUFSIZE], cf[9];
static inline char readChar() {
  if (!(rpos = (rpos+1) & (BUFSIZE-1)))
    fread(rbuf, 1, BUFSIZE, stdin);
  return rbuf[rpos];
}

static inline int read() {
  int ch, ret = 0;
  while (!isdigit(ch = readChar()));

  do
    ret = (ret << 3) + (ret << 1) + ch - '0';
  while (isdigit(ch = readChar()));

  return ret;
}

static inline void print (int x) {
  if (!x)
    putchar_unlocked('0');
  else {
    int pos = 9;

    while (x) {
      cf[--pos] = '0' + x%10;
      x /= 10;
    }

    puts(&cf[pos]);
    putchar_unlocked(' ');
  }
}

#define gc getchar_unlocked

main()
{
	// input n (# of elem)
    n=read();
	// input into array h, set all values
	// of s to 0 - this occurs between M
	// and n+M (implicit segtree?)
    for (i=M;i<n+M;) h[i]=read(),s[i++]=1;
	// fill in other nodes of segtree - assume
	// that balanced, M is power of 2
    for (i=M;i--;) s[i]=s[i<<1]<<1;
	// for each query:
    while (n--)
    {
		// a = element to be deleted
        a=read();
		// root node?
        i=1;
		// decrease "virtual index" each time
		// we take a right split, because we
		// are now traversing a new subtree
        while (i<M) a-=s[i<<=1]<a?s[i++]:0;
        print(h[i]);
		// iterate back up and update tree
        for (;i;i>>=1) --s[i];
    }
}
