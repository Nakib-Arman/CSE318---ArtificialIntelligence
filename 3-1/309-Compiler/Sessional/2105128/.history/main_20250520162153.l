%option noyywrap
%x PAREN
%x CURLY
%x SQUARE

%{
    #include<bits/stdc++.h>
    using namespace std;

%}

stack<char> st;

%%

"(" {
    BEGIN PAREN;
    st.push(yytext[0]);
}
<PAREN>")" {
    if(st.empty())
    st.pop();
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
    cout<<"Hello"<<endl;
}