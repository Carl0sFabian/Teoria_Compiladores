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
class Visitor(CPPVisitor):
    def __init__(self):
        self.sangria = 0  # nivel de sangría

    def imprimir(self, texto):
        print(("  " * self.sangria) + texto)

    # program
    def visitProg(self, ctx: CPPParser.ProgContext):
        for ch in ctx.getChildren():
            if ch.getChildCount() > 0:
                self.visit(ch)
        return None

    # para actualizar sangría cuando se inicie un bloque de codigo
    def visitBlock(self, ctx: CPPParser.BlockContext):
        self.sangria += 1
        for ch in ctx.getChildren():
            if ch.getChildCount() > 0:  
                self.visit(ch)
        self.sangria -= 1
        return None

    # declaracion y asignacion de variables
    def visitDecl(self, ctx: CPPParser.DeclContext):
        tipo = ctx.decltype().getText()
        nombre = ctx.ID().getText()
        if ctx.expr() is not None:
            self.imprimir("Se declara " + tipo + " " + nombre + " con valor " + ctx.expr().getText())
        else:
            self.imprimir("Se declara " + tipo + " " + nombre)
        return None

    def visitAssign(self, ctx: CPPParser.AssignContext):
        self.imprimir("Se actualiza " + ctx.ID().getText() + " con " + ctx.expr().getText())
        return None

    def visitAugAssignStmt(self, ctx: CPPParser.AugAssignStmtContext):
        nombre_variable = ctx.ID().getText()
        operador_compuesto = ctx.getChild(1).getText()  # "+=", "-=", "*=", "/=", "%="
        valor = ctx.expr().getText()

        simbolo = "+"
        if operador_compuesto == "-=":
            simbolo = "-"
        elif operador_compuesto == "*=":
            simbolo = "*"
        elif operador_compuesto == "/=":
            simbolo = "/"
        elif operador_compuesto == "%=":
            simbolo = "%"

        self.imprimir("Se actualiza " + nombre_variable + ": " + nombre_variable + " = " + nombre_variable + " " + simbolo + " " + valor)
        return None

    def visitIncDecStmt(self, ctx: CPPParser.IncDecStmtContext):
        nombre = ctx.ID().getText()
        op = ctx.getChild(1).getText()  # "++" o "--"
        if op == "++":
            self.imprimir("Se aumenta " + nombre + " en 1")
        else:
            self.imprimir("Se disminuye " + nombre + " en 1")
        return None

    # cout y cin
    def visitCoutStmt(self, ctx: CPPParser.CoutStmtContext):
        texto = "Se muestra: "
        primero = True
        l = list(ctx.getChildren())
        i = 0
        while i < len(l):
            tok = l[i].getText()
            if tok == "<<" and i + 1 < len(l):
                if not primero:
                    texto = texto + " , "
                texto = texto + l[i + 1].getText()  
                primero = False
                i = i + 2
            else:
                i = i + 1
        self.imprimir(texto)
        return None

    def visitCinStmt(self, ctx: CPPParser.CinStmtContext):
        texto = "Se solicitan valores para: "
        primero = True
        l = list(ctx.getChildren())
        i = 0
        while i < len(l):
            tok = l[i].getText()
            if tok == ">>" and i + 1 < len(l):
                if not primero:
                    texto = texto + ", "
                texto = texto + l[i + 1].getText() 
                primero = False
                i = i + 2
            else:
                i = i + 1
        self.imprimir(texto)
        return None

    def visitExprStmt(self, ctx: CPPParser.ExprStmtContext):
        mensaje = self.visit(ctx.expr())
        if mensaje is not None:
            self.imprimir(mensaje)
        else:
            self.imprimir("Se calcula: " + ctx.expr().getText())

    def visitExprUnary(self, ctx: CPPParser.ExprUnaryContext):
        l = list(ctx.getChildren())    # ('!'| '+'| '-') expr
        op = l[0].getText()
        sub = l[1].getText()
        if op == '!':
            return "Se niega " + sub
        elif op == '+':
            return "Se aplica signo positivo a " + sub
        else:  # '-'
            return "Se aplica signo negativo a " + sub

    def visitExprPreIncDec(self, ctx: CPPParser.ExprPreIncDecContext):
        l = list(ctx.getChildren())          # ('++'|'--') expr
        op = l[0].getText()
        var = l[1].getText()
        if op == '++':
            return "Se aumenta " + var + " en 1"
        else:
            return "Se disminuye " + var + " en 1"

    def visitExprPostIncDec(self, ctx: CPPParser.ExprPostIncDecContext):
        l = list(ctx.getChildren())          # expr ('++'|'--')
        var = l[0].getText()
        op  = l[1].getText()
        if op == '++':
            return "Se aumenta " + var + " en 1"
        else:
            return "Se disminuye " + var + " en 1"

    def visitExprEq(self, ctx: CPPParser.ExprEqContext):
        l = list(ctx.getChildren())          # expr ('=='|'!=') expr
        op = l[1].getText()
        op_txt = "igual a" if op == "==" else "distinto de"
        return "Se compara: " + l[0].getText() + " " + op_txt + " " + l[2].getText()

    def visitExprAnd(self, ctx: CPPParser.ExprAndContext):
        l = list(ctx.getChildren())          # expr '&&' expr
        left_txt  = l[0].getText()
        right_txt = l[2].getText()
        return "Se evalúa (" + left_txt + ") y (" + right_txt + ")"

    def visitExprOr(self, ctx: CPPParser.ExprOrContext):
        l = list(ctx.getChildren())          # expr '||' expr
        left_txt  = l[0].getText()
        right_txt = l[2].getText()
        return "Se evalúa (" + left_txt + ") o (" + right_txt + ")"


    # if
    def visitIfStmt(self, ctx: CPPParser.IfStmtContext):
        condicion = ctx.expr().getText() if ctx.expr() is not None else ""
        self.imprimir("Si " + condicion + ", se realiza lo siguiente:")
        self.sangria += 1
        self.visit(ctx.stmt(0))
        self.sangria -= 1
        if len(ctx.stmt()) > 1:
            self.imprimir("Si no, se realiza lo siguiente:")
            self.sangria += 1
            self.visit(ctx.stmt(1))
            self.sangria -= 1
        self.imprimir("Fin del si")
        return None

    # while
    def visitWhileStmt(self, ctx: CPPParser.WhileStmtContext):
        condicion = ctx.expr().getText() if ctx.expr() is not None else ""
        self.imprimir("Mientras " + condicion + ", se repite:")
        self.sangria += 1
        self.visit(ctx.stmt())
        self.sangria -= 1
        self.imprimir("Fin del mientras")
        return None

    # for
    def visitForStmt(self, ctx: CPPParser.ForStmtContext):
        txt_init = ""
        if ctx.forInit() is not None:
            txt_init = self.forInitText(ctx.forInit())

        txt_cond = ""
        if ctx.forCond() is not None:
            txt_cond = ctx.forCond().expr().getText()

        txt_post = ""
        if ctx.forPost() is not None:
            txt_post = self.forPostText(ctx.forPost())

        if txt_init == "":
            txt_init = "—"
        if txt_cond == "":
            txt_cond = "—"
        if txt_post == "":
            txt_post = "—"

        self.imprimir("Se ejecuta un ciclo para ( inicialización: " + txt_init +
                      " ; condición: " + txt_cond +
                      " ; actualización: " + txt_post + " ):")
        self.sangria += 1
        self.visit(ctx.stmt())
        self.sangria -= 1
        self.imprimir("Fin del para")
        return None


    # partes del for: inicializacion, condicion, actualizacion
    def forInitText(self, ctx: CPPParser.ForInitContext):
        if ctx.decltype() is not None:
            tipo = ctx.decltype().getText()
            texto = ""
            primera = True
            l = list(ctx.getChildren())
            i = 0
            while i < len(l):
                tok = l[i].getText()
                if tok == tipo or tok == ",":
                    i = i + 1
                    continue
                if tok == "=":
                    if i + 1 < len(l):
                        texto = texto + " con " + l[i + 1].getText()
                        i = i + 2
                        continue
                if not primera:
                    texto = texto + " , "
                texto = texto + "se declara " + tipo + " " + tok
                primera = False
                i = i + 1
            return texto

        texto = ""
        primero = True
        actual = ""
        for hijo in ctx.getChildren():
            tok = hijo.getText()
            if tok == ",":
                if primero:
                    texto = texto + actual
                    primero = False
                else:
                    texto = texto + " , " + actual
                actual = ""
            else:
                actual = actual + tok
        if actual != "":
            if primero:
                texto = texto + actual
            else:
                texto = texto + " , " + actual
        return texto

    def forPostText(self, ctx: CPPParser.ForPostContext):
        texto = ""
        primero = True
        actual = ""
        for ch in ctx.getChildren():
            tok = ch.getText()
            if tok == ",":
                if primero:
                    texto = texto + actual
                    primero = False
                else:
                    texto = texto + " , " + actual
                actual = ""
            else:
                actual = actual + tok
        if actual != "":
            if primero:
                texto = texto + actual
            else:
                texto = texto + " , " + actual
        return texto
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
