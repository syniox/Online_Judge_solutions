#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,q,lrq[N],*rans[N];
char str[N],*rq[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

namespace S{
	int cnt;
	struct node{
		int lk,c[26],cnt;
	}tr[2505];

	void add(const char *s,const int len){
		int p=0;
		for(int i=0; i<len; ++i){
			int &c=tr[p].c[s[i]-'a'];
			p=c?c:c=++cnt;
		}
		++tr[p].cnt;
	}
	void bfs(){
		static int que[2505];
		int hd=0,tl=1;
		while(hd!=tl){
			int x=que[hd++];
			tr[x].cnt+=tr[tr[x].lk].cnt;
			for(int i=0; i<26; ++i){
				const int y=tr[x].c[i],lk=tr[x].lk;
				if(!y) tr[x].c[i]=tr[lk].c[i];
				else{
					que[tl++]=y;
					if(x) tr[y].lk=tr[lk].c[i];//lk是否能为自己？
				}
			}
		}
	}
	int ask(char *str,const int len){
		int p=0,ans=0;
		for(int i=0; i<len; ++i){
			ans+=tr[p=tr[p].c[str[i]-'a']].cnt;
		}
		return ans;
	}
}

int addstr(char *s){
	using S::tr;
	static int cnr;
	int len=strlen(s);
	lrq[++cnr]=len;
	rq[cnr]=new char[len];
	memcpy(rq[cnr],s,len*sizeof(s[0]));
	rans[cnr]=new int[len];
	int p=0;
	for(int i=0; i<50; ++i){
		p=tr[p].c[s[i%len]-'a'];
	}
	for(int i=0; i<len; ++i){
		p=tr[p].c[s[(i+50)%len]-'a'];
		rans[cnr][(i+50)%len]=tr[p].cnt;
	}
	for(int i=1; i<len; ++i){
		rans[cnr][i]+=rans[cnr][i-1];
	}
	return cnr;
}

namespace T{
	int x,y,ret_id,qs_cnt;
	struct node{
		int s,ret,offs;
		bool upd;
		//offs: 区间第0位在rq中的下标
		//s默认前方都在而不是自循环的ans
		void set(const int id,const int offs,int len){
			int rl=lrq[id];
			ret=id,this->offs=offs;
			s=(offs?rans[id][offs-1]:0);
			upd=1;
			if(rl-offs>len){
				s=rans[id][offs+len-1]-s;
				return;
			}
			len-=rl-offs;
			s=rans[id][rl-1]-s;
			s+=(len/rl)*rans[id][rl-1];
			len%=rl;
			s+=len?rans[id][len-1]:0;
		}
	}tr[N<<1];

	int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)].s=tr[idx(l,mid)].s+tr[idx(mid+1,r)].s;
	}
	void psh(const int l,const int r){
		bool &u=tr[idx(l,r)].upd;
		if(!u) return;
		const int mid=(l+r)>>1;
		node *k=tr+idx(l,r);
		tr[idx(l,mid)].set(k->ret,k->offs,mid-l+1);
		tr[idx(mid+1,r)].set(k->ret,(k->offs+mid-l+1)%lrq[k->ret],r-mid);
		u=0;
	}

	int rnw_t(const int l,const int r,int t){
		if(l==r){
			int k=idx(l,r),c=rq[tr[k].ret][tr[k].offs]-'a';
			tr[k].s=S::tr[t=S::tr[t].c[c]].cnt;
			return t;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) t=rnw_t(l,mid,t);
		if(y>mid) t=rnw_t(mid+1,r,t);
		upd(l,r);
		return t;
	}
	int qst_t(const int l,const int r,int t){
		if(l==r){
			node *k=tr+idx(l,r);
			t=S::tr[t].c[rq[k->ret][k->offs]-'a'];
			qs_cnt+=S::tr[t].cnt;
			return t;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) t=qst_t(l,mid,t);
		if(y>mid) t=qst_t(mid+1,r,t);
		return t;
	}
	void set_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].set(ret_id,(l-x)%lrq[ret_id],r-l+1);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) set_t(l,mid);
		if(y>mid) set_t(mid+1,r);
		upd(l,r);
	}
	int qsum_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].s;
		psh(l,r);
		int ans=0,mid=(l+r)>>1;
		if(x<=mid) ans+=qsum_t(l,mid);
		if(y>mid) ans+=qsum_t(mid+1,r);
		return ans;
	}

	void rnw(const int l,const int r,const int t){
		T::x=l,T::y=r;
		rnw_t(0,n-1,t);
	}
	int qst(const int l,const int r,const int t){
		if(l>r) return 0;
		qs_cnt=0,T::x=l,T::y=r;
		return qst_t(0,n-1,t);
	}
	void set(const int l,const int r,const int ret_id){
		T::x=l,T::y=r,T::ret_id=ret_id;
		set_t(0,n-1);
		rnw(l,std::min(l+50,r),qst(std::max(0,l-50),l-1,0));
		rnw(r+1,std::min(n,r+50),qst(std::max(0,r-50),r,0));
	}
	int qsum(const int l,const int r){
		if(l>r) return 0;
		T::x=l,T::y=r;
		return qsum_t(0,n-1);
	}
}

int qsum(const int l,const int r){
	T::qst(l,std::min(r,l+50),0);
	return T::qsum(l+51,r)+T::qs_cnt;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		static char s[55];
		scanf("%s",s);
		int len=strlen(s);
		S::add(s,len);
	}
	S::bfs();
	scanf("%s",str);
	n=strlen(str);
	T::set(0,n-1,addstr(str));
	while(q--){
		if(nxi()==1){
			int l=nxi()-1,r=nxi()-1;
			scanf("%s",str);
			T::set(l,r,addstr(str));
		}else{
			int l=nxi()-1,r=nxi()-1;
			printf("%d\n",qsum(l,r));
		}
	}
	return 0;
}
