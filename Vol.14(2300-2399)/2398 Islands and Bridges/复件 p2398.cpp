// �е�ƫ�ѵĹ��ܶ�·��������... TLE

#include <iostream>
#include <vector>
using namespace std;

// case ���������������� 
int     T,  N,  M;

// ����Ȩֵ 
int     V[14];

// ����������ǰȨֵ�����Ȩֵ 
int     cnt, wgt, mx;

// �ڴ˲���˫��ͼ��ʾ 
// �ڽӱ�����ͼ���� 
vector<int> G1[14];
// �ڽӾ������ڱ߲�ѯ 
bool        G2[14][14];

// �ѷ��ʱ�� 
bool    B[14];
vector<int> trace; 
 

void Hamilton( int v, int s ) {
    
    // ���������ܶ�·�� 
    if( s == 1 ) {
        // ��ȡ��·����Ȩֵ 
        for( int i = wgt = 0; i < N; ++i ) {
//cout << trace[i] << ' '; 
            // ��һ�����Ȩ 
            wgt += V[trace[i]];
            // �ڶ����Ȩ 
            if( i + 1 < N )
                wgt += ( V[trace[i]] * V[trace[i+1]] ); 
            // �������·Ȩ
            if( i + 2 < N &&
                G2[trace[i]][trace[i+2]] ) {
                wgt += V[trace[i]] * 
                       V[trace[i+1]] *
                       V[trace[i+2]];
            }
        }
//cout << "  " << wgt << endl; 
        if( wgt == mx ) ++cnt;
        else if( wgt > mx ) {
            mx = wgt;
            cnt = 1; 
        }
        return; 
    }
    
    // ����(����) 
    for( int i = 0; i < G1[v].size(); ++i ) {
        if( !B[G1[v][i]] ) {
            B[G1[v][i]] = true;
            trace.push_back( G1[v][i] );
            Hamilton( G1[v][i], s - 1 );
            trace.pop_back();
            B[G1[v][i]] = false;
        }
    }
    
} 


int main() {
    
    for( cin >> T; T--; ) {
        
        // ��ͼ 
        cin >> N >> M;
        
        for( int i = 1; i <= N; ++i ) {
            cin >> V[i];
            G1[i].clear();
            memset( G2[i], 0, sizeof( G2[i] ) ); 
        }
        
        if( N == 1 ) { cout << V[1] << 1 << endl; continue; }
        
        for( int i = 1; i <= M; ++i ) {
            int x,  y;
            cin >> x >> y;
            G1[x].push_back( y );
            G1[y].push_back( x );
            G2[x][y] = G2[y][x] = true;
        }
        
        // ��ʼ���ܶ������������ж���Ϊ�����һ�� 
        cnt = mx = 0;
        for( int pos = 1; pos <= N; ++pos ) { 
            
            // ��ʼ��
            trace.clear(); 
            memset( B, 0, sizeof( B ) );
        
            // DFS
            trace.push_back( pos ); 
            B[pos] = true; 
            Hamilton( pos, N );
            
        }
        
        // �����ע��ͬһ�����ܶ�·���ᱻ���������� 
        cout << mx << ' ' << cnt / 2 << endl; 
         
    }
    
}
 
