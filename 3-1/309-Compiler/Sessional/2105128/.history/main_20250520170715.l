%option noyywrap
%x VECTOR

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;

%}


%%

"vector"[\v\t]"<" {
    BEGIN VECTOR;
    cout<<"vector found yayy"<<endl;
}

"\n" {
    
}

%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}