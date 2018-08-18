#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1e5+2;
int n,m,q,rev[N],ans[N];

struct data{
	int t,a,id;
	bool operator < (const data &b) const {
		return t<b.t;
	}
}dt[N];

inline void apx(int &x,const int y){
	if(x<y) x=y;
}
inline void apn(int &x,const int y){
	if(x>y) x=y;
}

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
//		printf("dpos%d upos%d pd%d\n",dpos,upos,pd);
		while(cnq<=q&&dt[cnq].t<=rev[i]){
			int move=r*(dt[cnq].t-rev[i-1]),dis=dt[cnq].a-dpos;
			apn(dis,upos-dpos);
			apx(dis,0);
			int ans0=pd+dis+move;
			apn(ans0,n);
			apx(ans0,0);
			ans[dt[cnq].id]=ans0;
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
		int move=r*(dt[cnq].t-rev[m]),dis=dt[cnq].a-dpos;
		apn(dis,upos-dpos);
		apx(dis,0);
		int ans0=pd+dis+move;
		apn(ans0,n);
		apx(ans0,0);
		ans[dt[cnq].id]=ans0;
		++cnq;
	}
	for(int i=1;i<=q;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
