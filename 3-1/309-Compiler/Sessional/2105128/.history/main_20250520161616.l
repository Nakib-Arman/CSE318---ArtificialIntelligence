%option noyywrap
%x PAREN
%x CURLY
%x SQUARE

%{
    #include<bits/stdc++.h>
    using namespace std;

%}

stack<ch> st;

%%

"(" {
    BEGIN PAREN;

}

%%

int main()
{
    cout<<"Hello"<<endl;
}