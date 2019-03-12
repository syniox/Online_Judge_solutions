#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=205;
const int mod=10007;
int n,len;
char ch[N];

class mtrx{
	public:
		int sz,n[305][305];
		mtrx(int len=0){
			sz=len;
			memset(n,0,sizeof(sz));
		}
		friend inline mtrx operator * (const mtrx &a,const mtrx &b);
		inline void oput(){
			for(int i=0; i<sz; ++i){
				for(int j=0; j<sz; ++j){
					printf("%d ",n[i][j]);
				}
				puts("");
			}
		}
};

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline mtrx operator * (const mtrx &a,const mtrx &b){
	assert(a.sz==b.sz);
	mtrx c;
	memset(c.n,0,sizeof(c.n));
	c.sz=a.sz;
	for(int i=0; i<a.sz; ++i){
		for(int j=i; j<a.sz; ++j){
			lint tp=0;
			for(int k=i; k<=j; ++k){
				tp+=a.n[i][k]*b.n[k][j];
			}
			c.n[i][j]=tp%mod;
		}
	}
	return c;
}

namespace G{
	int dp[N][N][N],res[N];
	//dp[i][j]: 到i点经过j个(端点字符不同, 自环权24)的路径数
	//res[i]: 经过i个type1点结束的总方案数
	inline void clear(){
		memset(dp,0,sizeof(dp));
		memset(res,0,sizeof(res));
	}

	inline void build(){
		//左边准备匹配第i位，右边准备匹配第j位
		dp[1][len][0]=1;
		for(int i=1; i<=len; ++i){
			for(int j=len; j>=i; --j){
				for(int k=0; k<len; ++k){
					const int cur=dp[i][j][k];
					if(!cur) continue;
					if(ch[i]==ch[j]){
						twk(dp[i+1][j-1][k]+=cur);
					}
					else{
						twk(dp[i+1][j][k+1]+=cur);
						twk(dp[i][j-1][k+1]+=cur);
					}
				}
			}
		}
	}

	inline void get_res(bool flag){
		for(int i=1; i<=len; ++i){
			for(int k=0; k<len; ++k){
				if(!flag) twk(res[k]+=dp[i][i][k]);
				if(ch[i]==ch[i+1]) twk(res[k]+=dp[i][i+1][k]);
			}
		}
	}

	inline mtrx get_mtrx(){
		const int tot=(len*3>>1)+1;
		mtrx step(tot+1);
		//i=cnt24,端点不同
		/*
		for(int i=0; i<len; ++i){
			printf("%d ",res[i]);
		}
		puts("");
		*/
		for(int i=0; i<len; ++i){
			const int cnt25=(len-i+1)>>1;
			step.n[cnt25-1][tot-i]=res[i];
			step.n[cnt25-1][cnt25-1]=25;
			step.n[tot-i][tot-i]=24;
			if(cnt25<(len+1)>>1){
				step.n[cnt25-1][cnt25]=1;
			}
			if(i) step.n[tot-i][tot-i+1]=1;
		}
		step.n[tot][tot]=26;
		return step;
	}
}

inline mtrx fpow(mtrx x,int t){
	mtrx res;
	res.sz=x.sz;
	for(int i=0; i<x.sz; ++i) res.n[i][i]=1;
	for(; t; t>>=1,x=x*x){
		if(t&1) res=res*x;
	}
	return res;
}

int main(){
	scanf("%s",ch+1);
	n=nxi();
	len=strlen(ch+1);
	G::build();
	G::get_res(0);
	const int tot=(len*3>>1)+1;
	mtrx step(G::get_mtrx());
	//printf("step: \n");
	//step.oput();
	//mtrx res=fpow(step,(n+len+1)>>1);
	if(((n+len)&1)==0){
		printf("%d\n",fpow(step,((n+len+1)>>1)).n[0][tot]);
		return 0;
	}
	mtrx res=fpow(step,((n+len+1)>>1)-1);
	//printf("res: \n");
	//res.oput();
	G::get_res(1);
	step=G::get_mtrx();
	//printf("step: \n");
	//step.oput();
	//puts("ans:");
	//(res*step).oput();
	printf("%d\n",((res*step).n[0][tot]+mod)%mod);
	return 0;
}
