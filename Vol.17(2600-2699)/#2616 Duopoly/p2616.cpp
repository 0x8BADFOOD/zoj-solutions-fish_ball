// 3055295 2008-08-29 19:40:32 Accepted 2616 C++ 00:00.62 6368K ���͵����� 

// ʵ������һ�����ֵ����⣬����ת��Ϊ����С�� 

// ���� A ���� N �����꣬B ���� M ������

// ����������£����Ӧ�������о��궼���յ����ܼ�ֵ�ﵽ S

// Ȼ������ N �� M ����������ĳЩ���ܹ���

// ���Ҫ���ĳЩ�ߣ��Է������Լ��

// ����һ��ͼ��S -> N ����һ���ߣ�����Ϊ�ø�����ļ۸�

// M -> T ����һ���ߣ�����Ϊ�ø�����ļ۸�

// ���⣬���� M��N ֮�䣬���ĳ��������֮�䲻�ܹ���

// ������֮������һ�����������ı�

// Ȼ�����ͼ��С�Ҳ����������������������ʧ

// ������� S - MaxFlow

// ����������⣬�����С���Ȼ��������м����Щ��

// Ҳ���ǲ���ͬʱȡì�ܵ�˫��

// ���⹹ͼ����ҪһЩ�ɾ� 

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int SZ = 6002;
const int INF = 1 << 28;

// �߽ṹ��

struct Edge {
    // u,v Ϊ�����ߵ������˵�
    // cuv �� cvu Ϊ�������������������
    // f Ϊ�����ߵĵ�ǰ����
    int u, v, cuv, cvu, f;

    Edge() {
    }

    Edge(int u, int v, int cuv, int cvu) :
            u(u), v(v), cuv(cuv), cvu(cvu), f(0) {
    }

    int other(int p)const {
        return p == u ? v : u;
    }

    int cap(int p)const {
        return p == u ? cuv - f : cvu + f;
    }

    void addFlow(int p, int flow) {
        f += (p == u ? flow : -flow);
    }
};


// �߶ȶ����б�

class NodeList {
    // lvl Ϊ��ǰ�б���߶���ĸ߶�
    // nxt Ϊĳ������ĺ��(һ������ֻ�ܴ�����һ���߶���)
    // idx Ϊĳ���߶ȵĵ�һ��������
    // v Ϊ����߶ȱ�Ķ�����Ŀ
    int lvl, nxt[SZ], idx[2 * SZ], v;
public:

    // ��ն����б�

    void clear(int cv) {
        v = cv;
        lvl = -1;
        memset(idx, -1, sizeof (idx));
    }

    // ��鶥���б��Ƿ�Ϊ��

    bool empty()const {
        return lvl < 0;
    }

    // �ڸ߶� h �����붥�� n

    void insert(int n, int h) {
        nxt[n] = idx[h];
        idx[h] = n;
        lvl = max(lvl, h);
    }

    // �Ƴ���ߵĶ��㣬�������ı��

    int remove() {
        int r = idx[lvl];
        idx[lvl] = nxt[idx[lvl]];
        while (lvl >= 0 && idx[lvl] == -1) lvl--;
        return r;
    }
};

// ������

class MaxFlow {public:
    // edge Ϊ���бߵ�ʵ�ʶ�λ
    // net Ϊͼ���ڽӱ�ָ�� edge �еı�
    // v Ϊ��������s,t ΪԴ�ͻ�Ķ�����
    // lst Ϊ�߶ȶ����б�
    // h Ϊ�����Ӧ�ĸ߶�
    // hn Ϊ���߶Ⱦ��еĶ�����
    // e Ϊ���������
    // cur Ϊ������
    vector<Edge> edge;
    vector<Edge*> net[SZ];
    int v, s, t;
    NodeList lst;
    int h[SZ], hn[2 * SZ], e[SZ], cur[SZ];

    // �������е� edge ����ͼ�ڽӱ�

    void initNet() {
        for (int i = 0; i < v; ++i)
            net[i].clear();
        for (int i = edge.size() - 1; i >= 0; --i) {
            net[edge[i].u].push_back(&edge[i]);
            net[edge[i].v].push_back(&edge[i]);
        }
    }

    // ��ʼ��������ĸ߶�

