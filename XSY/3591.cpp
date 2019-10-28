#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=205;
lint n;
int m,val[N],tot;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

struct mtrx{
	lint v[N][N];

	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		memset(c.v,-10,sizeof(c.v));
		for(int i=0; i<=tot; ++i){
			for(int j=0; j<=tot; ++j){
				if(a.v[i][j]<0) continue;
				for(int k=0; k<=tot; ++k){
					apx(c.v[i][k],a.v[i][j]+b.v[j][k]);
				}
			}
		}
		return c;
	}
};

namespace S{
	struct node{
		int lk,v,c[26];
	}tr[N];

	inline void insert(const char *str,const int v){
		int p=0,len=strlen(str+1);
		for(int i=1; i<=len; ++i){
			int &k=tr[p].c[str[i]-'a'];
			if(!k) k=++tot;
			p=k;
		}
		tr[p].v+=v;
	}

	inline void build(){
		static int que[N];
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++],lk=tr[x].lk;
			if(x) assert(x!=lk),tr[x].v+=tr[lk].v;
			for(int i=0; i<26; ++i){
				const int y=tr[x].c[i];
				if(!y) tr[x].c[i]=tr[lk].c[i];
				else{
					que[tl++]=y;
					if(x) tr[y].lk=tr[lk].c[i];
				}
			}
		}
	}

	lint work(){
		mtrx step,res;
		memset(step.v,-10,sizeof(step.v));
		for(int i=0; i<=tot; ++i){
			for(int j=0; j<26; ++j){
				int k=tr[i].c[j];
				step.v[i][k]=tr[k].v;
			}
		}
		for(bool f=0; n; step=step*step,n>>=1){
			if(n&1){
				res=f?res*step:step;
				f=1;
			}
		}
		lint ans=0;
		for(int i=0; i<=tot; ++i){
			apx(ans,res.v[0][i]);
		}
		return ans;
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		static char str[N];
		scanf("%s",str+1);
		S::insert(str,val[i]);
	}
	S::build();
	printf("%lld\n",S::work());
	return 0;
}
