// 2941726 2008-06-04 15:54:44 Accepted 2486 C++ 00:00.00 844K ���͵����� 

// �൱ ym��ԭ���� double ��������һ���ܳ��ܳ������� 

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    
    double  x,  y;
    
    while( cin >> x >> y )
        cout << round( exp( log( y ) / x ) ) << endl;
    
}
