
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long lint;
const int N=2e5+2;
int n,m,cnc,cnd,hx[N],qry_l[N],qry_r[N],to_l[N],to_r[N];
lint ans[N];
struct chan{
	int x,l,r,v;
	bool operator < (const chan &b) const {
		return x<b.x;
	}
}chn[N*3];
struct data{
	int x,id,v;
	bool operator < (const data &b) const {
		return x<b.x;
	}
}dt[N<<1];

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace BIT{
	lint tr1[N],tr2[N];
	inline void mod(int x,const int v){
		const int tp=x*v;
		for(;x<N;x+=x&-x){
			tr1[x]+=v,tr2[x]+=tp;
		}
	}
	inline lint ask(const int x){
		lint ans1=0,ans2=0;
		for(int p=x;p;p-=p&-p){
			ans1+=tr1[p],ans2+=tr2[p];
		}
		return ans1*(x+1)-ans2;
	}
	inline void mod(const int x,const int y,const int v){
		mod(x,v);
		mod(y+1,-v);
	}
	inline lint ask(const int x,const int y){
		return ask(y)-ask(x-1);
	}
}

inline void init(){
	static int stk[N];
	int top=0;
	for(int i=1;i<=n;++i){
		for(;top&&hx[stk[top]]<hx[i];--top){
			to_r[stk[top]]=i;
		}
		to_l[i]=stk[top];
		stk[++top]=i;
	}
	for(;top;--top) to_r[stk[top]]=n+1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	const int val1=nxi(),val2=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	init();
	for(int i=1;i<=n;++i){
		if(to_l[i]>0){
			if(to_r[i]<=n) chn[++cnc]=(chan){to_l[i],to_r[i],to_r[i],val1};
			if(to_r[i]>i+1) chn[++cnc]=(chan){to_l[i],i+1,to_r[i]-1,val2};
		}
		if(to_r[i]<=n&&to_l[i]<i-1){
			chn[++cnc]=(chan){to_r[i],to_l[i]+1,i-1,val2};
		}
	}
	std::sort(chn+1,chn+cnc+1);
	for(int i=1;i<=m;++i){
		qry_l[i]=nxi(),qry_r[i]=nxi();
		ans[i]=(lint)(qry_r[i]-qry_l[i])*val1;
		dt[++cnd]=(data){qry_l[i]-1,i,-1};
		dt[++cnd]=(data){qry_r[i],i,1};
	}
	std::sort(dt+1,dt+cnd+1);
	for(int i=1,j=1;i<=cnd;++i){
		for(;j<=cnc&&chn[j].x<=dt[i].x;++j){
			BIT::mod(chn[j].l,chn[j].r,chn[j].v);
		}
		ans[dt[i].id]+=BIT::ask(qry_l[dt[i].id],qry_r[dt[i].id])*dt[i].v;
	}
	for(int i=1;i<=m;++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
