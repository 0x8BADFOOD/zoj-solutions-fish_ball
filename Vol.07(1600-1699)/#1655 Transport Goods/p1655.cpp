// 3005534 2008-07-26 00:19:37 Accepted 1655 C++ 00:00.04 928K ���͵����� 

// ��Դ���·��ע��Ȩ��̵ĺ��壬�� Dijkstra��ʹ��·Ȩ�˻���� 

// ע�⣬���Ǹ�����ͼ���к� WS �����㣺
// 1. ��ƽ�б�; 2. ��ȷ����ͨ��

// �Ժ����⣬һ��Ҫע��ҧ�Ľ��֣�������Щϸ��Ҫ�ر�ϸ�� 

//////////////////////////////////////////////////////////
//       ӳ����ֶ�(Mapped_Binary_Heap)��ģ�� v1.3      //
//////////////////////////////////////////////////////////
//                                                      //
//                   ģ�����                           //
// 1. SZ:     ӳ����ֶѵ����������;                   //
// 2. T:      ӳ����ֶ��̺�ֵ���ͣ�ȱʡΪ int;         //
// 3. Op:     �Ƚ�׼�� functor��ȱʡΪС��;             // 
//                                                      //
//                     �ӿ�                             //
// 1. clear:  ��ն�;                                   //
// 2. empty:  �п�;                                     // 
// 3. size:   ���ضѴ�С(Ԫ�ظ���);                     //
// 4. top:    ���ضѶ�Ԫ��(������ֵ���);               //
// 5. push:   ����������Ԫ�أ��Զ�ʶ�����Ϊ��Сֵ;     //
// 6. pop:    ɾ����Сֵ;                               //
//                                                      //
//////////////////////////////////////////////////////////
//               2008 CopyRight(c) by elf               //
//////////////////////////////////////////////////////////

#include <functional>
#include <algorithm>
using namespace std;

template <int SZ, class T = int, class Op = less<T> >
class MBH {

    pair<int, T> heap[SZ + 1];
    int key[SZ + 1], sz;

public:

    void clear() { sz = 0; memset( key, 0, sizeof( key ) ); }
    
    int size() const { return sz; }
    
    bool empty() const { return sz == 0; } 
    
    pair<int, T> top() const { return heap[1]; }
    
    void push( int idx, T val ) {
        if( !key[idx] ) {
            key[idx] = ++sz;
            heap[sz] = make_pair( idx, val );
        }
        else if( Op()( val, heap[key[idx]].second ) )
            heap[key[idx]].second = val;
        for( int pos = key[idx], c;
            ( c = pos >> 1 ) && Op()( val, heap[c].second ); pos = c ) {
            swap( heap[pos], heap[c] );
            key[idx] = c;
            key[heap[pos].first] = pos;
        }
    }
    
    void pop() {
        key[heap[1].first] = 0;
        heap[1] = heap[sz--];
        if( sz == 0 )   return;
        key[heap[1].first] = 1;
        for( int pos = 1, c; ( c = pos<<1 ) <= sz; pos = c ) {
            if( c < sz && Op()( heap[c+1].second, heap[c].second ) ) ++c;
            if( Op()( heap[c].second, heap[pos].second ) ) {
                swap( heap[c], heap[pos] );
                key[heap[c].first] = c;
                key[heap[pos].first] = pos;
            }
            else break;
        }
    }

};

//////////////////////////////////////////////////////////
//               2008 CopyRight(c) by elf               //
//////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

MBH<100, double, greater<double> >  hp;

double  dist[101],  val[101],   z,  tot;

double  G[101][101]; 

int N,  M,  x,  y;

int main() {
    
    while( scanf( "%d%d", &N, &M ) != EOF ) {
    
        for( int i = 1; i < N; ++i )
            scanf( "%lf", val + i );
        
        memset( G, 0, sizeof( G ) );
        
        while( M-- ) {
            scanf( "%d%d%lf", &x, &y, &z );
            if( G[y][x] < 1.0 - z )
                G[y][x] = 1.0 - z; 
            G[x][y] = G[y][x];
        }
        
        for( int i = 1; i < N; ++i )
            dist[i] = -1.0; 
        
        dist[x = N] = 1.0;
        hp.clear();
        
        while( 1 ) {
            for( y = 1; y <= N; ++y )
                if( G[x][y] > -0.5 && dist[y] < -0.5 )
                    hp.push( y, dist[x] * G[x][y] );
            if( hp.empty() )    break; 
            x = hp.top().first;
            dist[x] = hp.top().second;
            hp.pop();
        }
        
        tot = 0.0;
        for( int i = 1; i < N; ++i )
            if( dist[i] > -0.5 ) 
                tot += ( val[i] * dist[i] );
            
        printf( "%.2lf\n", tot );
    
    }
    
}
