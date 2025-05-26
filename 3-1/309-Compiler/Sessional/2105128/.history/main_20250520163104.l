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
    if(st.empty()){
        cout<<"not matched"<<endl;
        return 0;
    }
    st.pop();
    if(st.empty()){
        BEGIN INITIAL;
    }
    
        char c = st.top();
        if(c == '{'){
            BEGIN CURLY;
        }
        if(c == '['){
            BEGIN SQUARE;
        }
}

%%

int main()
{
    yyin = stdin;
    yylex();

    return 0;
}