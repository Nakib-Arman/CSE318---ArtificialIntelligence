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
    if (argc != 2) {
        printf("No input file provided");
        fprintf(f1,"No input file provided");
        return 1;
    }
    char* filename = argv[1];
    FILE *input_file = fopen(filename,"r");
    if(input_file == NULL){
        perror("Error opening input file");
        return 1;
    }

    yyin = input_file;
    yylex();
    fclose(yyin);
    fclose(f1);

    return 0;
}