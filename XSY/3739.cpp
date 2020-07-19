#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=2005;
const int Sigma=5;
const int mod=998244353;
int n,m,pw5[N];
char str[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int qunused(){
	static bool vis[Sigma];
	for(int i=1; i<=n; ++i){
		vis[str[i]-'a']=1;
	}
	int cnt=0;
	for(int i=0; i<Sigma; ++i){
		cnt+=!vis[i];
	}
	return (lint)cnt*pw5[m-1]%mod;
}

void getnx(const char *str,int *nx,const int len,int go[N][Sigma]=0){
	nx[0]=nx[1]=0;
	for(int i=2,j=0; i<=len; ++i){
		while(j&&str[j+1]!=str[i]) j=nx[j];
		j+=str[j+1]==str[i];
		nx[i]=j;
	}
	if(!go) return;
	memset(go,0,(len+1)*sizeof(go[0]));
	for(int i=0; i<=len; ++i){
		if(i<len) go[i][str[i+1]-'a']=i+1;
		for(int j=0; j<Sigma; ++j){
			if(!go[i][j]) go[i][j]=go[nx[i]][j];
		}
	}
}

int solve(const int st){
	//todo: 特殊处理结尾
	static int nx[N],minnx[N],go[N][Sigma],reqc[N][Sigma],invld[N][Sigma];//remove go
	static int invcnt[N];
	memset(reqc,10,sizeof(reqc));
	memset(invcnt,0,sizeof(invcnt));
	memset(invld,0,sizeof(invld));
	const int len=n-st+1;
	getnx(str+st-1,nx,len,go);
	for(int i=1; i<=len; ++i){
		minnx[i]=nx[i]?minnx[nx[i]]:i;
	}
	for(int p=0,i=1; i<=n; ++i){
		int q=go[p][str[i]-'a'];
		if(q&&p){
			if(q!=p+1){
				++invcnt[p+1];
				--invcnt[m+1];
			}
			if(minnx[q]<p){
				++invcnt[p];
				--invcnt[p+1];
			}
		}
		if(q){
			apn(reqc[p][str[i]-'a'],minnx[q]);
		}
		p=q;
	}
	for(int i=len; i; --i){
		const int f=nx[i];
		bool ivld=0;
		if(i<len){
			invld[i][str[i+st]-'a']=1;
		}
		for(int j=0; j<Sigma; ++j){
			invld[f][j]|=invld[i][j];
			ivld|=reqc[i][j]<=i;
			if(reqc[i][j]<=f&&str[st+f]-'a'!=j){
				++invcnt[f+1];
				--invcnt[i];
			}
			apn(reqc[f][j],reqc[i][j]);
		}
		if(ivld){
			++invcnt[i];
			--invcnt[i+1];
		}
	}
	for(int i=1; i<=len; ++i){
		invcnt[i]+=invcnt[i-1];
	}
	int minp=0,ans=0;
	for(int p=0,i=1; i<=n; ++i){
		p=go[p][str[i]-'a'];
		if(st+p-1==i) break;
		apx(minp,p);
	}
	for(int i=minp+1; i<=min(len,m); ++i){
		if(invcnt[i]) continue;
		int vldcnt=0;
		for(int j=0; j<Sigma; ++j){
			vldcnt+=!invld[i][j];
		}
		ans=(ans+(i==m?1ll:(lint)vldcnt*pw5[m-i-1]))%mod;
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=pw5[0]=1; i<=m; ++i){
		pw5[i]=pw5[i-1]*5ll%mod;
	}
	scanf("%s",str+1);
	int ans=qunused();
	for(int i=1; i<=n; ++i){
		ans=(ans+solve(i))%mod;
	}
	eprintf("real ans: %d\n",ans);
	ans=(lint)ans*fpow(fpow(Sigma,m),mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}
