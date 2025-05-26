%option noyywrap
%x PAREN
%x CURLY
%x SQUARE

%{
    #include<bits/stdc++.h>
    using namespace std;
    stack<char> st;

%}


%%

"(" {
    BEGIN PAREN;
    st.push(yytext[0]);
}
<PAREN>")" {
    st.pop();
    if(st.empty()){
        BEGIN INITIAL;
        cout<<"matched"<<endl;
    }
    else{
        char c = st.top();
        if(c == '{'){
            BEGIN CURLY;
        }
        if(c == '['){
            BEGIN SQUARE;
        }
    }
}
<PAREN>
. {}


%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}