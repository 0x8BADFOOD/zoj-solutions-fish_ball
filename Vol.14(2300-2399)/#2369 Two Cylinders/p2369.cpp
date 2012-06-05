// ��ֵ����... �������ֺ����ǳ�����

// ���ֿ��������㣺������Բ������ƽ��ƽ�еķ�����Ƭ
// �г����Ķ��Ǿ��Σ�����Ƴ����Ĺ�ʽ��
// 8��sqrt(r1^2-x^2)*sqrt(r2^2-x^2)dx 

// ������ô�߾��Ȼ��֣�������������ʽ֮��ģ������ҳ�����
// ����������ر�ĺã���С����... 

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double  R,  r;
int     T;

inline double f( const double& x ) {
    return  sqrt( ( R*R - x*x ) * ( r*r - x*x ) );
}

double simpson(double a, double b, double eps) {
    int n,i;
    double h = b - a, temp, ret, T, C, x;
    for (T = f(a) + f(b), n = 1; ; ) {
        for (x = a + 0.5 * h, C = 0.0, i = 0; i < n; x += h, ++i)
            C += f(x);
        ret = (T + 4 * C) * h / 6;
        if (fabs(ret - temp) < eps)
            return ret;
        temp = ret, T += 2 * C, h *= 0.5, n <<= 1;
    }
}

int main() {
    
    cin >> T;
        
    while( T-- ) {
        
        cin >> R >> r;
        
        if( R < r )
            swap( R, r );

        double ans = simpson( 0.0, r, 1e-5 );
        
        printf( "%.4lf\n", ans * 8.0 );
        
        if( T ) cout << endl;

    }
    
}
