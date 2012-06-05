// ���~~���ݺ��������� sample2.cpp ���㷨������ȷ��
// �� sample.cpp ��Ҳ�Ǵ�� 
// ���͵�����ϵĶ���Ҳ AC ��
// ���Ǻ����ԵĿ��Ծٳ������� 7 7 50 --> 0 ��ȷ 
// ������� sample.cpp �õ��� 7 7 50 --> 1 ����
// ����̫�� 
#include <iostream>
using namespace std;

int main() {
    int     F[7][7][49];
    for( int a = 0; a < 7; a++ )
    for( int b = 0; b < 7; b++ ) {
        F[a][b][0] = F[a][b][1] = 1;
        for( int i = 2; i < 49; i++ ) {
            F[a][b][i] = ( a * F[a][b][i - 1] +
                           b * F[a][b][i - 2] ) % 7;
        }
    }
    int     A,  B,  N;
    while( ( cin >> A >> B >> N ) && ( A || B || N ) ) {
        A %= 7;
        B %= 7;
        N = ( N - 1 ) % 49;
        cout << F[A][B][N] << endl;
    }
}
