#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
typedef long long lint;
const int N=3e5+5;
int n,qa[N],qb[N],qc[N];
struct data{
	lint x,y;
	friend bool operator < (const data &a,const data &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
}dt[N];

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	static lint buk[N];
	n=nxi();
	for(int i=1; i<=n; ++i) qa[i]=nxi();
	for(int i=1; i<n; ++i) qb[i]=nxi();
	for(int i=1; i<n; ++i) qc[i]=nxi();
	lint pre_b=0,pre_c=0;
	for(int i=1; i<=n; ++i){
		if(qb[i]>qc[i]){
			puts("-1");
			return 0;
		}
		dt[i]=(data){(lint)qa[i]-pre_c,pre_b-(lint)qa[i]};
		pre_b+=qb[i],pre_c+=qc[i];
	}
	std::sort(dt+1,dt+n+1);
	int top=0;
	for(int i=1; i<=n; ++i){
		if(!top||buk[top]<=dt[i].y) buk[++top]=dt[i].y;
		else buk[std::upper_bound(buk+1,buk+top+1,dt[i].y)-buk]=dt[i].y;
	}
	printf("%d\n",n-top);
	return 0;
}
