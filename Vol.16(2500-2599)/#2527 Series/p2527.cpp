// 1655154 2008-10-03 20:28:27 Accepted  2527 C++ 70 4096 ���͵����� 

// �ܲҵ�һ���⣬�����ٴθ��ܵ� DP ������
// ���� WA �Ѿ����� 10 ����
// ��ʼ��ο���дд�˸� O(n^3)�� DP��Ȼ�� TLE
// Ȼ��ο� ����Ĵ��� ���͵Ľ��ⱨ�棬��д��һ��
// ����֪����Ȼ��������һ�亦������ WA
// ���ۣ������ܵ��ͣ�DP ����Ҫ 

#include <cstdio>
#include <cstdlib>

int icmp( const void* a, const void* b ) {  
	if( *( int* )a > *( int* )b ) return 1;
	if( *( int* )a < *( int* )b ) return -1;
	return	0;
}  

int main() {
	int	max,	top,	temp,	N,	A[1001];
	int*	ptr;
	int	( *B )[1001] = new int[1001][1001];
	while( scanf( "%d", &N ) != EOF ) {
		for( int i = 0; i < N; i++ ) scanf( "%d", A + i );
		// ���� 
		qsort( A, N, 4, icmp );
		// �����ظ������֣�����¼�����ͬ��С���е� max 
		for( int i = top = max = temp = 1; i < N; i++ ) {
			if( A[i] == A[i - 1] )	temp++;
			else {
				A[top++] = A[i];
				if( temp > max ) max = temp;
				temp = 1;
			}
		}
		if( temp > max ) max = temp;
		N = top;
		// ��ʼDP
		for( int i = 1; i < N; i++ ) {
			for( int j = 0; j < i; j++ ) {
				temp = 2 * A[j] - A[i];
				ptr = ( int* )bsearch( &temp, A, j, 4, icmp );
				if( !ptr )	B[i][j] = 2;
				else {
					B[i][j] = B[j][ptr - A] + 1;
					if( B[i][j] > max ) max = B[i][j];
				}
			}
		}
		if( B[N - 1][N - 2] > max ) max = B[N - 1][N - 2];
		printf( "%d\n", max );
	}
}
