grammar MiniC;

// PARSER
prog: (decl | stmt)* EOF;

// declaraciones
decl
  : vtype ID '=' expr ';'        // int x = 5;
  | vtype ID ';'                 // int x;
  ;

// sentencias
stmt
  : '{' (decl | stmt)* '}'                                  #Block
  | 'if' '(' expr ')' stmt ('else' stmt)?                   #IfStmt
  | 'while' '(' expr ')' stmt                               #WhileStmt
  | 'for' '(' forInit? ';' forCond? ';' forPost? ')' stmt   #ForStmt
  | ID '=' expr ';'                                         #Assign
  | ID ('+=' | '-=' | '*=' | '/=' | '%=') expr ';'          #AugAssignStmt
  | ID ('++' | '--') ';'                                    #IncDecStmt
  | 'cout' ('<<' expr)+ ';'                                 #CoutStmt
  | 'cin'  ('>>' ID)+  ';'                                  #CinStmt
  | expr ';'                                                #ExprStmt
  ;

// partes del for
forInit
  : vtype ID ('=' expr)? (',' ID ('=' expr)? )*
  | postItem (',' postItem)*
  ;
forCond : expr ;
forPost : postItem (',' postItem)* ;

// i = 0, j += 2, k++
postItem
  : ID '=' expr                                            #PostAssign
  | ID ('+=' | '-=' | '*=' | '/=' | '%=') expr             #PostAugAssign
  | ID ('++' | '--')                                       #PostIncDecPost
  | ('++' | '--') ID                                       #PostIncDecPre
  ;

// expresiones
expr
  : ('!' | '+' | '-') expr                                 #exprUnary
  | ('++' | '--') expr                                     #exprPreIncDec
  | expr ('++' | '--')                                     #exprPostIncDec
  | expr ('*' | '/' | '%') expr                            #exprMulDiv
  | expr ('+' | '-') expr                                  #exprAddSub
  | expr ('<' | '<=' | '>' | '>=') expr                    #exprRel
  | expr ('==' | '!=') expr                                #exprEq
  | expr '&&' expr                                         #exprAnd
  | expr '||' expr                                         #exprOr
  | '(' expr ')'                                           #exprPar
  | literal                                                #exprLiteral
  | ID                                                     #exprVar
  ;

// literales y tipos
literal
    : INT
    | DOUBLE
    | BOOL
    | STRING
    ;

vtype : 'int' | 'double' | 'bool' | 'string' ;

// LEXER
// tipo de variable
TINT         : 'int' ;
TDOUBLE      : 'double' ;
TBOOL        : 'bool' ;
TSTRING      : 'string' ;

// palabras reservadas
IF           : 'if' ;
ELSE         : 'else' ;
WHILE        : 'while' ;
FOR          : 'for' ;
COUT         : 'cout' ;
CIN          : 'cin' ;

// delimitadores
SEMI         : ';' ;
COMMA        : ',' ;
LPAREN       : '(' ;
RPAREN       : ')' ;
LBRACE       : '{' ;
RBRACE       : '}' ;

// operadores
ASSIGN       : '=' ;
PLUS         : '+' ;
MINUS        : '-' ;
MUL          : '*' ;
DIV          : '/' ;
MOD          : '%' ;
PLUSEQ       : '+=' ;
MINUSEQ      : '-=' ;
STAREQ       : '*=' ;
DIVEQ        : '/=' ;
MODEQ        : '%=' ;
PLUSPLUS     : '++' ;
MINUSMINUS   : '--' ;
LT           : '<' ;
LE           : '<=' ;
GT           : '>' ;
GE           : '>=' ;
EQEQ         : '==' ;
NEQ          : '!=' ;
ANDAND       : '&&' ;
OROR         : '||' ;
NOT          : '!' ;
SHL          : '<<' ; // para cout <<
SHR          : '>>' ; // para cin >>

// literales e identificadores
BOOL         : 'true' | 'false' ;
INT          : [0-9]+ ;
DOUBLE       : [0-9]+ '.' [0-9]+ ;
STRING       : '"' (~["\\] | '\\' .)* '"' ;
ID           : [a-zA-Z_][a-zA-Z_0-9]* ;

// espacios y comentarios
WS           : [ \t\r\n]+ -> skip ;
LINE_COMMENT : '//' ~[\r\n]* -> skip ;
BLOCK_COMMENT: '/*' .*? '*/' -> skip ;