    void initHeight() {
        memset(h, 0, sizeof (h));
        memset(hn, 0, sizeof (hn));
        memset(e, 0, sizeof (e));
        e[s] = INF;
        for (int i = 0; i < v; ++i) h[i] = v;
        queue<int>Q;
        Q.push(t);
        h[t] = 0;
        while (!Q.empty()) {
            int p = Q.front();
            Q.pop();
            for (int i = net[p].size() - 1; i >= 0; --i) {
                int u = net[p][i]->other(p), ec = net[p][i]->cap(u);
                if (ec != 0 && h[u] == v && u != s) {
                    h[u] = h[p] + 1;
                    Q.push(u);
                }
            }
        }
        for (int i = 0; i < v; ++i)++hn[h[i]];
    }

    // ִ�м�϶�Ż�

    void gapHeuristic(int k) {
        if (hn[k] != 0 || k > v + 1)return;
        for (int i = 0; i < v; ++i) {
            if (h[i] > k && h[i] <= v && i != s) {
                --hn[h[i]];
                ++hn[v + 1];
                h[i] = v + 1;
            }
        }
    }

    // ��ĳ������ĵ�ǰ��ִ��ѹ�����

    void push(int u) {
        Edge*te = net[u][cur[u]];
        int ex = min(te->cap(u), e[u]), p = te->other(u);
        if (e[p] == 0 && p != t)lst.insert(p, h[p]);
        te->addFlow(u, ex);
        e[u] -= ex;
        e[p] += ex;
    }

    // �ر��һ������

    void relabel(int u) {
        int mh = 2 * v, oh = h[u];
        for (int i = net[u].size() - 1; i >= 0; --i) {
            int p = net[u][i]->other(u);
            if (net[u][i]->cap(u) != 0)
                mh = min(mh, h[p] + 1);
        }
        hn[h[u]]--;
        hn[mh]++;
        h[u] = mh;
        cur[u] = net[u].size() - 1;
        gapHeuristic(oh);
    }

    // ��ʼ��������

    void initFlow() {
        initNet();
        initHeight();
        for (int i = 0; i < v; ++i)
            cur[i] = net[i].size() - 1;
        lst.clear(v);
        for (; cur[s] >= 0; --cur[s])push(s);
    }

    // �ų�һ������

    void discharge(int u) {
        while (e[u] > 0) {
            if (cur[u] < 0)relabel(u);
            else if (net[u][cur[u]]->cap(u) > 0 &&
                    h[u] == h[net[u][cur[u]]->other(u)] + 1)
                push(u);
            else --cur[u];
        }
    }

public:

    // ���ر߼��ϵ�����

    vector<Edge>& edges() {
        return edge;
    }

    // �������

    int maxFlow(int ss, int tt) {
        s == ss;
        t = tt;
        initFlow();
        while (!lst.empty()) {
            int u = lst.remove();
            discharge(u);
        }
        return e[t];
    }
};

#include <iostream>
#include <set>
using namespace std;

MaxFlow     mf;

int     T,  N,  M,  S,  X;

vector<int> H[300001];

set<int>    P;
set<int>::iterator  it;

int main() {

    scanf( "%d", &T );

    for( int t = 0; t < T; ++t ) {

        if( t ) puts( "" );

        for( int i = 1; i < 300001; ++i )
            H[i].clear();
            
        S = 0;
////////////////////
        mf.edges().clear();
        
        scanf( "%d", &N );
        for( int i = 1; i <= N; ++i ) {
            scanf( "%d", &X );
            S += X;
////////////////////
            mf.edges().push_back( Edge( 0, i, X, 0 ) );
            while( getchar() != '\n' ) {
                scanf( "%d", &X );
                H[X].push_back( i );
            }
        }
        
        scanf( "%d", &M );
        for( int i = N+1; i <= N+M; ++i ) {
            scanf( "%d", &X );
            S += X;
            mf.edges().push_back( Edge( i, N+M+1, X, 0 ) );
            P.clear();
            while( getchar() != '\n' ) {
                scanf( "%d", &X );
                for( int j = 0; j < H[X].size(); ++j )
                    P.insert( H[X][j] );
            }
            for( it = P.begin(); it != P.end(); ++it )
                mf.edges().push_back( Edge( *it, i, INF, 0 ) );
        }
        
        printf( "Case %d:\n", t + 1 );
        mf.v = M+N+2;
        printf( "%d\n", S - mf.maxFlow( 0, N+M+1 ) );

    }

}
