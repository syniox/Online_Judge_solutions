#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <bitset>
typedef long long lint;
const int N=1005;
const int mod=1e9+7;
int p,q,s,m,rk_p[N][N],rk_s[N][N];
//rk_{*}[i][j]: {*}行i列秩为j的矩阵数
bool type,tgt_mtrx[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void get_rk_mtrx(int rk[N][N],int p,int m){
	rk[0][0]=1;
	for(int i=0; i<=m; ++i){
		for(int j=0; j<=i; ++j){
			if(!rk[i][j]) continue;
			int pow2_j=fpow(2,j);
			rk[i+1][j]=(rk[i+1][j]+(lint)rk[i][j]*pow2_j)%mod;
			rk[i+1][j+1]=(rk[i+1][j+1]+(lint)rk[i][j]*(fpow(2,p)+mod-pow2_j))%mod;
		}
	}
}

inline int get_ans(const int rank){
	int ans=0;
	for(int i=rank; i<=q; ++i){
		ans=(ans+(lint)rk_p[q][i]*rk_s[i][rank]%mod*fpow(2,s*(q-i)))%mod;
	}
	return (lint)ans*fpow(rk_p[s][rank],mod-2)%mod;
}

namespace B{
	std::bitset <N> mtrx[N],bel_mtrx[N];
	std::bitset <N> bel_zero[N<<1];
	int cnt_zero;
	bool vis[N],used[N<<1];

	inline bool insert(std::bitset <N> cur_mtrx,std::bitset <N> cur_bel){
		for(int j=0; j<s; ++j){
			if(cur_mtrx[j]){
				if(vis[j]){
					cur_mtrx^=mtrx[j];
					cur_bel^=bel_mtrx[j];
				}
				else{
					vis[j]=1;
					mtrx[j]=cur_mtrx;
					bel_mtrx[j]=cur_bel;
					return 1;
				}
			}
		}
		bel_zero[cnt_zero++]=cur_bel;
		return 0;
	}

	inline bool remove(const int row){
		int del_base=-1;
		for(int i=0; i<cnt_zero&&del_base==-1; ++i){
			if(!used[i]&&bel_zero[i][row]==1) del_base=i;
		}
		if(~del_base){
			for(int i=0; i<cnt_zero; ++i){
				if(!used[i]&&i!=del_base&&bel_zero[i][row]==1){
					bel_zero[i]^=bel_zero[del_base];
				}
			}
			for(int i=0; i<s; ++i){
				if(bel_mtrx[i][row]){
					bel_mtrx[i]^=bel_zero[del_base];
				}
			}
			used[del_base]=1;
			return 0;
		}
		else{
			for(int i=s-1; i>=0; --i){
				if(bel_mtrx[i][row]==1){
					if(del_base==-1) del_base=i;
					else{
						bel_mtrx[i]^=bel_mtrx[del_base];
						mtrx[i]^=mtrx[del_base];
					}
				}
			}
			if(~del_base){
				vis[del_base]=0;
				mtrx[del_base].reset();
				bel_mtrx[del_base].reset();
				return 1;
			}
			return 0;
		}
	}

	inline void solve(){
		std::bitset <N> cur_mtrx,cur_bel;
		int rnk=0;
		for(int i=0; i<p; ++i){
			cur_mtrx.reset();
			cur_bel.reset();
			for(int j=0; j<s; ++j){
				cur_mtrx[j]=tgt_mtrx[i][j];
			}
			cur_bel[i]=1;
			rnk+=insert(cur_mtrx,cur_bel);
		}
		int ans=get_ans(rnk);
		printf("%d\n",ans);
		for(int i=1; i<=m; ++i){
			int row=(nxi()^(type*ans))-1;
			rnk-=remove(row);
			cur_mtrx.reset();
			cur_bel.reset();
			for(int j=0; j<s; ++j){
				cur_mtrx[j]=nxi();
			}
			cur_bel[row]=1;
			rnk+=insert(cur_mtrx,cur_bel);
			printf("%d\n",ans=get_ans(rnk));
		}
	}
}

int main(){
	p=nxi(),q=nxi(),s=nxi(),m=nxi();
	type=nxi();
	for(int i=0; i<p; ++i){
		for(int j=0; j<s; ++j){
			tgt_mtrx[i][j]=nxi();
		}
	}
	get_rk_mtrx(rk_p,p,std::max(q,s));
	get_rk_mtrx(rk_s,s,q);
	B::solve();
	return 0;
}
