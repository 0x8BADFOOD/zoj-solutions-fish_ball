// 2955002 2008-06-22 22:20:03 Accepted 2992 C++ 00:00.00 860K ���͵����� 

// ������������ʵ�϶�����һ��ջ�㶨�İ취���������ˣ�ֱ��������ģ�� 

// ������İ취�ǣ�����һ���ն����������нṹû�����ݵģ�
// Ȼ���ú��� weight �������
// ��� weight �ǿգ����� 1
// ���򣬵ݹ��������������Ȩֵ��ȡ������ߵ���������
// ���ķ���ֵ���Ǹ�������Ȩֵ

// ��������ʱ���Ƚ��������һ���ڵ㣬��ǰָ��ָ������ڵ� 
// ������������ţ������ǰ���ţ�������չһ���ڵ�
//  ����������������������Ƚ��ڵ㣬��ǰָ��ָ������������������������ 
// ����Ǻ����ţ�ָ��ָ�����ĸ��� 

// ��󣬼ǵ�����������ȻҲ������֮�ڴ�й©��

// ���У�������մ���ʱ����Ϊ 1 

#include <iostream>
#include <string>
using namespace std;

struct Node {
    Node*   left;
    Node*   right;
    Node*   parent;
    Node( Node* p ) : parent( p ),
        left( NULL ), right( NULL ) {}
};

int weight( Node* ptr ) {
    
    if( !ptr )  return 1;
    
    int x = weight( ptr -> left ),
        y = weight( ptr -> right );
    
    return  ( x < y ) ? 2 * y : 2 * x;
    
}

void destroy( Node* ptr ) {
    
    if( ptr -> left )
        destroy( ptr -> left );
        
    if( ptr -> right )
        destroy( ptr -> right );
        
    delete  ptr;
    ptr = NULL; 
    
}
    
int main() {
    
    int     T;
    string  S;
    
    cin >> T;
    getline( cin, S );
    
    for( int t = 1; t <= T; ++t ) {
        
        getline( cin, S );
        cout << t << ' ';
        
        if( S == "" ) {
            puts( "1" );
            continue; 
        }        
        
        Node*   root = new Node( NULL );
        Node*   ptr = root;
        
        for( int i = 1; i + 1 < S.size(); ++i ) {
            if( S[i] == '[' ) {
                if( !ptr -> left ) {
                    ptr -> left = new Node( ptr );
                    ptr = ptr -> left;
                }
                else {
                    ptr -> right = new Node( ptr );
                    ptr = ptr -> right;
                }
            }
            else    ptr = ptr -> parent;
        }
        
        cout << weight( root ) << endl;

        destroy( root );
        
    }
    
}
