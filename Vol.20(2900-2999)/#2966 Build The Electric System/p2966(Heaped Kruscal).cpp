// 2997508 2008-07-22 21:10:36 Accepted 2966 C++ 00:00.02 3368K ���͵����� 

// ��С�����������Ż� Kruscal �㷨 

////////////////////////////////////////////////////
//              ���鼯ģ��(UFS) v1.2              //
////////////////////////////////////////////////////
//                                                //
// 1. SZ:         ���鼯���Ԫ������(ģ�����);   //
// 2. make_set:   ��ʼ�� N ��Ԫ�صĲ��鼯;        //
// 3. find_set:   �ҳ�ĳ��Ԫ�����ڵļ���;         //
// 4. union_set:  �ϲ���������;                   // 
// 5. get_sets:   ���ز��鼯�Ӽ��ĸ���;           //
// 6. get_size:   ����Ԫ�������Ӽ��Ĵ�С;         //
//                                                //
// v1.2 �����ԣ�                                  // 
//   ����ʽ���ԣ� ���Ⱥϲ���·��ѹ��              //
//   �����ӿڣ�   �Ӽ��������Ӽ���С              // 
//                                                //
////////////////////////////////////////////////////
//            2008 CopyRight(c) by elf            //
////////////////////////////////////////////////////

template<int SZ> class UFS {

    int p[SZ+1], rank[SZ+1], size[SZ+1], sets; 

public:
    
    void make_set( int sz ) {
        for( int i = 0; i <= sz; ++i ) {
            p[i] = i;
            rank[i] = 0;
            size[i] = 1;
        }
        sets = sz;
    }
    
    int find_set( int x ) {
        if( x != p[x] )
            p[x] = find_set( p[x] );
        return  p[x];
    }

    bool union_set( int x, int y ) {
        x = find_set( x );
        y = find_set( y );
        if( x == y )    return  false;
        --sets;
        if( rank[x] > rank[y] ) {
            size[x] += size[y];
            p[y] = x;
        }
        else {
            size[y] += size[x];
            p[x] = y;
        }
        if( rank[x] == rank[y] )
            ++rank[y];
        return  true;
    }
    
    int get_sets() const { return sets; }
    
    int get_size( int x ) { return size[find_set( x )]; }
    
};

////////////////////////////////////////////////////
//            2008 CopyRight(c) by elf            //
////////////////////////////////////////////////////


#include <cstdio>
#include <algorithm>

struct Edge {
    int x,  y,  w;
    Edge() {};
    Edge( int x, int y, int w ) :
        x( x ), y( y ), w( w ) {}
};

UFS<500>    U;

Edge    P[500*500];
int     V,  E,  T,  x,  y,  w,  L;

inline bool operator < ( const Edge& e1, const Edge& e2 ) {
    return  e1.w > e2.w;
}

int main() {
    
    for( scanf( "%d", &T ); T--; ) {

        scanf( "%d%d", &V, &E );

        U.make_set( V );

        for( int i = 0; i < E; ++i ) {
            scanf( "%d%d%d", &x, &y, &w );
            P[i].x = x;
            P[i].y = y;
            P[i].w = w;
        }
        
        std::make_heap( P, P + E );
        
        L = 0;
        
        while( E-- ) {
            if( U.find_set( P -> x ) != U.find_set( P -> y ) ) {
                L += P -> w;
                U.union_set( P -> x, P -> y );
            }
            if( U.get_sets() == 1 ) break;
            std::pop_heap( P, P + E + 1 ); 
        }

        printf( "%d\n", L );
        
    }

} 
