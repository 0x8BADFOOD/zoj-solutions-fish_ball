// 1653342 2008-10-01 21:26:38 Accepted  1577 C++ 220 260 ���͵����� 

// ����������ǿ��Թ��ģ���Ҫ��ͷ�Բ�������
// �߼����ܴ��ˣ�����
// ���㷨���ǲ�̫�õģ������ƹ�ʽ 
#include <cstring>
#include <cstdio>

int main() {
	int	X,	Y,	M,	N,	R;
	while( scanf( "%d%d", &X ,&Y ) != EOF ) {
		int	count = 0;
		for( int i = X; i <= Y; i += X ) {
			if( Y % i == 0 ) {
				M = X * Y / i;
				N = i;
				while( N ) {
					R = M % N;
					M = N;
					N = R;
				}
				if( M == X )	count++;
			}
		}
		printf( "%d\n", count );
	}
	
}
