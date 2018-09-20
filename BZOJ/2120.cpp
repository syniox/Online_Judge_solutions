#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1e4+5,N32=470;
int n,m,cnr,cnd,col[N],ans[N];
struct mod{
	int x,pre,cur;
}ch[N];
struct data{
	int x,y,t,id,sqx,sqy;
	bool operator < (const data &b) const {
		if(sqx!=b.sqx) return sqx<b.sqx;
		if(sqy!=b.sqy) return sqy<b.sqy;
		return t<b.t;
	}
}dt[N];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace S{
	int l,r,t,cur,buk[(int)1e6+2];
	inline void add(const int k){
		if(++buk[col[k]]==1) ++cur;
	}
	inline void del(const int k){
		if(!--buk[col[k]]) --cur;
	}
	inline void move_time(const int t,const bool ahead){
		const int x=ch[t].x;
		const bool f=(x>=l&&x<=r);
		if(f) del(x);
		col[x]=ahead?ch[t].cur:ch[t].pre;
		if(f) add(x);
	}
	inline void solve(){
		l=dt[1].x,r=dt[1].x-1,t=cnr;
		for(int i=1;i<=cnd;++i){
			while(l>dt[i].x) add(--l);
			while(r<dt[i].y) add(++r);
			while(l<dt[i].x) del(l++);
			while(r>dt[i].y) del(r--);
			while(t<dt[i].t) move_time(++t,1);
			while(t>dt[i].t) move_time(t--,0);
			ans[dt[i].id]=cur;
		}
	}
}


int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		col[i]=nxi();
	}
	for(int i=1;i<=m;++i){
		char c;
		while((c=getchar())!='Q'&&c!='R');
		if(c=='R'){
			const int x=nxi(),v=nxi();
			ch[++cnr]=(mod){x,col[x],v};
			col[x]=v;
		}
		else{
			const int x=nxi(),y=nxi();
			++cnd;
			dt[cnd]=(data){x,y,cnr,cnd,x/N32,y/N32};
		}
	}
	std::sort(dt+1,dt+cnd);
	S::solve();
	for(int i=1;i<=cnd;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
