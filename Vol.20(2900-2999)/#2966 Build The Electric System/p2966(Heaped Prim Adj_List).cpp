// 2998166 2008-07-23 10:29:17 Accepted 2966 C++ 00:00.04 964K ���͵����� 

// ��С�����������Ż� Prim �㷨

//////////////////////////////////////////////////////////
//       ӳ����ֶ�(Mapped_Binary_Heap)��ģ�� v1.0      //
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
#include <vector>
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

MBH<500>    hp;

vector<pair<int, int> > W[500];

bool    P[500];

int     V,  E,  T,  L;

int     x,  y,  w;

int main() {

    for( scanf( "%d", &T ); T--; ) {

        scanf( "%d%d", &V, &E );

        for( int i = 0; i < V; ++i )
            W[i].clear();

        while( E-- ) {
            scanf( "%d%d%d", &x, &y, &w );
            W[x].push_back( make_pair( y, w ) );
            W[y].push_back( make_pair( x, w ) );
        }

        hp.clear();
        
        x = 0,  y = V - 1,  L = 0;
        
        memset( P, 0, sizeof( P ) );
        
        while( y-- ) {

            P[x] = true;
            
            for( int i = 0; i < W[x].size(); ++i )
                if( !P[W[x][i].first] )
                    hp.push( W[x][i].first, W[x][i].second );
            
            x = hp.top().first;
            L += hp.top().second;
            hp.pop();
            
        }
        
        printf( "%d\n", L );
        
    }

} 
