%option noyywrap
%x PAREN
%x curly
%x square

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