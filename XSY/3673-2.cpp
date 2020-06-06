#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
int n,qa,qb,dis[26][26],cyc_len[26];
int *bs[26],cbs[26],*bt[26],cbt[26];
int des[N][26];
char nxt[26],src[N],tgt[N];
bool vld[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

lint gcd(lint x,lint y){
	return y?gcd(y,x%y):x;
}
lint lcm(lint x,lint y){
	return x&&y?x/gcd(x,y)*y:x+y;
}

void exgcd(lint &a,lint &b,const lint x,const lint y,const int c){
	if(!y){
		assert(c%x==0);
		a=c/x,b=0;
		return;
	}
	exgcd(a,b,y,x%y,c);
	lint tmp=a-x/y*b;
	a=b,b=tmp;
}

void get_dis(){
	static bool vis[N];
	static int cyc[N];
	memset(dis,-1,sizeof(dis));
	for(int i=0; i<26; ++i){
		if(vis[i]) continue;
		int sz=0;
		for(int j=i; !vis[j]; j=nxt[j]){
			vis[cyc[sz++]=j]=1;
		}
		for(int j=0; j<sz; ++j){
			int x=cyc[j],l=0;
			for(int k=j; dis[x][cyc[k]]==-1; k=(k+qb)%sz,++l){
				dis[x][cyc[k]]=l;
			}
			cyc_len[x]=l;
		}
	}
}

void get_num(char *str,int **bk,int *cbk){
	static int cnt[26];
	memset(cnt,0,sizeof(cnt));
	for(int i=0; i<n; ++i){
		++cnt[str[i]-'a'];
	}
	for(int i=0; i<26; ++i){
		if(cnt[i]) bk[i]=new int[cnt[i]];
	}
	for(int i=0; i<n; ++i){
		bk[str[i]-'a'][cbk[str[i]-'a']++]=i;
	}
}

void get_vld(){
	static int d[N],nxt[N];
	memset(des,-1,sizeof(des));
	for(int i=0; i<26; ++i){
		int cl=cbs[i];
		for(int j=1; j<=cl; ++j){
			d[j]=(bs[i][j%cl]-bs[i][j-1]+n)%n;
		}
		for(int p=0,j=2; j<=cl; ++j){
			while(p&&d[p+1]!=d[j]) p=nxt[p];
			nxt[j]=p+=d[p+1]==d[j];
		}
		for(int j=0; j<26; ++j){
			if(cbt[j]!=cbs[i]) continue;
			int p=0;
			for(int k=1; k<cl*2; ++k){
				int t=(bt[j][k%cl]-bt[j][(k-1)%cl]+n)%n;
				while(p&&d[p+1]!=t) p=nxt[p];
				if((p+=d[p+1]==t)==cl){
					int st=k-cl;
					des[(bs[i][0]-bt[j][st]+n)%n][i]=j;
					p=nxt[p];
				}
			}
		}
	}
}

lint solve(const int t,const int step){
	static int req[30],buk[30],qr[30];
	memset(buk,-1,sizeof(buk));
	int top=0;
	req[++top]=n/gcd(n,qa);
	qr[top]=step;
	for(int i=0; i<26; ++i){
		if(!cbs[i]) continue;
		if(des[t][i]==-1)
			return 2e18;
		int cl=cyc_len[i],d=dis[i][des[t][i]];//des[t][i]出错
		if(d==-1||(~buk[cl]&&buk[cl]!=d))
			return 2e18;
		buk[cl]=d;
	}
	for(int i=2; i<=26; ++i){
		if(~buk[i]) req[++top]=i,qr[top]=buk[i];
	}
	for(int i=top; i>1; --i){
		lint p1,p2;
		if((qr[i-1]-qr[i])%gcd(req[i],req[i-1]))
			return 2e18;
		exgcd(p1,p2,req[i],-req[i-1],qr[i-1]-qr[i]);
		lint lm=lcm(req[i],req[i-1]),res=((p1*req[i]+qr[i])%lm+lm)%lm;
		req[i-1]=lm,qr[i-1]=res;
	}
	return qr[1]?qr[1]:req[1];
}

int main(){
	n=nxi(),qa=nxi(),qb=nxi();
	scanf("%s%s%s",nxt,src,tgt);
	for(int i=0; i<26; ++i){
		nxt[i]-='a';
	}
	get_num(src,bs,cbs);
	get_num(tgt,bt,cbt);
	get_dis();
	get_vld();
	lint ans=2e18;
	for(int i=0,j=0; ; ++j){
		apn(ans,solve(i,j));
		if(!(i=(i+qa)%n)) break;
	}
	ans=ans==2e18?-1ll:ans;
	printf("%lld\n",ans);
	return 0;
}
