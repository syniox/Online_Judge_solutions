#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
typedef long long lint;
const int N=1e5+5;
int n,qx,qy,qz,hx[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint psh(std::priority_queue <int> &q1,std::priority_queue <int> &q2,
		const int pos,const int cos){
	if(!q2.empty()&&(lint)pos*qz-q2.top()<cos){
		const int tp=q2.top();
		q1.push(((lint)pos*qz<<1)-tp);
		q2.pop();
		return (lint)pos*qz-tp;
	}
	q1.push((lint)pos*qz+cos);
	return cos;
}

inline lint solve(){
	std::priority_queue <int> qi,qo;
	lint ans=0;
	for(int i=1;i<=n;++i){
		while(hx[i]){
			if(hx[i]<0) ++hx[i],ans+=psh(qo,qi,i,qy);
			else --hx[i],ans+=psh(qi,qo,i,qx);
		}
//		printf("%d: %lld\n",i,ans);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),qx=nxi(),qy=nxi(),qz=nxi();
	for(int i=1;i<=n;++i){
		int bef=nxi(),aft=nxi();
		hx[i]=aft-bef;
	}
	printf("%lld\n",solve());
	return 0;
}
