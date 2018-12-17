#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1005;
int n,mp[N][N];

namespace IO{
	char obuf[1000000],*h=obuf,*t=h+1000000;
	char stk[15];
	inline void flush(){
		fwrite(obuf,1,h-obuf,stdout);h=obuf;
	}
	inline void put_c(const char c){
		*h++=c;if(h==t) flush();
	}
	inline int nxi(){
		int x=0;
		char c;
		while((c=getchar())>'9'||c<'0');
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return x;
	}
	inline void putint(int x){
		int top=0;
		//if(!x) stk[++top]='0';
		for(int y; x;){
			y=x/10;
			stk[++top]=x-y*10+'0';
			x=y;
		}
		while(top) put_c(stk[top--]);
	}
}

int mtrx[2][5][5]={
	//&1=1
	{
		{1,23,18,2,24},
		{6,13,10,7,16},
		{21,3,25,22,19},
		{11,8,17,12,9},
		{5,14,20,4,15}
	},
	{//&1=0
		{24,2,18,23,1},
		{16,7,10,13,6},
		{19,22,25,3,21},
		{9,12,17,8,11},
		{15,4,20,14,5}
	}
};


inline void fill(int x,int y,int cnt,int blk,int cut,int col[5][5]){
	const int after=n*n-(blk+1)*25;
	const int basex=(x-1)*5,basey=(y-1)*5;
	for(int i=1; i<=5; ++i){
		for(int j=1; j<=5; ++j){
			mp[i+basex][j+basey]=col[i-1][j-1]+cnt+(col[i-1][j-1]>cut?after:0);
		}
	}
}

int main(){
	n=IO::nxi();
	int block=n/5;
	for(int i=1,cnt=0,blk=0; i<=block; ++i){
		int step=i&1?1:-1,end=i&1?block:1;
		for(int j=i&1?1:block; j!=end; j+=step,++blk,cnt+=18){
			fill(i,j,cnt,blk,18,mtrx[(i&1)^1]);
		}
		fill(i,end,cnt,blk,19,mtrx[(i&1)^1]);
		++blk,cnt+=19;
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			IO::putint(mp[i][j]);
			IO::put_c(' ');
		}
		IO::put_c('\n');
	}
	IO::flush();
	return 0;
}
