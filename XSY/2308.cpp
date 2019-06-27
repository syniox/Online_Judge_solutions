#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=105;
const int mod=1e9+7;
int n,m,q,lenbas[51],st[51][N];
char bas[51][N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

//A-C Automation
namespace ACA{
	int cnt,san_tot;
	struct node{
		int lk,c[26];
		bool end;
	}tr[N];

	void insert(const char *str,const int len){
		int p=0;
		for(int i=1; i<=len; ++i){
			int &k=tr[p].c[str[i]-'a'];
			if(!k) k=++cnt;
			p=k;
		}
		tr[p].end=1;
	}

	void build(){
		static int que[N];
		int hd=0,tl=1;
		que[0]=0;
		while(hd!=tl){
			const int x=que[hd++],lk=tr[x].lk;
			tr[x].end|=tr[lk].end;
			for(int i=0; i<26; ++i){
				const int y=tr[x].c[i];
				if(!y) tr[x].c[i]=tr[lk].c[i];
				else{
					if(x!=lk) tr[y].lk=tr[lk].c[i];
					que[tl++]=y;
				}
			}
		}
	}

	void get_st(){
		static int id[N];
		for(int i=1; i<=n; ++i){
			const int len=lenbas[i];
			for(int j=0; j<=cnt; ++j){
				if(tr[j].end) continue;
				int p=j;
				for(int k=1; k<=len; ++k){
					p=tr[p].c[bas[i][k]-'a'];
					if(tr[p].end){
						p=-1;
						break;
					}
				}
				st[i][j]=p;
			}
		}
		for(int i=0; i<=cnt; ++i){
			if(!tr[i].end) id[i]=san_tot++;
		}
		for(int i=1; i<=n; ++i){
			for(int j=0; j<=cnt; ++j){
				int tmp=st[i][j];
				st[i][j]=-1;
				if(!tr[j].end&&~tmp){
					st[i][id[j]]=id[tmp];
				}
			}
		}
	}
}

namespace S1{
	int dp[N][N];

	void main(){
		const int tot=ACA::san_tot;
		dp[0][0]=1;
		for(int i=0; i<q; ++i){
			for(int j=0; j<tot; ++j){
				if(!dp[i][j]) continue;
				const int cur=dp[i][j];
				for(int k=1; k<=n; ++k){
					const int nxt=i+lenbas[k];
					if(nxt<=q&&~st[k][j]){
						dp[nxt][st[k][j]]=(dp[nxt][st[k][j]]+cur)%mod;
					}
				}
			}
		}
		int ans=0;
		for(int i=0; i<tot; ++i){
			ans=(ans+dp[q][i])%mod;
		}
		printf("%d\n",ans);
	}
}

namespace S2{
	int tot,t2;
	struct mtrx{
		int v[202][202];

		inline void clr(){
			memset(v,0,sizeof(v));
		}
		friend mtrx operator * (const mtrx &a,const mtrx &b){
			mtrx c;
			c.clr();
			for(int i=0; i<t2; ++i){
				for(int j=0; j<t2; ++j){
					for(int k=0; k<t2; ++k){
						c.v[i][k]=(c.v[i][k]+(lint)a.v[i][j]*b.v[j][k])%mod;
					}
				}
			}
			return c;
		}
	};

	struct vec{
		int v[202];

		inline void clr(){
			memset(v,0,sizeof(v));
		}
		friend vec operator * (const vec &a,const mtrx &b){
			vec c;
			c.clr();
			for(int i=0; i<t2; ++i){
				for(int j=0; j<t2; ++j){
					c.v[j]=(c.v[j]+(lint)a.v[i]*b.v[i][j])%mod;
				}
			}
			return c;
		}
	};

	mtrx fpow(mtrx x,int t){
		mtrx res;
		res.clr();
		for(int i=0; i<t2; ++i){
			res.v[i][i]=1;
		}
		for(; t; x=x*x,t>>=1){
			if(t&1) res=res*x;
		}
		return res;
	}

	void main(){
		tot=ACA::san_tot;
		t2=tot+tot;
		mtrx step;
		step.clr();
		for(int i=1; i<=n; ++i){
			int offs=tot*(lenbas[i]==1);
			for(int j=0; j<tot; ++j){
				if(~st[i][j]) ++step.v[j+offs][st[i][j]+tot];
			}
		}
		for(int i=0; i<tot; ++i){
			++step.v[i+tot][i];
		}
		mtrx res_mat=fpow(step,q);
		vec res_vec;
		res_vec.clr();
		res_vec.v[0]=1;
		for(int i=0; i<tot; ++i){
			res_vec.v[i+tot]=step.v[tot][i+tot];
		}
		res_vec=res_vec*res_mat;
		int ans=0;
		for(int i=0; i<tot; ++i){
			ans=(ans+res_vec.v[i])%mod;
		}
		printf("%d\n",ans);
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",bas[i]+1);
		lenbas[i]=strlen(bas[i]+1);
	}
	for(int i=1; i<=m; ++i){
		static char str[N];
		scanf("%s",str+1);
		ACA::insert(str,strlen(str+1));
	}
	ACA::build();
	ACA::get_st();
	if(q<=100) S1::main();
	else S2::main();
	return 0;
}
