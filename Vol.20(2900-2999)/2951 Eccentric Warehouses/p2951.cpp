// 1870318 2009-05-15 14:47:56 Accepted  2951 C++ 1550 184 ���͵����� 

// �������ʴ��ݣ�����С�Ĵ��ݴ��ۡ� 
// ���������ŵĲ����£��ض���һ��·��û�д��ݡ�
// ö������·��������һ�ξ����ˣ�O(n^2) �ĸ��Ӷȡ�
// �����Թ�Լ����С��������������� 

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int T, N;
    double A[2000], B[2000], C[2001];
    int P[2000], D[2000];
    for(cin >> T; T--;) {
        cin >> N;
        double tot = 0, den = 0;
        for(int i = 0; i < N; ++i) {
            cin >> A[i];
            tot += A[i];
        }
        for(int i = 0; i < N; ++i) {
            cin >> P[i];
            den += P[i];
        }
        for(int i = 0; i < N; ++i) cin >> D[i];
        for(int i = 0; i < N; ++i)
            B[i] =  tot * P[i] / den;
        double ans = 1e99;
        for(int i = 0; i < N; ++i) {
            double cost = 0;
            for(int j = 0; j < N; ++j) C[j] = A[j];
            int j = i;
            do {
                cost += fabs(C[j] - B[j]) * D[j];
                C[(j + 1) % N] += C[j] - B[j];
                C[j] = B[j];
                j = (j + 1) % N;
            } while(j != i);
            if(cost < ans) ans = cost;
        }
        printf("%.2lf\n", ans);
    }
}
