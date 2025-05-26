%option noyywrap
%x PAREN
%x CURLY
%x SQUARE

%{
    #include<bits/stdc++.h>
    using namespace std;

%}

%%

"(" {
    BEGIN 
}

%%

int main()
{
    cout<<"Hello"<<endl;
}