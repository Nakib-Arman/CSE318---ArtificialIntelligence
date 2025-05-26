%option noyywrap
%x paren
%x curly
%x square

%{
    #include<bits/stdc++.h>
    using namespace std;

%}

%%

"(" {
    
}

%%

int main()
{
    cout<<"Hello"<<endl;
}