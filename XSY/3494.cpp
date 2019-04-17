#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
const int N=1e5+5;
int n,q,chn_cnt,idx[N],ans[N];//idx下标在sa上
char str[N];
std::set <int> stat[N];//下标按照sa顺序，内部存储原字符串下标
struct _data{
	int x,y;
};
struct _qry{
	int id,x,y;
	friend bool operator < (const _qry &a,const _qry &b){
		return a.x<b.x;
	}
}qry[N];
std::vector <_data> mbuk[N];

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace U{
	int fa[N];
	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

namespace S{
	int sa[N],rnk[N],hgt[N];

	inline int get_rk(const int x){
		return x>n?0:rnk[x];
	}

	inline int cmp_hgt(const int a,const int b){
		return hgt[a]<hgt[b];
	}

	void qsort(int *sa,int *rnk,int *idx){
		static int buk[N];
		memset(buk+1,0,std::max(n,26)*sizeof(int));
		for(int i=1; i<=n; ++i){
			++buk[rnk[idx[i]]];
		}
		for(int i=1; i<=n; ++i){
			buk[i]+=buk[i-1];
		}
		for(int i=n; i>=1; --i){
			sa[buk[rnk[idx[i]]]--]=idx[i];
		}
	}

	void build(char *str,int n){
		static int tmp[N];
		for(int i=1; i<=n; ++i){
			tmp[i]=i;
			rnk[i]=str[i]-'a'+1;
		}
		qsort(sa,rnk,tmp);
		for(int w=1,cnt_rk=0; w<n&&cnt_rk<n; w<<=1){
			for(int i=1; i<=w; ++i){
				tmp[i]=n-w+i;
			}
			for(int i=1,j=w; i<=n; ++i){
				if(sa[i]>w) tmp[++j]=sa[i]-w;
			}
			qsort(sa,rnk,tmp);
			cnt_rk=0;
			for(int i=1; i<=n; ++i){
				if(rnk[sa[i-1]]!=rnk[sa[i]]||get_rk(sa[i-1]+w)!=get_rk(sa[i]+w)){
					++cnt_rk;
				}
				tmp[sa[i]]=cnt_rk;
			}
			memcpy(rnk+1,tmp+1,n*sizeof(int));
		}
		int pre=0;
		for(int i=1; i<=n; ++i){
			pre=std::max(pre-1,0);
			if(rnk[i]==1) continue;
			for(int x=sa[rnk[i]-1]+pre,y=i+pre; x<=n&&y<=n&&str[x]==str[y]; ){
				++x,++y,++pre;
			}
			hgt[rnk[i]]=pre;
		}
	}
}

namespace B{
	int tr[N];
	inline void apl(int x,const int v){
		if(tr[x]>=v) return;
		for(; x<=n; x+=x&-x) apx(tr[x],v);
	}
	inline int ask(int x){
		assert(x>=0);
		int ans=0;
		for(; x; x-=x&-x) apx(ans,tr[x]);
		return ans;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	scanf("%s",str+1);
	S::build(str,n);
	for(int i=1; i<=n; ++i){
		idx[i]=i;
	}
	std::sort(idx+1,idx+n+1,S::cmp_hgt);
	for(int i=1; i<=n; ++i){
		stat[i].insert(S::sa[i]);
	}
	for(int i=n; i; --i){
		int x=idx[i],len=S::hgt[x];
		if(len==0) break;
		assert(x>1);
		int y=U::find_rt(x-1);
		U::fa[x]=y;
		if(stat[x].size()>stat[y].size()){
			std::swap(x,y);
		}
		for(std::set <int> ::iterator it=stat[x].begin(); it!=stat[x].end(); ++it){
			std::set <int> ::iterator pos=stat[y].lower_bound(*it);
			if(pos!=stat[y].end()){
				mbuk[*it].push_back((_data){*pos,len});
			}
			if(pos!=stat[y].begin()){
				--pos;
				mbuk[*pos].push_back((_data){*it,len});
				++pos;
			}
			stat[y].insert(pos,*it);
		}
		if(x<y) std::swap(stat[x],stat[y]);
		stat[std::max(x,y)].clear();
	}
	for(int i=1; i<=q; ++i){
		qry[i].id=i;
		qry[i].x=nxi(),qry[i].y=nxi();
	}
	std::sort(qry+1,qry+q+1);
	for(int i=n,j=q; i; --i){
		for(std::vector <_data> ::iterator it=mbuk[i].begin(); it!=mbuk[i].end(); ++it){
			B::apl(it->x,it->y);
		}
		for(; qry[j].x==i; --j){
			const int x=qry[j].x,y=qry[j].y;
			int l=0,r=y-x,mid;
			while(l!=r){
				mid=(l+r+1)>>1;
				if(B::ask(y-mid+1)>=mid) l=mid;
				else r=mid-1;
			}
			ans[qry[j].id]=l;
		}
	}
	for(int i=1; i<=q; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
