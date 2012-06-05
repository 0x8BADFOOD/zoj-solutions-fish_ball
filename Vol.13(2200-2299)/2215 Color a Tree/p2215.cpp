//     ��������Ҫ�� Sigma( i * Ci ) (i = 1 .. n) ��ֵ��С
// { Ci } �ǽڵ���õ�һ�����У�ͬʱҪ���㸸�ڵ�Ҫ�������ӽڵ�ǰ�档

//     ���û�и��ڵ�������ӽڵ�ǰ��������ƣ���ô�𰸺�����:
// ��{ Ci }���������е�ʱ��Sigma ��ֵ����С�ġ�

//     ����������Ƶ�ʱ�����Ҳ�����Ƶġ�����ĳһ�����н⣬
// ����{ Ci }��ĳһ�����С��ҵ����е����ֵ������Ϊ Ck��
// ����һ�����ڵ���� Cp����Ȼ Cp Ҫ������ Ck ֮ǰ������һ����
// Cp ��Ӧ�ó�����Ck��ǰһ��λ�á�ֻ���������п���Sigma��ֵ��С��
// ��Ȼ���ǿ��Խ�Ckλ����ǰ�ƶ����õ�һ����С��Sigmaֵ��
// ���Ҳ��ƻ������Լ������ȻCp�ͳ�����Ck��ǰһ��λ�ã�
// ��ô������ʵ��������һ��ģ�������Ϊһ������������
// ��������Ĺ�ģ����n��С��n-1��Ȼ���ظ���һ���̣�ֱ�����е�λ�ö�ȷ��������
// �������Ǿ��ҵ������Ž⡣

// �ϲ���Ľڵ������ǵ�ƽ��ֵ���� 

#include <queue>
#include <iostream>
#include <vector>
using namespace std;

int     N,  R,  x,  y;
int     C[1001], A[1001], D[1001]; 
double  B[1001];
int     tot,    cnt;

priority_queue<pair<double, int> >  hp;

vector<int> V[1001];

void DFS( int v ) {
    A[v] = 1;
    D[v] = C[v];
    for( int i = 0; i < V[v].size(); ++i ) {
        DFS( V[v][i] );
        A[v] += A[V[v][i]];
        D[v] += D[V[v][i]];
    }
    B[v] = double( D[v] ) / double( A[v] );
}

int main() {
    
    while( cin >> N >> R && N ) {
    
        for( int i = 1; i <= N; ++i ) {
            cin >> C[i];
            V[i].clear();
        }

        for( int i = 1; i < N; ++i ) {
            cin >> x >> y;
            V[x].push_back( y );
        }
        
        DFS( R );

        while( !hp.empty() ) hp.pop();
        tot = cnt = 0;
        
        tot += C[R] * ++cnt;
        while( 1 ) {
            for( int i = 0; i < V[R].size(); ++i )
                hp.push( make_pair( B[V[R][i]], V[R][i] ) );
            if( hp.empty() ) break;
            R = hp.top().second;
            hp.pop();
            tot += C[R] * ++cnt;
        }
        
        cout << tot << endl;
    
    }
    
}
