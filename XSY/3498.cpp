#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
const int N=1505;
const double eps=1e-9;
int n,m;
char src[N],tgt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

namespace S{
	int cnt;
	double dp[2][N];
	struct node{
		int s,lk,c[10];
		double v;
	}tr[N];

	void insert(const char *str,const int len,const double v){
		int p=0;
		for(int i=1; i<=len; ++i){
			if(!tr[p].c[str[i]-'0']){
				tr[p].c[str[i]-'0']=++cnt;
			}
			p=tr[p].c[str[i]-'0'];
		}
		++tr[p].s;
		tr[p].v+=v;
	}

	void build(){
		static int que[N];
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++],lk=tr[x].lk;
			tr[x].s+=tr[lk].s;
			tr[x].v+=tr[lk].v;
			for(int i=0; i<10; ++i){
				const int y=tr[x].c[i];
				if(!y) tr[x].c[i]=tr[lk].c[i];
				else{
					if(x) tr[y].lk=tr[lk].c[i];
					que[tl++]=y;
				}
			}
		}
	}

	bool jdg(const double tgt){
		dp[0][0]=0;
		for(int i=1; i<=cnt; ++i){
			dp[0][i]=-1e9;
		}
		for(int i=1; i<=cnt; ++i){
			tr[i].v-=tgt*tr[i].s;
		}
		for(int i=0; i<n; ++i){
			int p=i&1;
			for(int j=0; j<=cnt; ++j){
				dp[p^1][j]=-1e9;
			}
			if(src[i+1]=='.'){
				for(int j=0; j<=cnt; ++j){
					if(dp[p][j]<-1e8) continue;
					double cur=dp[p][j];
					for(int k=0; k<=9; ++k){
						int c=tr[j].c[k];
						apx(dp[p^1][c],cur+tr[c].v);
					}
				}
			}
			else{
				for(int j=0; j<=cnt; ++j){
					if(dp[p][j]<-1e8) continue;
					int c=tr[j].c[src[i+1]-'0'];
					apx(dp[p^1][c],dp[p][j]+tr[c].v);
				}
			}
		}
		for(int i=1; i<=cnt; ++i){
			tr[i].v+=tgt*tr[i].s;
		}
		double res=-1e9;
		for(int i=0; i<=cnt; ++i){
			apx(res,dp[n&1][i]);
			if(dp[n&1][i]>0) return 1;
		}
		return 0;
	}

	void getstr(char *tgt,const double ans){
		static int lst_p[N][N];
		static char lst_c[N][N];
		dp[0][0]=0;
		for(int i=1; i<=cnt; ++i){
			dp[0][i]=-1e9;
		}
		for(int i=0; i<n; ++i){
			int p=i&1;
			for(int j=0; j<=cnt; ++j){
				dp[p^1][j]=-1e9;
			}
			if(src[i+1]=='.'){
				for(int j=0; j<=cnt; ++j){
					if(dp[p][j]==-1e9) continue;
					double cur=dp[p][j];
					for(int k=0; k<=9; ++k){
						int c=tr[j].c[k];
						double wgt=tr[c].v-ans*tr[c].s;
						if(dp[p^1][c]<cur+wgt){
							lst_p[i+1][c]=j;
							lst_c[i+1][c]=k+'0';
							dp[p^1][c]=cur+wgt;
						}
					}
				}
			}
			else{
				for(int j=0; j<=cnt; ++j){
					if(dp[p][j]==-1e9) continue;
					int c=tr[j].c[src[i+1]-'0'];
					double v=dp[p][j]+tr[c].v-ans*tr[c].s;
					if(dp[p^1][c]<v){
						lst_p[i+1][c]=j;
						lst_c[i+1][c]=src[i+1];
						dp[p^1][c]=v;
					}
				}
			}
		}
		int pos=0;
		for(; pos<=cnt&&dp[n&1][pos]<=0; ++pos);
		assert(pos<=cnt);
		for(int i=n; i; --i){
			tgt[i]=lst_c[i][pos];
			pos=lst_p[i][pos];
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	static char str[N];
	n=nxi(),m=nxi();
	scanf("%s",src+1);
	for(int i=1; i<=m; ++i){
		scanf("%s",str+1);
		S::insert(str,strlen(str+1),log(nxi()));
	}
	S::build();
	double l=0,r=21,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		if(S::jdg(mid)) l=mid;
		else r=mid;
	}
	S::getstr(tgt,l);
	printf("%s\n",tgt+1);
	fprintf(stderr,"(l: %lf, ans: %lf)\n",l,pow(2.71828,l));
	return 0;
}
