<div style="width: 100%; clear: both;">
<div style="float: left; width: 50%;">
<img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ45DITH77up1n8tb7Bx2n7TO8tBq4I65ZIuw&s", align="left">
</div>
<div style="float: right; width: 50%;">
<p style="margin: 0; padding-top: 22px; text-align:right;">1ACC0218-2520-1733 - Teoría de Compiladores </p>
<p style="margin: 0; text-align:right;">2025 · Compilador</p> 
<p style="margin: 0; text-align:right;">Prof: <b>Peter Jonathan Montalvo Garcia</b></p>
<p style="margin: 0; text-align:right; padding-button: 100px;">Integrante 1: <b>Mendoza Quispe Carlos Fabian  </b> - <a href="">U20231C416@upc.edu.pe</a></p>
<p style="margin: 0; text-align:right; padding-button: 100px;">Integrante 2: <b>Ibarra Cabrera Camila Adriana </b> - <a href="">U202317287@upc.edu.pe</a></p>
<p style="margin: 0; text-align:right; padding-button: 100px;">Integrante 3: <b>Rojas Sánchez Patricia Lucía del Rosario</b> - <a href="">U202310474@upc.edu.pe</a></p>
</div>
</div>
<div style="width:100%;">&nbsp;</div>
<center><h1>📙 Introducción</h1></center>
El pensamiento computacional es una habilidad crucial y fundamental para la programación moderna, ya que dota a los individuos de capacidades esenciales como el pensamiento crítico, la abstracción y el razonamiento algorítmico necesarias para la formulación de soluciones óptimas a problemas complejos, tanto dentro como fuera del ámbito informático; sin embargo, a pesar de su reconocida importancia, persisten serias dificultades en la enseñanza de la programación, inherentes a su complejidad técnica y a la falta de desarrollo de estas habilidades clave, donde la tendencia actual, amplificada por la influencia de la IA, prioriza la generación de código funcional complejo sobre el dominio de los fundamentos lógicos y algorítmicos, dejando a menudo a los programadores principiantes o inexpertos sin una base sólida; por esta razón, es imperativo reenfocar el aprendizaje de la programación desde sus etapas iniciales hacia la lógica y el pensamiento computacional, lo que no solo facilitará la comprensión clara y accesible de los fundamentos, sino que también proporcionará a los estudiantes una base robusta que les permitirá trascender las reglas específicas de un lenguaje para aplicar principios generales en diversos contextos, promoviendo una crucial adaptabilidad y preparándolos efectivamente para enfrentar nuevas tecnologías, herramientas y paradigmas de la programación.

<div style="width:100%;">&nbsp;</div>
<center><h1>👥 Integrantes </h1></center>
Los integrantes para el desarrollo del proyecto son los siguientes:

<table>
  <thead>
    <tr>
      <th scope="col">Número</th>
      <th scope="col">Integrante</th>
      <th scope="col">Correo</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>1</td>
      <td>Camila Adriana Ibarra Cabrera</td>
      <td>U202317287@upc.edu.pe</td>
    </tr>
    <tr>
      <td>2</td>
      <td>Carlos Fabian Mendoza Quispe</td>
      <td>U20231C416@upc.edu.pe</td>
    </tr>
    <tr>
      <td>3</td>
      <td>Patricia Lucía del Rosario Rojas Sánchez</td>
      <td>U202310474@upc.edu.pe</td>
    </tr>
  </tbody>
</table>

<center><h1>📁 Descripción del Codigo en Python </h1></center>
A continuación se muestra el código explicado paso a paso.

### 1. Instalación de dependencias

```bash
!curl -O https://www.antlr.org/download/antlr-4.13.1-complete.jar
```  
```bash
!pip install -U antlr4-python3-runtime
```

