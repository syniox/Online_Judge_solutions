#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
typedef long long lint;
const int N=1e6+5;
int n,m;
struct data{
	int pos,size;
	bool mouse;
	bool operator < (const data &b) const {
		return pos<b.pos;
	}
}dt[N<<1];
struct hole{
	int pos,size;
	bool operator < (const hole &b) const {
		return pos<b.pos;
	}
};
struct mice{
	int pos,dis;
	bool operator < (const mice &b) const {
		return pos+dis<b.pos+b.dis;
	}
};

inline char get_c(){
	static char *h,*t,buf[200000];
	if(h==t){
		t=(h=buf)+fread(buf,1,200000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=get_c())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=get_c());
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return f?-x:x;
}

inline lint solve(){
	static int need_pt,need_pos[N];
	std::priority_queue <hole> qh;
	std::priority_queue <mice> qm;
	lint ans=0;
	for(int i=1;i<=n+m;++i){
		if(dt[i].mouse){
			if(qh.empty()){
				need_pos[++need_pt]=dt[i].pos;
				continue;
			}
			hole x=qh.top();
			ans+=dt[i].pos-x.pos;
			qm.push((mice){dt[i].pos,dt[i].pos-x.pos});
			qh.pop();
			if(--x.size) qh.push(x);
		}
		else{
			int w=dt[i].size;
			for(;w&&need_pt;--need_pt,--w){
				ans+=dt[i].pos-need_pos[need_pt];
			}
			if(!w) continue;
			for(;w&&!qm.empty();){
				const mice x=qm.top();
				if(dt[i].pos<x.pos+x.dis){
					const int dis=dt[i].pos-x.pos;
					ans+=dis-x.dis;
					--w;
					qh.push((hole){dt[i].pos-(x.dis-dis),1});
					qm.pop();
				}
				else qm=std::priority_queue <mice> ();
			}
			if(w) qh.push((hole){dt[i].pos,w});
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		dt[i]=(data){nxi(),0,1};
	}
	lint sum_w=0;
	for(int i=1;i<=m;++i){
		const int pos=nxi(),w=nxi();
		dt[i+n]=(data){pos,w,0};
		sum_w+=w;
	}
	if(sum_w<n){
		puts("-1");
		return 0;
	}
	std::sort(dt+1,dt+n+m+1);
	printf("%lld\n",solve());
	return 0;
}
