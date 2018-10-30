#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <list>
typedef long long lint;
const int N=3e5+5;
int n,m,q,cnt_mp,des[N];
std::map <int,int> mp[N];
struct data{
	int tick,ov[2],rv[2],sz[2];
	//ov: single
	//0: x to y, 1: y to x first
	std::list <int> que[2];
}dt[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())<'0');
	while(x=x*10-48+c,(c=getchar())>='0');
	return x;
}

inline void init(){
	for(int i=1;i<N;++i){
		dt[i].ov[0]=dt[i].ov[1]=(int)1e8;
		dt[i].rv[0]=dt[i].rv[1]=(int)1e8;
	}
}

inline int get_mp(int x,int y,int &rev){
	if(x>y){
		rev=1,std::swap(x,y);
	}
	if(mp[x].find(y)==mp[x].end()){
		mp[x][y]=++cnt_mp;
	}
	return mp[x][y];
}

inline lint clear_r(const int t,const bool f){
	std::list <int> ::iterator it0,it1;
	it0=dt[t].que[f&1].begin();
	it1=dt[t].que[f^1].begin();

	std::list <int> ::iterator end0,end1;
	end0=dt[t].que[f&1].end();
	end1=dt[t].que[f^1].end();

	lint ans=0;
	while(it0!=end0&&it1!=end1){
		while(it1!=end1&&(*it1)<(*it0)){
			++it1;
		}
		if(it1!=end1){
			ans+=dt[t].rv[f];
			it0=dt[t].que[f&1].erase(it0);
			it1=dt[t].que[f^1].erase(it1);
			--dt[t].sz[0];
			--dt[t].sz[1];
		}
	}
	return ans;
}

inline lint clear_o(const int t){
	const lint ans0=(lint)dt[t].ov[0]*dt[t].sz[0];
	const lint ans1=(lint)dt[t].ov[1]*dt[t].sz[1];
	dt[t].sz[0]=0;
	dt[t].sz[1]=0;
	return ans0+ans1;
}

inline lint calc(const int t){
	apn(dt[t].ov[0],dt[t].rv[0]);
	apn(dt[t].ov[1],dt[t].rv[1]);
	lint ans=0;
	int vr[]={dt[t].rv[0],dt[t].rv[1]};
	int vo=dt[t].ov[0]+dt[t].ov[1];
	if(vr[0]<vo&&vr[1]<vo){
		ans+=clear_r(t,vr[1]<vr[0]);
		ans+=clear_r(t,vr[1]>=vr[0]);
	}
	else if(vr[0]<vo) ans+=clear_r(t,0);
	else if(vr[1]<vo) ans+=clear_r(t,1);
	ans+=clear_o(t);
	return ans;
}

inline lint solve(){
	lint ans=0;
	for(int i=1;i<=cnt_mp;++i){
		ans+=calc(i);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	init();
	for(int i=1;i<=q;++i){
		des[i]=nxi();
		if(i==1) continue;
		int x=des[i-1],y=des[i],rev=0;
		const int cur=get_mp(x,y,rev);
		dt[cur].que[rev].push_back(++dt[cur].tick);
		++dt[cur].sz[rev];
	}
	m=nxi();
	for(int i=1;i<=m;++i){
		int x=nxi(),y=nxi(),rev=0,val;
		char type;
		while((type=getchar())!='R'&&type!='O');
		val=nxi();
		const int cur=get_mp(x,y,rev);
		if(type=='R') apn(dt[cur].rv[rev],val);
		else apn(dt[cur].ov[rev],val);
	}
	printf("%lld\n",solve());
	return 0;
}
