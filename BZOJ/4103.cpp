#include<iostream>
#include<cstdio>
#include<cstring>
#include<climits>
const int N=3e5+2;
int n,m,rt[N],sx[1002];

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=gtc())>'9'||c<'0');
	while(x=x*10+c-48,(c=gtc())>='0'&&c<='9');
	return x;
}
namespace T{
	int cnt;
	struct node{
		int s,c[2];
	}tr[N*15];
	void mod(int x,int t){
		int p=rt[t-1],np=++cnt;
		rt[t]=np;
		for(int i=30;i>=0;--i){
			tr[np]=tr[p];
			++tr[np].s;
			if(x&(1<<i)){
				p=tr[p].c[1];
				np=tr[np].c[1]=++cnt;
			}
			else{
				p=tr[p].c[0];
				np=tr[np].c[0]=++cnt;
			}
		}
		++tr[np].s;
	}
}

inline int solve(){
	using T::tr;
	static int p0[1002],p1[1002];
	int u=nxi(),d=nxi(),l=nxi(),r=nxi(),k=nxi(),ans=0;
	for(int i=u;i<=d;++i){
		p0[i]=rt[l-1];
		p1[i]=rt[r];
	}
	for(int i=30;i>=0;--i){
		int tps=0;
		bool fx=1;
		for(int j=u;j<=d;++j){
			bool tp=((sx[j]>>i)&1)^1;
			tps+=tr[tr[p1[j]].c[tp]].s;
			tps-=tr[tr[p0[j]].c[tp]].s;
		}
		if(tps<k){
			fx=0;
			k-=tps;
		}
		else ans|=1<<i;
		for(int j=u;j<=d;++j){
			bool tp=((sx[j]>>i)&1)^fx;
			p0[j]=tr[p0[j]].c[tp];
			p1[j]=tr[p1[j]].c[tp];
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	rt[0]=T::cnt=1;
	for(int i=1;i<=n;++i){
		sx[i]=nxi();
	}
	for(int i=1;i<=m;++i){
		T::mod(nxi(),i);
	}
	int q=nxi();
	while(q--){
		printf("%d\n",solve());
	}
	return 0;
}
