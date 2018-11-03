#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
typedef long long lint;
const int N=1e5+2;
int n,cnr,hx[N],dp[N],to_l[N];
lint rab[60];
struct data{
	int pos,v;
	bool operator < (const data &b) const{
		return v==b.v?v<b.v:pos<b.pos;
	}
};

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	rab[1]=1,rab[2]=2;
	for(cnr=3;rab[cnr-1]<1e9;++cnr){
		rab[cnr]=rab[cnr-1]+rab[cnr-2];
	}
}

inline void get_l(){
	std::map <int,int> mp;
	for(int i=1;i<=n;++i){
		std::map <int,int> ::iterator it;
		to_l[i]=1;
		for(int j=1;j<=cnr;++j){
			const lint tp=rab[j]-hx[i];
			if(tp<0||tp>1e9) continue;
			if((it=mp.find(tp))!=mp.end()){
				apx(to_l[i],it->second+1);
			}
		}
		mp[hx[i]]=i;
	}
}

inline int solve(){
	std::deque <int> dq;
	dq.push_back(0);
	for(int i=1;i<=n;++i){
		while(!dq.empty()&&dq.front()<to_l[i]-1) dq.pop_front();
		dp[i]=dp[dq.front()]+1;
		while(!dq.empty()&&dp[dq.back()]>=dp[i]) dq.pop_back();
		dq.push_back(i);
	}
	return dp[n];
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	init();
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	get_l();
	for(int i=1;i<=n;++i){
		if(to_l[i]!=i) apx(to_l[i],to_l[i-1]);
	}
	printf("%d\n",solve());
	return 0;
}
