%option noyywrap
%x VECTOR

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;

%}


%%

"vector"([ \v\t]"<" {
    BEGIN VECTOR;
    cout<<"vector found yayy"<<endl;
    return 0;
}

"\n" {
    return 0;
}

%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}