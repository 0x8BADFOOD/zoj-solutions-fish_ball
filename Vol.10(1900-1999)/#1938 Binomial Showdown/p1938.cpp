#include <iostream>
using namespace std;

int main() {
    double  sum;
    int     i,  n,  k;
    while( ( cin >> n >> k ) && ( k || n ) ) {
        sum = 1.0;
        if( k > n - k ) k = n - k;
        for( i = 1; i <= k; i++ )
            sum *= ( double( n - k + i ) / double( i ) );
        // ����˸�����������Ϊ�˷�ֹ int( 1.9999999999... ) = 1 ֮������ 
        cout << int( sum * 1.000000000001 ) << endl;
    }
}
