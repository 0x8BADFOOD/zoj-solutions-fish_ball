// �е�ƫ�ѵĹ��ܶ�·��������... TLE

#include <cstdio>
#include <cstring>

////////////////////////////////////////////////////
//                 ���鼯ģ�� v1.1                //
////////////////////////////////////////////////////
//                                                //
//  1. SZ:      ���鼯���Ԫ������(ģ�����);     //
//  2. init:    ��ʼ�� N ��Ԫ�صĲ��鼯;          //
//  3. check:   �������Ԫ���Ƿ񹲼������ϲ�֮;   //
//  4. getSets: ���ز��鼯���Ӽ�����;             //
//  5. single:  ���һ�����Ƿ����;               // 
//                                                //
////////////////////////////////////////////////////
//            2008 CopyRight(c) by elf            //
////////////////////////////////////////////////////

template<int SZ> class Union {
    int elem,   subSets;
    int* U;
    bool* B; 
public:
    Union( int N = 0 ) : elem( N ), subSets( N )
        { U = new int[SZ+1]; B = new bool[SZ+1]; }
    void init( const int& );
    bool check( int, int ) const;
    bool merge( const int&, const int& );
    bool single( const int& v ) { return !B[v]; } 
    int getSets() const { return subSets; }
    ~Union() { delete [] U; delete [] B; }
};

template<int SZ> void Union<SZ>::init( const int& N ) {
    elem = subSets = N;
    for( int i = 0; i <= N; i++ )   U[i] = i;
}

template<int SZ> bool Union<SZ>::check( int x, int y ) const {
    while( U[x] != x ) x = U[x];
    while( U[y] != y ) y = U[y];
    return x == y;
}

template<int SZ> bool Union<SZ>::merge( const int& x, const int& y ) {
    B[x] = B[y] = true; 
    int p = x, q = y, r = y;
    while( U[p] != p ) p = U[p];
    while( U[q] != q ) q = U[q];
    if( p == q ) return true;
    U[q] = p;
    while( U[r] != p ) {
        q = U[r];
        U[r] = p;
        r = q;
    }
    subSets--;
    return  false;
}

////////////////////////////////////////////////////
//            2008 CopyRight(c) by elf            //
////////////////////////////////////////////////////



// case ���������������� 
int     T,  N,  M;

// ����Ȩֵ 
int     V[14];

// ����������ǰȨֵ�����Ȩֵ 
int     cnt, wgt, mx;

// �ڴ˲���˫��ͼ��ʾ 
// �ڽӱ�����ͼ���� 
int     G1[14][14];
// �ڽӾ������ڱ߲�ѯ 
bool    G2[14][14];

// �ѷ��ʱ�� 
bool    B[14];
int     trace[14]; 
 
// ���鼯(����ͨǰ�ü�֦)
Union<14>   U; 

void Hamilton( int v, int s ) {
    
    // ���������ܶ�·�� 
    if( s == 1 ) {
        // ��ȡ��·����Ȩֵ 
        wgt = 0;
        for( int i = 1; i <= N; ++i ) {
//cout << trace[i] << ' '; 
            // ��һ�����Ȩ 
            wgt += V[trace[i]];
            // �ڶ����Ȩ 
            if( i + 1 <= N )
                wgt += ( V[trace[i]] * V[trace[i+1]] ); 
            // �������·Ȩ
            if( i + 2 <= N &&
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
    for( int i = 1; i <= G1[v][0]; ++i ) {
        if( !B[G1[v][i]] ) {
            B[G1[v][i]] = true;
            trace[trace[0]++] = G1[v][i];
            Hamilton( G1[v][i], s - 1 );
            --trace[0];
            B[G1[v][i]] = false;
        }
    }
    
} 


int main() {
    
    for( scanf( "%d", &T ); T--; ) {
        
        // ��ͼ 
        scanf( "%d%d", &N, &M );
        
        U.init( N ); 
        
        for( int i = 1; i <= N; ++i ) {
            scanf( "%d", V + i );
            G1[i][0] = 1;
            memset( G2[i], 0, sizeof( G2[i] ) ); 
        }
        
        if( N == 1 ) { printf( "%d 1\n", V[1] ); continue; }
        
        for( int i = 1; i <= M; ++i ) {
            int x,  y;
            scanf( "%d%d", &x, &y );
            U.merge( x, y ); 
            G1[x][G1[x][0]++] = y;
            G1[y][G1[y][0]++] = x;
            G2[x][y] = G2[y][x] = true;
        }
        
        // �������ͨ������
        if( U.getSets() != 1 ) {
            puts( "0 0" );
            continue; 
        }
        
        // ��ʼ���ܶ������������ж���Ϊ�����һ�� 
        cnt = mx = 0;
        for( int pos = 1; pos <= N; ++pos ) { 
            
            // ��ʼ��
            trace[0] = 1; 
            memset( B, 0, sizeof( B ) );
        
            // DFS
            trace[trace[0]++] = pos; 
            B[pos] = true; 
            Hamilton( pos, N );
            
        }
        
        // �����ע��ͬһ�����ܶ�·���ᱻ���������� 
        printf( "%d %d\n", mx, cnt / 2 ); 
         
    }
    
}
 
