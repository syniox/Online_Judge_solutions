#include <iostream>
#include <cstdio>
#include <cstring>
const int N=2005;
int n,m,mp[N][N],nx[30][N];

template <class T> inline T san(T x){
	while(x>n) x-=n;
	return x;
}

inline char get_c(){
	static char *h,*t,buf[50000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}


inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline int get_nx(const int org_x,const int to){
	int x=san(org_x);
	int pt=x,hx=mp[x][to];
	int x_up=san(x+n-1);
	if(mp[x_up][to]>hx) pt=x_up,hx=mp[x_up][to];
	int x_dn=san(x+1);
	if(mp[x_dn][to]>hx) pt=x_dn;
	return pt+org_x-x;
}

inline int get_to_1(int x,int y){
	if(y==1) return x;
	for(; y<m; ++y) x=get_nx(x,y+1);
	return get_nx(x,1);
}

inline void make_nx(){
	for(int i=1; i<30; ++i){
		for(int j=1; j<=n; ++j){
			nx[i][j]=nx[i-1][nx[i-1][j]];
		}
	}
}

inline void backport(const int x,int y,const int val){
	int l=x+n,r=x+n;
	for(; y>1&&l<=r&&r-l<n; --y){
		if(get_nx(l,y)>r) return;
		if(get_nx(l,y)<l) ++l;
		else if(get_nx(l-1,y)>=l) --l;
		if(get_nx(r,y)<l) return;
		if(get_nx(r,y)>r) --r;
		else if(get_nx(r+1,y)<=r) ++r;
	}
	for(int i=l; i<=r; ++i){
		nx[0][san(i)]=val;
	}
}

inline void change(){
	int x=nxi(),y=nxi(),val=nxi();
	int cur_y=y==1?m:y-1;
	int bef[3],fx[3]={san(x+n-1),x,san(x+1)};
	for(int i=0; i<3; ++i){
		bef[i]=get_to_1(get_nx(fx[i],y),y);
	}
	mp[x][y]=val;
	for(int i=0; i<3; ++i){
		int tp=get_to_1(get_nx(fx[i],y),y);
		if(tp!=bef[i]){
			backport(fx[i],cur_y,tp);
		}
	}
	make_nx();
}

inline void move(int &cur_x,int &cur_y){
	int step=nxi();
	for(; step&&cur_y<m; --step,++cur_y){
		cur_x=get_nx(cur_x,cur_y+1);
	}
	if(!step--) return; 
	cur_y=1,cur_x=get_nx(cur_x,1);
	for(int tp=step/m,i=29; i>=0; --i){
		if(tp>>i&1) cur_x=nx[i][cur_x];
	}
	for(step%=m; step; --step,++cur_y){
		cur_x=get_nx(cur_x,cur_y+1);
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			mp[i][j]=nxi();
		}
	}
	for(int i=1; i<=n; ++i){
		nx[0][i]=get_to_1(get_nx(i,2),2);
	}
	make_nx();
	for(int cur_x=1,cur_y=1,q=nxi(); q; --q){
		char c;
		while((c=get_c())>'z'||c<'a');
		if(c=='c') change();
		else{
			move(cur_x,cur_y);
			printf("%d %d\n",cur_x,cur_y);
		}
	}
	return 0;
}
