#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=5e5+5;
const int mx=N<<1;
int n,m,pre_qry[N],ans[N];

class pair{
	public:
		int x,y;
};

class _Qry{
	public:
		int id,x,y;
}chn[N],qry[N];

template <class T> inline bool cmp_x(const T &a,const T &b){
	return a.x<b.x;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}
template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace B{
	int tick,tag[N<<1|1],tr[N<<1|1];

	inline void clear(){
		++tick;
	}
	inline void upd(const int k){
		if(tag[k]<tick) tag[k]=tick,tr[k]=0;
	}
	inline void mod(int x,const int v){
		for(; x<mx; x+=x&-x) apx(tr[x],v);
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) apx(ans,tr[x]);
		return ans;
	}
}

inline void upd_ans(pair *src,int slen,int l,int r){
	static _Qry buk[N];
	int tlen=r-l+1;
	memcpy(buk,qry+l,tlen*sizeof(_Qry));
	std::sort(buk,buk+tlen,cmp_x <_Qry>);
	std::sort(src,src+slen,cmp_x <pair>);
	//right_up
	B::clear();
	for(int j=slen-1,i=tlen-1; ~i; --i){
		for(; j>=0&&src[j].x>=buk[i].x; --j){
			B::mod(mx-src[j].y,-src[j].x-src[j].y);
		}
		apn(ans[buk[i].id],-B::ask(mx-buk[i].y)-buk[i].x-buk[i].y);
	}
	//left_up
	B::clear();
	for(int j=slen-1,i=tlen-1; ~i; --i){
		for(; j>=0&&src[j].x>=buk[i].x; --j){
			B::mod(src[j].y,-src[j].x+src[j].y);
		}
		apn(ans[buk[i].id],-B::ask(buk[i].y)-buk[i].x+buk[i].y);
	}
	//left_down
	for(int i=0,j=0; i<tlen; ++i){
		for(; j<slen&&src[j].x<=buk[i].x; ++j){
			B::mod(src[j].y,src[j].x+src[j].y);
		}
		apn(ans[buk[i].id],-B::ask(buk[i].y)+buk[i].x+buk[i].y);
	}
	//right_down
	for(int i=0,j=0; i<tlen; ++i){
		for(; j<slen&&src[j].x<=buk[i].x; ++j){
			B::mod(mx-src[j].y,src[j].x-src[j].y);
		}
		apn(ans[buk[i].id],-B::ask(mx-buk[i].y)+buk[i].x-buk[i].y);
	}
}

void cdq(const int l,const int r){
	static pair buk[N];
	const int mid=(l+r)>>1;
	if(l<mid) cdq(l,mid);
	if(mid+1<r) cdq(mid+1,r);
	int pt=0;
	for(int i=l; i<=mid; ++i){
		if(!chn[i].id) buk[pt++]=(pair){chn[i].x,chn[i].y};
	}
	upd_ans(buk,pt,pre_qry[l-1]+1,pre_qry[r]);
}

int main(){
	static pair org[N];
	memset(ans,10,sizeof(ans));
	m=nxi(),n=nxi();
	for(int i=0; i<m; ++i){
		const int x=nxi()+1,y=nxi()+1;
		org[i]=(pair){x,y};
	}
	for(int i=1; i<=n; ++i){
		const int op=nxi(),x=nxi()+1,y=nxi()+1;
		pre_qry[i]=pre_qry[i-1]+(op==2);
		if(op==1){
			chn[i]=(_Qry){0,x,y};
		}
		else{
			chn[i]=qry[pre_qry[i]]=(_Qry){pre_qry[i],x,y};
		}
	}
	upd_ans(org,m,1,pre_qry[n]);
	fprintf(stderr,"First ans: ");
	for(int i=1; i<=pre_qry[n]; ++i){
		fprintf(stderr,"%d ",ans[i]);
	}
	puts("");
	cdq(1,n);
	for(int i=1; i<=pre_qry[n]; ++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
