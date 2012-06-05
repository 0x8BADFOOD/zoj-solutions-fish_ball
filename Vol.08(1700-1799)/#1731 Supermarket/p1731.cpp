// 2995835 2008-07-22 11:11:09 Accepted 1731 C++ 00:00.12 1160K ���͵����� 

// N ����Ʒ��ÿ���۸�Ϊ p��������Ϊ d
// ÿ��ֻ����һ��������ô���ţ�ʹ�������������������� 

// ��̰�������Ȱ��۸����򣬼۸����ѡʱ���� 
// Ȼ���մӴ�Сö�٣�����ļ���û�ù� 
// ��û�ù��ĸ���������ѡȡ���ȵ�ǰ��Ʒ������С�ĵ������� 
// ɾ�����죬�����ܼ۸���ϵ�ǰ��Ʒ�ļ۸�

// ����û�ù���������һ�� set ��ά�����൱�� 

#include <iostream>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

pair<int, int>  V[10001];

int     N;

set<int>            S;
set<int>::iterator  iter;

int main() {
    
    while( scanf( "%d", &N ) != EOF ) {
    
        int mx = 0;
        
        for( int i = 0; i < N; ++i ) {
            scanf( "%d%d", &V[i].first, &V[i].second );
            if( V[i].second > mx )
                mx = V[i].second;
        }
        
        S.clear();
        for( int i = 1; i <= mx; ++i )
            S.insert( S.end(), i );
        
        sort( V, V + N );
        
        int cnt = 0;
        
        for( int i = N - 1; i >= 0; --i ) {
            if( S.empty() ) break;
            if( *S.begin() > V[i].second ) continue;
            cnt += V[i].first;
            iter = S.upper_bound( V[i].second );
            --iter;
            S.erase( iter );
        }
        
        printf( "%d\n", cnt );
    
    }
    
}
