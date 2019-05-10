#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=2005;
int qa,qb,n;
bool honest[N<<1];

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

int main(){
	static int stk[N<<1];
	int top=0;
	qa=nxi(),qb=nxi();
	if(qa<=qb){
		puts("Impossible");
		return 0;
	}
	n=qa+qb;
	for(int i=0; i<n; ++i){
		if(!top) stk[++top]=i;
		else{
			printf("? %d %d\n",stk[top],i);
			fflush(stdout);
			char c;
			while((c=getchar())!='N'&&c!='Y');
			if(c=='N') --top;
			else stk[++top]=i;
		}
	}
	int rt=stk[top];
	honest[rt]=1;
	for(int i=0; i<n; ++i){
		if(i==rt) continue;
		printf("? %d %d\n",rt,i);
		fflush(stdout);
		char c;
		while((c=getchar())!='N'&&c!='Y');
		honest[i]=c=='Y';
	}
	printf("!");
	for(int i=0; i<n; ++i){
		putchar(honest[i]+'0');
	}
	puts("");
	return 0;
}
