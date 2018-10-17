#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2e5+2;
int n,bit,vl[19],dp[N],pos[N],dpl[1<<18],dpr[1<<18],to_l[N][19],to_r[N][19];
//dp[i]: 左侧覆盖1~i,右侧最多能够覆盖dp[i]~n(不使用未跳跃)

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	memset(dp,1,sizeof(dp));
	memset(dpr,1,sizeof(dpr));
	n=nxi(),vl[0]=nxi();
	for(;vl[bit];++bit){
		vl[bit+1]=vl[bit]>>1;
	}
	for(int i=1;i<=n;++i){
		pos[i]=nxi();
	}
	for(int i=0;i<=bit;++i){
		for(int s=1,t;s<=n;s=t+1){
			t=s;
			while(t<n&&pos[t+1]-pos[t]<=vl[i]) ++t;
			for(int j=s;j<=t;++j){
				to_l[j][i]=s,to_r[j][i]=t;
			}
		}
	}
	dpl[0]=0,dpr[0]=n+1;
	for(int i=0;i<1<<bit;++i){
		for(int j=1;j<=bit;++j){
			if(!(i&(1<<(j-1)))){
				apx(dpl[i|1<<(j-1)],to_r[dpl[i]+1][j]);
				if(dpr[i]){
					apn(dpr[i|1<<(j-1)],to_l[dpr[i]-1][j]);
				}
				else dpr[i|1<<(j-1)]=0;
			}
		}
	}
	for(int i=0;i<1<<bit;++i){
		apn(dp[dpl[i]],dpr[((1<<bit)-1)^i]);
	}
	for(int i=n;i;--i){
		apn(dp[i-1],dp[i]);
	}
	for(int i=1;i<=n;++i){
		puts(dp[to_l[i][0]-1]<=to_r[i][0]+1?"Possible":"Impossible");
	}
	return 0;
}
