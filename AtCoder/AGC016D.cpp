#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1e5+10;
int n,gdbtp,cn,fa[N],sz[N],qa[N],qb[N],qc[N],qd[N];

int get_rt(const int x){
	return fa[x]?fa[x]=get_rt(fa[x]):x;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int jdg(){
	memcpy(qc,qa,sizeof(qa));
	memcpy(qd,qb,sizeof(qb));
	std::sort(qc+1,qc+n+2);
	std::sort(qd+1,qd+n+2);
	for(int i=1;i<=n+1;++i){
		if(qc[i]!=qd[i]) return 0;
	}
	return 1;
}

inline int solve(){
	if(!jdg()) return -1;
	int ans=0;
	cn=std::unique(qc+1,qc+n+2)-qc-1;
	for(int i=1;i<=cn;++i){
		sz[i]=1;
	}
	for(int i=1;i<=n;++i){
		if(qa[i]!=qb[i]){
			++ans;
			gdbtp=std::lower_bound(qc+1,qc+cn+1,qa[i])-qc;
			const int x=get_rt(std::lower_bound(qc+1,qc+cn+1,qa[i])-qc);
			const int y=get_rt(std::lower_bound(qc+1,qc+cn+1,qb[i])-qc);
			if(x!=y){
				fa[x]=y;
				sz[y]+=sz[x];
			}
		}
	}
	if(ans==0) return 0;
	else ans-=1;
	for(int i=1;i<=cn;++i){
		ans+=(!fa[i]&&sz[i]>1);
	}
	const int tp=std::lower_bound(qc+1,qc+cn+1,qa[n+1])-qc;
	return ans+(sz[get_rt(tp)]==1);
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		qa[i]=nxi();
		qa[n+1]^=qa[i];
	}
	for(int i=1;i<=n;++i){
		qb[i]=nxi();
		qb[n+1]^=qb[i];
	}
	printf("%d\n",solve());
	return 0;
}
