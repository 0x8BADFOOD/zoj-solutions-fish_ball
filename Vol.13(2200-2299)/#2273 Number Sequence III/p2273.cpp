// 1796957 2009-03-21 16:49:41 Accepted  2273 C++ 50 4580 ���͵����� 

// ����������������ҲҪ��������������ѯ���࣡ 
// ����һ�α�������ѱ�������Ȼ����ÿ�β�ѯ�Ĵ��۽�����͡�
// ��ô��һ�α��������н�����������أ�
// ��һ������(����������ģ��)����Ŵ� 1 ���� 99999 �������ַ���
// �Լ��ø��ַ���������һ�����ֵġ�
// Ȼ��һ��һ��ɾ��ɾ֮ǰ��������һ���͵ڶ����Ƿ�����ͬһ�����֡�
// ������ǣ���ô�����һ���ڵ��������� k���ַ��� c��
// ��ô��ѯ k �Ľ������ c������ ans[k] = c
// ����Ԥ������֮�󣬶���ÿ�β�ѯ k�� 
// ��� k �Ѿ��������������ô�ǹ����� ans[k]��
// �����һֱ��ǰ�ң�ֱ���ҳ���һ������������� ans[k']�� 

#include <iostream>
using namespace std;

char ans[100000] = {'1'};

char content[488900] = {};
int next[488900] = {1}, idx[488900] = {};

int main() {
    char S[6];
    int top = 1;
    for(int i = 1; i <= 99999; ++i) {
        sprintf(S, "%d", i);
        for(int j = 0; S[j]; ++j) {
            content[top] = S[j];
            next[top] = top + 1;
            idx[top] = i;
            top++;
        }
    }
    int rem = top - 1;
    for(int k = 0; rem > 1; k = 1 - k) {
        int it = next[0], post = 0;
        if(idx[it] != idx[next[it]])
            ans[idx[it]] = content[it];
        if(k == 0) { it = next[it], post = next[post]; }
        while(it != top) {
            next[post] = it = next[it];
            --rem;
            if(it != top) { it = next[it], post = next[post]; }
        }
    }
    int N;
    for(int i = 1; i <= 99999; ++i) if(!ans[i]) ans[i] = ans[i-1];
    while(scanf("%d", &N) != EOF) { putchar(ans[N]); puts(""); }
}
