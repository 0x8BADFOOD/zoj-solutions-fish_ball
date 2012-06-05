// Greedy
#include <cstdio>
#include <cstring>
#define MAX 100001

int main() {
	int	A[MAX],	a[MAX],	count[MAX], 
		p[MAX],	m[MAX],	sum;
	int	T,	N;
	int*	index[MAX];
	scanf( "%d", &T ); 
	while( T-- ) {
		scanf( "%d", &N ); 
		sum = 0;
		scanf( "%d%d%d", A, p, m );
		a[0] = A[0];
		for( int i = 1; i < N; i++ ) {
			scanf( "%d%d%d", A + i, p + i, m + i );
			// a �� A ����� 
			a[i] = a[i - 1] + A[i];
		}
		memset( count, 0, N * sizeof( int ) );
		// ���ɼ۸��������� 
		for( int i = N - 2; i >= 0; i-- )
		for( int j = i + 1; j < N; j++ )
			if( p[i] < p[j] )	count[j]++;
			else			count[i]++;
		for( int i = 0; i < N; i++ )
			index[count[i]] = p + i;
		// ��������̰���㷨������������ 
		for( int i = N - 1; i >= 0; i-- ) {
			if( !*index[i] ) continue;
			int	j = index[i] - p;
			// ʵ������Ϊ�ִ��Ʊ�����������֮�����Сֵ 
			int	minus = ( a[j] > m[j] ) ? m[j] : a[j];
			sum += minus * p[j];
			// �����й�Ʊ���� A �� a �м�ȥ������Ʊ��̰�Ĳ��ԣ����������ڿ����
			for( int k = j + 1; k < N; k++ )
				a[k] -= minus;
			while( 1 ) {
				if( minus > A[j] ) {
					a[j] -= A[j];
					minus -= A[j];
					A[j--] = 0;
				}
				else {
					A[j] -= minus;
					a[j] -= minus;
					break;
				}
			}
		}
	/*		
			
			
		while( 1 ) {
			int	max = 0, maxi = -1;
			for( int i = 0; i < N; i++ ) {
				if( p[i] && p[i] >= max ) {
					max = p[i];
					maxi = i;
				}
			}
			if( maxi == -1 ) break;
			int	a = 0;
			for( int i = 0; i <= maxi; i++ )	a += A[i];
			int	minus = ( a > m[maxi] ) ? m[maxi] : a;
			sum += minus * p[maxi];
			p[maxi] = 0;
			while( 1 ) {
				if( minus > A[maxi] ) {
					minus -= A[maxi];
					A[maxi--] = 0;
				}
				else {
					A[maxi] -= minus;
					break;
				}
			}
		}	
		
		
		*/
		printf( "%d\n", sum );
	} 
} 
