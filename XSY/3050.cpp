#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=75,F=1<<16,L=4005;
const int mod=1e9+7;
int n,m,full,dp[N][F];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void FWT(int a[F],const int len){
	for(int i=1;i<len;i<<=1){
		for(int j=0;j<len;j+=i<<1){
			for(int k=0;k<i;++k) twk(a[j+i+k]+=a[j+k]);
		}
	}
}

inline void IFWT(int a[F],const int len){
	for(int i=len>>1;i;i>>=1){
		for(int j=0;j<len;j+=i<<1){
			for(int k=0;k<i;++k) twk(a[j+i+k]+=mod-a[j+k]);
		}
	}
}

inline void xor_rev(int a[F],int b[F],const int len){
	for(int i=0;i<len;++i){
		if(i<((len-1)^i)){
			int x=a[i],y=a[(len-1)^i];
			b[(len-1)^i]=x,b[i]=y;
		}
	}
}

inline void init(){
	static int buk[2][N][F];
	full=1<<(1<<m);
	for(int i=1;i<=m;++i){
		int res=0;
		for(int j=1<<(i-1);j<1<<m;j=(j+1)|1<<(i-1)){
			res|=1<<j;
		}
		++dp[0][res];
	}
	memcpy(buk[0][0],dp[0],full<<2);
	xor_rev(buk[0][0],buk[1][0],full);
	FWT(buk[0][0],full);
	FWT(buk[1][0],full);
	for(int i=1;i<=n;++i){
		memcpy(dp[i],buk[1][i-1],full<<2);
		for(int j=0;j<i;++j){
			for(int k=0;k<full;++k){
				dp[i][k]=(dp[i][k]+(lint)buk[1][j][k]*buk[0][i-j-1][k])%mod;
			}
		}
		memcpy(buk[0][i],dp[i],full<<2);
		IFWT(dp[i],full);
		memcpy(buk[1][i],dp[i],full<<2);
		xor_rev(buk[1][i],buk[1][i],full);
		FWT(buk[1][i],full);
	}
}

namespace S{
	int len,st,deny0,deny1,to_l[L],to_r[L];
	bool curq;
	char ch[L];

	bool get_val(int &l){
		if(ch[l]=='~') return get_val(++l)^1;
		if(ch[l]=='Q') return ++l,curq;
		if(ch[l]=='x'){
			l+=2;
			return st>>(ch[l-1]-'0'-1)&1;
		}
		int ans=1,tp=l+1;
		while(tp<to_r[l]){
			ans=(ans^1)|get_val(tp);
			while(ch[tp]=='-'||ch[tp]=='>') ++tp;
		}
		l=to_r[l]+1;
		return ans;
	}

	inline int solve(){
		static int stk[L];
		int top=deny0=deny1=0;
		scanf("%s",ch+1);
		len=strlen(ch+1);
		for(int i=len;i;--i){
			ch[i+1]=ch[i];
		}
		ch[1]='(';
		len+=2;
		ch[len]=')';
		for(int i=1;i<=len;++i){
			if(ch[i]=='(') stk[++top]=i;
			else if(ch[i]==')'){
				to_l[i]=stk[top];
				to_r[stk[top--]]=i;
			}
		}
		for(st=0;st<1<<m;++st){
			int tp;
			curq=0;
			if(!get_val(tp=1)) deny0|=1<<st;
			curq=1;
			if(!get_val(tp=1)) deny1|=1<<st;
			if(deny0&deny1) return 0;
		}
		int ans=0;
		for(int i=0;i<full;++i){
			if(!(((full-1)^i)&deny0)&&!(i&deny1)){
				twk(ans+=dp[n][i]);
			}
		}
		return ans;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	init();
	for(int q=nxi();q;--q){
		printf("%d\n",S::solve());
	}
	return 0;
}
