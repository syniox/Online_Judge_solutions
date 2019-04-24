#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=5e5+5;
int n,m,old_n,q,opt[N],optarg[N],lg2[1<<20];
int curpos,plen[N],lstpos[N];
char str[N<<1];
bool vis[N],inq[N];
struct _pair{
	int x,y;
}stat[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=2; i<=n+m; ++i){
		lg2[i]=lg2[i>>1]+1;
	}
}

namespace S{
	int n,sa[N<<1],sum[N<<1],rnk[N<<1],hgt[20][N<<1];

	inline int get_rk(const int x){
		return x>n?0:rnk[x];
	}

	void qsort(int *sa,const int *rnk,const int *idx){
		static int buk[N<<1];
		const int lim=std::max(28,n);
		memset(buk+1,0,lim*sizeof(int));
		for(int i=1; i<=n; ++i){
			++buk[rnk[idx[i]]];
		}
		for(int i=1; i<=lim; ++i){
			buk[i]+=buk[i-1];
		}
		for(int i=n; i>=1; --i){
			sa[buk[rnk[idx[i]]]--]=idx[i];
		}
	}

	void build(const char *str,const int old_n,const int n){
		static int tmp[N<<1];
		S::n=n;
		for(int i=1; i<=n; ++i){
			tmp[i]=i;
			rnk[i]=str[i]-'a'+1;
		}
		qsort(sa,rnk,tmp);
		for(int w=1,cnt_rk=0; cnt_rk<n; w<<=1){
			for(int i=1; i<=w; ++i){
				tmp[i]=n-w+i;
			}
			cnt_rk=w;
			for(int i=1; i<=n; ++i){
				if(sa[i]>w) tmp[++cnt_rk]=sa[i]-w;
			}
			qsort(sa,rnk,tmp);
			cnt_rk=0;
			for(int i=1; i<=n; ++i){
				if(rnk[sa[i]]!=rnk[sa[i-1]]||get_rk(sa[i]+w)!=get_rk(sa[i-1]+w)){
					++cnt_rk;
				}
				tmp[sa[i]]=cnt_rk;
			}
			memcpy(rnk+1,tmp+1,n*sizeof(int));
		}
		for(int i=1,p=0; i<=n; ++i){
			p=std::max(p-1,0);
			if(rnk[i]==1) continue;
			for(int j=sa[rnk[i]-1]; j+p<=n&&i+p<=n&&str[j+p]==str[i+p]; ++p);
			hgt[0][rnk[i]]=p;
		}
		for(int i=1; i<20; ++i){
			for(int j=1<<(i-1); j<=n; ++j){
				hgt[i][j]=std::min(hgt[i-1][j],hgt[i-1][j-(1<<(i-1))]);
			}
		}
		for(int i=1; i<=n; ++i){
			sum[i]=sum[i-1]+(sa[i]<=old_n);
		}
	}

	inline int getlcp(int x,int y){
		x=rnk[x],y=rnk[y];
		if(x>y) std::swap(x,y);
		int lg=lg2[y-x];
		return std::min(hgt[lg][y],hgt[lg][x+(1<<lg)]);
	}
}

_pair merge(const _pair pr,const int tl,const int tr,const int len){
	if(tl>tr) return pr;
	_pair ans;
	int l,r,mid,tmp;
	l=pr.x,r=pr.y;
	while(l!=r){
		mid=(l+r)>>1;
		if((tmp=S::getlcp(S::sa[pr.x]+len,tl))>=len) r=mid;
		else if(str[pr.x+len+tmp]>str[tl+tmp]) r=mid; 
		else l=mid+1;
	}
	ans.x=l;
	l=l-1,r=pr.y;
	while(l!=r){
		mid=(l+r+1)>>1;
		if((tmp=S::getlcp(S::sa[pr.x]+len,tl))>=len) l=mid;
		else if(str[pr.x+len+tmp]<str[tl+tmp]) l=mid;
		else r=mid-1;
	}
	ans.y=r;
	return ans;
}

inline int ask(const int x){
	_pair res=merge(stat[x],lstpos[x],curpos,plen[x]);
	return S::sum[res.y]-S::sum[res.x]+1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	nxi();
	n=nxi(),m=nxi(),q=nxi();
	init();
	scanf("%s",str+1);
	old_n=n;
	str[++n]='z'+1;
	for(int i=1; i<=m; ++i){
		stat[i]=(_pair){1,n};
	}
	for(int i=1; i<=q; ++i){
		opt[i]=nxi();
		if(opt[i]==2){
			char c;
			while((c=getchar())>'z'||c<'a');
			str[++n]=c;
		}
		else optarg[i]=nxi();
	}
	S::build(str,old_n,n);
	for(int i=1; i<=q; ++i){
		if(opt[i]==1){
			const int x=optarg[i];
			if(inq[x]){
				stat[x]=merge(stat[x],lstpos[x],curpos,plen[x]);
				inq[x]=0;
				vis[x]=1;
			}
			else{
				inq[x]=1;
				lstpos[x]=curpos+1;
			}
		}
		if(opt[i]==2){
			++curpos;
		}
		if(opt[i]==3){
			const int x=optarg[i];
			if(!vis[x]){
				if(lstpos[x]&&lstpos[x]<=curpos) printf("%d\n",ask(x));
				else puts("0");
			}
			else if(!inq[x]){
				printf("%d\n",S::sum[stat[x].y]-S::sum[stat[x].x+1]);
			}
			else printf("%d\n",ask(x));
		}
	}
	return 0;
}
