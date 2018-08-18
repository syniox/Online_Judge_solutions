#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1e5+2;
int n,m,q,rev[N];

struct data{
	int t,a,id;
	bool operator < (const data &b) const {
		return t<b.t;
	}
}dt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		rev[i]=nxi();
	}
	q=nxi();
	for(int i=1;i<=q;++i){
		dt[i].id=i;
		dt[i].t=nxi(),dt[i].a=nxi();
	}
	std::sort(dt+1,dt+q+1);
	int dpos=1,upos=n,pd=1,cnq=1,r=-1;
	for(int i=1;i<=m;++i,r=-r){
		while(cnq<=q&&dt[cnq].t<=rev[i]){
			int move=r*(dt[cnq].t-rev[i-1]);
			int ans=pd+(dt[cnq].a-dpos)+move;
			if(ans<0) ans=0;
			if(ans>n) ans=n;
			printf("%d\n",ans);
			++cnq;
		}
		int p=r*(rev[i+1]-rev[i]);
		pd+=p;
		if(r>0&&pd+(upos-dpos)>n){
			upos-=pd+(upos-dpos)-n;
			pd=n;
		}
		else if(r<0&&pd<0){
			dpos+=-pd;
			pd=0;
		}
	}
	while(cnq<=q){
		int move=r*(dt[cnq].t-rev[m]);
		int ans=pd+(dt[cnq].a-dpos)+move;
		if(ans<0) ans=0;
		if(ans>n) ans=n;
		printf("%d\n",ans);
		++cnq;
	}
	return 0;
}
