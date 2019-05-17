#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int N=5e5+5;
int n,totlen,pos0[N],pos1[N],spos[N],slen[N];
char *str[N];

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}

	template <class T>
		inline void apx(T &x,const T y){
			x<y?x=y:0;
		}

	template <class T>
		inline void apn(T &x,const T y){
			x>y?x=y:0;
		}
}
using namespace utils;

inline bool cmp_slen(const int x,const int y){
	return slen[x]<slen[y];
}

namespace G{
	int cnt,cscc,fir[N*6],bel[N*6],dfn[N*6],low[N*6];
	struct edge{
		int to,nx;
	}eg[N*14];

	inline void add(const int a,const int b){
		//printf("add: %d -> %d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int cnd,top,stk[N*6];
		stk[++top]=x;
		dfn[x]=low[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) tarjan(y);
			if(!bel[y]) apn(low[x],low[y]);
		}
		if(dfn[x]!=low[x]) return;
		++cscc;
		for(int i=stk[top--]; ; i=stk[top--]){
			bel[i]=cscc;
			if(i==x) break;
		}
	}
}

namespace S{
	int offs,cnt,tr[N<<1][2];
	bool invld[N<<1];

	inline void clear(){
		memset(tr,0,(cnt+1)*sizeof(tr[0]));
		cnt=0;
	}

	int pos(const char *str,const int len){
		assert(len);
		int p=0;
		for(int i=1; i<=len; ++i){
			int c=str[i]-'0';
			if(!tr[p][c]) return 0;
			p=tr[p][c];
		}
		return p;
	}

	int ins(const char *str,const int len){
		int p=0,lst;
		for(int i=1; i<=len; ++i){
			int c=str[i]-'0';
			lst=tr[p][c];
			tr[p][c]=++cnt;
			if(lst){
				memcpy(tr[cnt],tr[lst],sizeof(tr[cnt]));
			}
			p=cnt;
		}
		if(lst){
			G::add(p+offs,lst+offs);
		}
		return p;
	}

	void build_g(){
		for(int i=1; i<=cnt; ++i){
			if(tr[i][0]) G::add(i+offs,tr[i][0]+offs);
			if(tr[i][1]) G::add(i+offs,tr[i][1]+offs);
		}
	}

	bool get_vld(){
		static int id[N],que[N<<1];
		for(int i=1; i<=n; ++i){
			id[i]=i;
		}
		std::sort(id+1,id+n+1,cmp_slen);
		for(int i=1; i<=n; ++i){
			if(spos[i]) continue;
			pos0[i]=ins(str[i],slen[i]);
		}
		for(int i=n; i>=1; --i){
			int x=id[i];
			if(spos[x]) continue;
			int p=0;
			for(int j=1; j<=slen[x]; ++j){
				int c=str[x][j]-'0';
				p=tr[p][c];
				if(j==slen[x]&&invld[p]) return 0;
				invld[p]=1;
			}
			assert(p=pos0[x]);
		}
		for(int i=1; i<=n; ++i){
			if(!spos[i]) continue;
			str[i][spos[i]]='0';
			int p0=pos(str[i],slen[i]);
			str[i][spos[i]]='1';
			int p1=pos(str[i],slen[i]);
			assert(p0&&p1);
			if(invld[p0]&&invld[p1]) return 0;
			if(invld[p0]) G::add(i,i+n);
			if(invld[p1]) G::add(i+n,i);
		}
		memset(invld,0,totlen*2*sizeof(bool));
		for(int i=1; i<=n; ++i){
			if(!spos[i]) invld[pos0[i]]=1;
		}
		int hd=0,tl=0;
		for(int i=1; i<=cnt; ++i){
			if(invld[i]) que[tl++]=i;
		}
		while(hd!=tl){
			const int x=que[hd++];
			int c0=tr[x][0],c1=tr[x][1];
			if(c0&&!invld[c0]){
				que[tl++]=c0;
				invld[c0]=1;
			}
			if(c1&&!invld[c1]){
				que[tl++]=c1;
				invld[c1]=1;
			}
		}
		for(int i=1; i<=n; ++i){
			if(!spos[i]) continue;
			int p0=pos0[i],p1=pos1[i];
			if(invld[p0]&&invld[p1]) return 0;
			if(invld[p0]) G::add(i,i+n);
			if(invld[p1]) G::add(i+n,i);
		}
		return 1;
	}
}

void getstr(const int x){
	static char tmp[N];
	scanf("%s",tmp+1);
	int l=strlen(tmp+1);
	slen[x]=l;
	totlen+=l;
	for(int i=1; i<=l; ++i){
		if(tmp[i]=='?'){
			spos[x]=i;
			break;
		}
	}
	str[x]=new char[l+1];
	memcpy(str[x],tmp,l+1*sizeof(char));
}

void build(const int x){
	if(!spos[x]) return;
	char *str=::str[x];
	str[spos[x]]='0';
	const int lnk_0=S::pos(str,slen[x]);
	str[spos[x]]='1';
	const int lnk_1=S::pos(str,slen[x]);
	if(lnk_0) G::add(x+0,lnk_0+S::offs);
	if(lnk_1) G::add(x+n,lnk_1+S::offs);

	str[spos[x]]='1';
	pos0[x]=S::ins(str,slen[x]);
	G::add(pos0[x]+S::offs,x+0);
	str[spos[x]]='0';
	pos1[x]=S::ins(str,slen[x]);
	G::add(pos1[x]+S::offs,x+n);
}

bool jdg(){
	for(int i=1; i<=n; ++i){
		assert(G::bel[i]&&G::bel[i+n]);
		if(G::bel[i]==G::bel[i+n]) return 0;
	}
	return 1;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		getstr(i);
	}
	S::offs=n*2;
	for(int i=1; i<=n; ++i){
		build(i);
	}
	S::build_g();
	S::clear();
	S::offs=n*2+totlen*2;
	for(int i=n; i>=1; --i){
		build(i);
	}
	S::build_g();
	if(S::get_vld()==0){
		puts("NO");
		return 0;
	}
	for(int i=1; i<=n<<1; ++i){
		if(!G::bel[i]) G::tarjan(i);
	}
	puts(jdg()?"YES":"NO");
	return 0;
}
