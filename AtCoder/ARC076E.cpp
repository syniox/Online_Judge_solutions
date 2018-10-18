#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1e5+2;
int n,m,q,cnt;
struct pnt{
	int x,y,id;
	//right -> down -> left -> up
}pt[N<<1];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_level(const pnt &a){
	if(a.y==m) return 1;
	if(a.x==n) return 2;
	if(a.y==0) return 3;
	return 4;
}

bool cp_pnt(const pnt &a,const pnt &b){
	const int t1=get_level(a),t2=get_level(b);
	if(t1!=t2) return t1<t2;
	if(a.y==b.y) return (a.y==m)^(a.x>b.x);
	return (a.x==n)^(a.y<b.y);
}

inline bool on_edge(const int x,const int y){
	return x==0||x==n||y==0||y==m;
}

inline bool jdg(){
	static int stk[N<<1];
	static bool vis[N<<1];
	int top=0;
	for(int i=1;i<=cnt;++i){
		const int cur=pt[i].id;
		if(vis[cur]){
			if(stk[top]!=cur) return 0;
			--top;
		}
		else{
			stk[++top]=cur;
			vis[cur]=1;
		}
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1;i<=q;++i){
		const int x1=nxi(),y1=nxi(),x2=nxi(),y2=nxi();
		if(on_edge(x1,y1)&&on_edge(x2,y2)){
			pt[++cnt]=(pnt){x1,y1,i};
			pt[++cnt]=(pnt){x2,y2,i};
		}
	}
	std::sort(pt+1,pt+cnt+1,cp_pnt);
//	for(int i=1;i<=cnt;++i){
//		printf("%d %d %d\n",pt[i].x,pt[i].y,pt[i].id);
//	}
	puts(jdg()?"YES":"NO");
	return 0;
}
