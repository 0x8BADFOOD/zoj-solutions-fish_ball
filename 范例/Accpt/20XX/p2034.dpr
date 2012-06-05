program p2034;

{$APPTYPE CONSOLE}

{%File 'p.in'}

const
        maxn    = 100;

type
        Tb      = set of 1 .. maxn;

var
        light , heavy           : Tb; // ���ܼ��ϣ��� ����
        part , n , m            : Longint;
        state                   : Char;

procedure doit;
var     left , right            : Tb;
        l , i , t               : Longint;
begin
left := []; right := [];
read ( l );
for i := 1 to l do
        begin
        read ( t );
        left := left + [t];
        end;

for i := 1 to l do
        begin
        read ( t ); if t in left then while true do;
        right := right + [t];
        end;
readln;
readln ( state );

case state of
        '='     : begin // ���ͬʱ�ų�����
                heavy := heavy - left - right;
                light := light - left - right;
                end;
        '>'     : begin // �����  ��ô�����ؼ��� ֻ�ܳ������ ���������ұ� �������
                heavy := heavy * left; heavy := heavy - right;
                light := light - left; light := light * right;
                end;
        '<'     : begin // ����
                heavy := heavy - left; heavy := heavy * right;
                light := light * left; light := light - right;
                end;
end;

end;

procedure print;
var     ta , tb         : Longint;
        c1 , c2 , c     : Longint;
        i               : Longint;
begin
ta := 0; tb := 0; c1 := 0; c2 := 0; c := 0;
for i := 1 to n do
        if i in light then
                begin
                c1 := i;    // ��¼�����е�һ��Ԫ�� ���ֻ��һ����ô�������Ψһ�Ĵ�
                c := i;
                inc ( ta ); // ���Ἧ���е�Ԫ�ظ���
                end;

for i := 1 to n do
        if i in heavy then
                begin
                c2 := i;
                c := i;
                inc ( tb ); // ���ؼ����е�Ԫ�ظ���
                end;

if ( ta + tb = 1 ) then writeln ( c ) else // ֻ��һ��Ԫ��
if ( ta = 1 ) and ( tb = 1 ) and ( c1 = c2 ) then writeln ( c1 ) else // ���������ж���һ����ͬ��Ԫ��
        writeln ( 0 );
end;

begin
readln ( part );
while ( part > 0 ) do
        begin
        readln ( n , m );

        light := [1..n];
        heavy := [1..n]; // �����е�Ԫ��Ϊ���ܵ�

        while ( m > 0 ) do
                begin
                doit; // ���������ж�
                dec ( m );
                end;

        print;   // ���

        dec ( part );
        if part > 0 then writeln;
        end;
end.

