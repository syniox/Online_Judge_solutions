#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long lint;
using namespace std;
const int N=1e5+5,M=1e6+5;
int n,m,cfa[M];
struct pep{
    int fr,to,id;
    const bool direct() const;
};
struct op_s{
    bool type;
    int x,y;
};
vector<pep> pel[M],per[M];
//pel: 从左边过来 per: 从右边过来
 
namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
    template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
    template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
    template <class T> inline T cabs(const T &x){return x<0?-x:x;}
    static struct{
        template <class T> operator T(){
            T x=0;
            char c;
            while(((c=getchar())>'9'||c<'0')&&c!='-');
            const bool f=(c=='-')&&(c=getchar());
            while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
            return f?-x:x;
        }
    }ni;
}
using namespace utils;
 
const bool pep::direct() const{
    return fr<to;
}
 
lint cans(){
    lint ans=0;
    for(int scc=0,i=1; i<m; ++i){
        scc+=cfa[i];
        ans+=cabs(scc);
    }
    return ans;
}
 
queue<pep> que;
vector<op_s> frt,bck;
 
bool getpep(const int i,pep &p){
    for(; !que.empty()&&(p=que.front(),max(p.fr,p.to)<=i); que.pop()){
        bck.push_back((op_s){0,p.id,p.to});
    }
    return !que.empty();
}
 
void oput_ans(){
    frt.clear(),bck.clear();
    for(int i=1; i<=m; ++i){
        pep f;
        for(vector<pep>::iterator it=pel[i].begin(); it!=pel[i].end(); ++it){
            if(!getpep(i,f)||f.direct()==it->direct()){
                que.push(*it);
            }else{
                que.pop();
                assert(f.fr!=f.to);
                bck.push_back((op_s){0,f.id,f.to});
                if(f.fr<=it->to){//交错
                    frt.push_back((op_s){0,f.id,it->fr});
                    frt.push_back((op_s){1,it->id,f.id});
                    frt.push_back((op_s){0,it->id,f.fr});
                    if(f.fr!=it->to){
                        pel[f.fr].push_back((pep){f.fr,it->to,it->id});
                    }
                }else{
                    bck.push_back((op_s){0,it->id,it->to});
                    bck.push_back((op_s){1,it->id,f.id});
                    bck.push_back((op_s){0,f.id,it->fr});
                    per[it->to].push_back((pep){f.fr,it->to,f.id});
                }
            }
        }
        for(vector<pep>::iterator it=per[i].begin(); it!=per[i].end(); ++it){
            if(!getpep(i,f)||f.direct()==it->direct()){
                que.push(*it);
            }else{
                que.pop();
                if(it->to!=f.fr){
                    frt.push_back((op_s){0,f.id,it->to});
                }
                if(f.to<=it->fr){//交错
                    bck.push_back((op_s){0,f.id,f.to});
                    bck.push_back((op_s){1,f.id,it->id});
                    bck.push_back((op_s){0,it->id,it->to});
                    if(f.to!=it->fr){
                        per[f.to].push_back((pep){it->fr,f.to,it->id});
                    }
                }else{
                    frt.push_back((op_s){0,it->id,it->to});
                    frt.push_back((op_s){1,it->id,f.id});
                    frt.push_back((op_s){0,f.id,it->fr});
                    pel[it->fr].push_back((pep){it->fr,f.to,f.id});
                }
            }
        }
    }
    pep fff;
    assert(!getpep(m,fff));
    printf("%d\n",int(frt.size()+bck.size()));
    for(vector<op_s>::iterator it=frt.begin(); it!=frt.end(); ++it){
        printf("%d %d %d\n",it->type,it->x,it->y);
    }
    for(vector<op_s>::reverse_iterator it=bck.rbegin(); it!=bck.rend(); ++it){
        printf("%d %d %d\n",it->type,it->x,it->y);
    }
}
 
int main(){
    for(int T=ni; T--; ){
        n=ni,m=ni;
        memset(cfa+1,0,m*sizeof(cfa[0]));
        for(int i=1; i<=m; ++i){
            pel[i].clear();
            per[i].clear();
        }
        for(int i=1; i<=n; ++i){
            pep tmp=(pep){ni,ni,i};
            if(tmp.fr<tmp.to){
                pel[tmp.fr].push_back(tmp);
            }else{
                per[tmp.to].push_back(tmp);
            }
            ++cfa[tmp.fr];
            --cfa[tmp.to];
        }
        printf("%lld ",cans());
        oput_ans();
    }
    return 0;
}