### 2. Creación de la gramática CPP.g4
```bash
%%writefile CPP.g4
grammar CPP;

// PARSER
prog: (decl|stmt)* EOF;

// declaraciones
decl
  : decltype ID '=' expr ';'        // int x = 5;
  | decltype ID ';'                 // int x;
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
  : decltype ID ('=' expr)? (',' ID ('=' expr)? )*
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
	: ('!' | '+' | '-') expr                               #exprUnary
  | ('++' | '--') ID                                     #exprPreIncDec
  | ID ('++' | '--')                                     #exprPostIncDec
  | expr ('*' | '/' | '%') expr                          #exprMulDiv
  | expr ('+' | '-') expr                                #exprAddSub
  | expr ('<' | '<=' | '>' | '>=') expr                  #exprRel
  | expr ('==' | '!=') expr                              #exprEq
  | expr '&&' expr                                       #exprAnd
  | expr '||' expr                                       #exprOr
  | '(' expr ')'                                         #exprPar
  | literal                                              #exprLiteral
  | ID                                                   #exprVar
  ;

// literales y tipos
literal
    : INT
    | DOUBLE
    | BOOL
    | STRING
    ;
decltype : 'int' | 'double' | 'bool' | 'string' ;


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
BLOCK_COMMENT: '/*' .*? '*/' -> skip ;%%writefile CPP.g4
grammar CPP;

// PARSER
prog: (decl|stmt)* EOF;

// declaraciones
decl
  : decltype ID '=' expr ';'        // int x = 5;
  | decltype ID ';'                 // int x;
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
  : decltype ID ('=' expr)? (',' ID ('=' expr)? )*
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
	: ('!' | '+' | '-') expr                               #exprUnary
  | ('++' | '--') ID                                     #exprPreIncDec
  | ID ('++' | '--')                                     #exprPostIncDec
  | expr ('*' | '/' | '%') expr                          #exprMulDiv
  | expr ('+' | '-') expr                                #exprAddSub
  | expr ('<' | '<=' | '>' | '>=') expr                  #exprRel
  | expr ('==' | '!=') expr                              #exprEq
  | expr '&&' expr                                       #exprAnd
  | expr '||' expr                                       #exprOr
  | '(' expr ')'                                         #exprPar
  | literal                                              #exprLiteral
  | ID                                                   #exprVar
  ;

// literales y tipos
literal
    : INT
    | DOUBLE
    | BOOL
    | STRING
    ;
decltype : 'int' | 'double' | 'bool' | 'string' ;


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
```
### 3. Generar el lexer y parser en Python
```bash
!java -jar antlr-4.13.1-complete.jar -Dlanguage=Python3 -visitor CPP.g4
```
### 4. Visitor en Python (Visitor.py)
```bash
from antlr4 import *
from CPPLexer import CPPLexer
from CPPParser import CPPParser
from CPPVisitor import CPPVisitor

class Visitor(CPPVisitor):
    def __init__(self):
        self.ind = 0

    def pad(self, s):
        print("  " * self.ind + s)

    # ========== raíz ==========
    def visitProg(self, ctx:CPPParser.ProgContext):
        for ch in list(ctx.getChildren()):
            self.visit(ch)
        return None

    # ========== declaraciones ==========
    # decl : decltype ID '=' expr ';' | decltype ID ';'
    def visitDecl(self, ctx:CPPParser.DeclContext):
        kids = list(ctx.getChildren())  # [decltype, ID, ('=' expr)?, ';']
        t = kids[0].getText()
        name = kids[1].getText()
        if len(kids) >= 5 and kids[2].getText() == '=':
            self.pad(f"declarar {t} {name} ← {self._ppExpr(ctx.expr())}")
        else:
            self.pad(f"declarar {t} {name}")
        return None

    # ========== sentencias ==========
    def visitBlock(self, ctx):
        self.pad("inicio")
        self.ind += 1
        for ch in list(ctx.getChildren()):
            # dentro hay decl | stmt repetidos
            if isinstance(ch, (CPPParser.DeclContext, CPPParser.StmtContext)):
                self.visit(ch)
        self.ind -= 1
        self.pad("fin")
        return None

    def visitAssign(self, ctx):
        self.pad(f"{ctx.ID().getText()} ← {self._ppExpr(ctx.expr())}")
        return None

    def visitAugAssignStmt(self, ctx):
        # ID ('+='|... ) expr ';'
        kids = list(ctx.getChildren())
        x = kids[0].getText()
        op = kids[1].getText().replace('=','')
        self.pad(f"{x} ← {x} {op} {self._ppExpr(ctx.expr())}")
        return None

    def visitIncDecStmt(self, ctx):
        kids = list(ctx.getChildren())
        x = kids[0].getText()
        op = kids[1].getText()
        self.pad(f"{x} ← {x} {'+ 1' if op=='++' else '- 1'}")
        return None

    def visitCoutStmt(self, ctx):
        parts = [self._ppExpr(e) for e in ctx.expr()]
        self.pad("mostrar " + " ; ".join(parts))
        return None

    def visitCinStmt(self, ctx):
        ids = [tok.getText() for tok in ctx.ID()]
        self.pad("leer " + ", ".join(ids))
        return None

    def visitExprStmt(self, ctx):
        self.pad(self._ppExpr(ctx.expr()))
        return None

    def visitIfStmt(self, ctx):
        # 'if' '(' expr ')' stmt ('else' stmt)?
        self.pad(f"si {self._ppExpr(ctx.expr())} entonces")
        self.ind += 1
        self.visit(ctx.stmt(0))
        self.ind -= 1
        if ctx.stmt(1) is not None:
            self.pad("si no")
            self.ind += 1
            self.visit(ctx.stmt(1))
            self.ind -= 1
        self.pad("fin si")
        return None

    def visitWhileStmt(self, ctx):
        self.pad(f"mientras {self._ppExpr(ctx.expr())} hacer")
        self.ind += 1
        self.visit(ctx.stmt())
        self.ind -= 1
        self.pad("fin mientras")
        return None

    def visitForStmt(self, ctx):
        # 'for' '(' forInit? ';' forCond? ';' forPost? ')' stmt
        init = self._ppForInit(ctx.forInit()) if ctx.forInit() else ""
        cond = self._ppExpr(ctx.forCond().expr()) if ctx.forCond() else ""
        post = self._ppForPost(ctx.forPost()) if ctx.forPost() else ""
        self.pad(f"para ( {init} ; {cond} ; {post} )")
        self.ind += 1
        self.visit(ctx.stmt())
        self.ind -= 1
        self.pad("fin para")
        return None

    # ========== partes del for ==========
    def _ppForInit(self, ctx:CPPParser.ForInitContext):
        if ctx.decltype():
            # decltype ID (=expr)? (',' ID (=expr)?)*
            t = ctx.decltype().getText()
            names = [tok.getText() for tok in ctx.ID()]
            exprs = [self._ppExpr(e) for e in ctx.expr()]
            out, ei = [], 0
            for name in names:
                if ei < len(exprs):
                    out.append(f"declarar {t} {name} ← {exprs[ei]}"); ei += 1
                else:
                    out.append(f"declarar {t} {name}")
            return " , ".join(out)
        # postItem lista
        return " , ".join(self._ppPostItem(pi) for pi in ctx.postItem())

    def _ppForPost(self, ctx:CPPParser.ForPostContext):
        return " , ".join(self._ppPostItem(pi) for pi in ctx.postItem())

    def _ppPostItem(self, pi):
        cname = type(pi).__name__
        if cname.endswith("PostAssign"):
            return f"{pi.ID().getText()} ← {self._ppExpr(pi.expr())}"
        if cname.endswith("PostAugAssign"):
            x = pi.ID().getText()
            op = pi.getChild(1).getText().replace('=','')
            return f"{x} ← {x} {op} {self._ppExpr(pi.expr())}"
        if cname.endswith("PostIncDecPost"):
            x = pi.ID().getText()
            op = pi.getChild(1).getText()
            return f"{x} ← {x} {'+ 1' if op=='++' else '- 1'}"
        if cname.endswith("PostIncDecPre"):
            x = pi.ID().getText()
            op = pi.getChild(0).getText()
            return f"{x} ← {x} {'+ 1' if op=='++' else '- 1'}"
        return "<postItem>"

    # ========== pretty de expresiones (estilo simple como en clase) ==========
    def _ppExpr(self, ectx:CPPParser.ExprContext):
        cname = type(ectx).__name__
        # unario
        if cname.endswith("ExprUnary"):
            op = ectx.getChild(0).getText()
            return f"{op}{self._ppExpr(ectx.expr())}"
        # ++i / i++
        if cname.endswith("ExprPreIncDec"):
            return f"{ectx.getChild(0).getText()}{ectx.ID().getText()}"
        if cname.endswith("ExprPostIncDec"):
            return f"{ectx.ID().getText()}{ectx.getChild(1).getText()}"
        # binarios
        if cname.endswith("ExprMulDiv") or cname.endswith("ExprAddSub") \
           or cname.endswith("ExprRel") or cname.endswith("ExprEq") \
           or cname.endswith("ExprAnd") or cname.endswith("ExprOr"):
            left = self._ppExpr(ectx.expr(0))
            op   = ectx.getChild(1).getText()
            right= self._ppExpr(ectx.expr(1))
            return f"{left} {op} {right}"
        # paréntesis
        if cname.endswith("ExprPar"):
            return f"({self._ppExpr(ectx.expr())})"
        # literal / var
        if cname.endswith("ExprLiteral"):
            return self._ppLit(ectx.literal())
        if cname.endswith("ExprVar"):
            return ectx.ID().getText()
        # fallback
        return ectx.getText()

    def _ppLit(self, lctx:CPPParser.LiteralContext):
        if lctx.INT():    return lctx.INT().getText()
        if lctx.DOUBLE(): return lctx.DOUBLE().getText()
        if lctx.BOOL():   return "verdadero" if lctx.BOOL().getText()=="true" else "falso"
        if lctx.STRING(): return lctx.STRING().getText()  # deja comillas
        return lctx.getText()
```
### 5. Programa de prueba (ejem.upc)
```bash
%%writefile ejem.upc
int x = 0;
int y;
for (int i = 0, j = 2; i < j; i++, --j) {
  if (i == 1) cout << "ok" << i;
  else x += i;
}
x = x + 3;
while (x > 0) { x--; }
cin >> x >> y;
```
### 6. Ejecución del compilador
```bash
input_stream = FileStream('ejem.upc')
lexer = CPPLexer(input_stream)
token_stream = CommonTokenStream(lexer)
parser = CPPParser(token_stream)
tree = parser.prog()
visitor = Visitor()
visitor.visit(tree)
```
