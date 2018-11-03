#include <iostream>
#include <cstdio>
#include <cstring>
const int N=50005;
int ch[N*10];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	int cnt;
	struct node{
		int x,s,c[2];
	}tr[N*10];

	inline void add(const int len){
		int p=0;
		for(int i=1;i<=len;++i){
			if(!tr[p].c[ch[i]]) tr[p].c[ch[i]]=++cnt;
			p=tr[p].c[ch[i]];
		}
		++tr[p].x,++tr[p].s;
	}

	inline void build(const int x){
		if(tr[x].c[0]){
			build(tr[x].c[0]);
			tr[x].s+=tr[tr[x].c[0]].s;
		}
		if(tr[x].c[1]){
			build(tr[x].c[1]);
			tr[x].s+=tr[tr[x].c[1]].s;
		}
	}

	inline int calc(const int len){
		int p=0,ans=0;
		for(int i=1;i<=len;++i){
			ans+=tr[p].x;
			if(!tr[p].c[ch[i]]) return ans;
			p=tr[p].c[ch[i]];
		}
		return ans+tr[p].s;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	const int n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		const int len=nxi();
		for(int i=1;i<=len;++i) ch[i]=nxi();
		S::add(len);
	}
	S::build(0);
	for(int i=1;i<=m;++i){
		const int len=nxi();
		for(int i=1;i<=len;++i) ch[i]=nxi();
		printf("%d\n",S::calc(len));
	}
	return 0;
}
