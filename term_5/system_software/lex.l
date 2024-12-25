%{
    #include <stdio.h>
    #include <stdlib.h>  
%}
%%
    "int"       {return ;}
    "for"       {return ;}
    "while"     {return ;}
    "goto"      {return ;}
    "if"        {return ;}
    "else"      {return ;}
    "printf"    {return ;}
%%

[0-9]*{strcpy(yylval.data, yytext); return num;}
[a-zA-Z]{strcpy(yylval.char, yytext); return rune;}
[+ * / >> << % - *= /= += == > < ++]{strcpy(yylval.char, yytext); return sign;}

in yywrap(void) {
    return 1;
}