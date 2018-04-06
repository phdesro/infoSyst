# infoSyst

http://homepages.laas.fr/ealata/Projet_Syst_Info_2018.pdf

## TODO:
### Urgent:
* if/else
* while
* function
* express arithm
* err de base
### plus tard:
* déclaration fonction imbriquée
* erreur approfondi
* jit (?)
* typessss
* pointeurs
* structures
* tableaux
* pp

## Tableau de symbol:
Pour introduire un nouveau type, à faire 4 étapes:

1. 
```c
// symbol.h
typedef enum {/*...*/, s_montype} TypeSymbol; // définir le nouveau symbol
```

2.
```c
// symbol.c
int sizeSymbol(Symbol* symbol)	{
	switch(symbol->type)	{
		//...
		case s_montype: 	return /* size */;
		//...
	}
}

char * typeToString(TypeSymbol type)	{
	switch(type)	{
		//...
		case s_montype:
			return "montype";	// ceci est pour l'affichage du tableau de caractère
		//...
	}
}
```

3.
```
/* compiler.l */
montoken		{
				yylval.lxType = s_montype;
				return tTOKEN; 
			}
```

4.
```
/* compiler.y */
/*...*/
%token tCONST ... tTOKEN
/*...*/
%type <lxType> ... tTOKEN ...
/*...*/
Type:	tINT 
		| ...
		| tTOKEN
		| tFLOAT { $$ = $1; };
			}
```

Vérifier avec `make test`

## Note du cours:

----------- $$ ------------
E <- E + E
E <- E * E
E <- id
E <- nb

Préciser la réduction:
%left tADD tMUL
%left tMUL tDIV

----------- $$ ------------

chaque déclaration de var, on mémorise en mémoire. Pour pouvoir gérer la cohérence entre variables et sa valeur dans l'espace mémoire :
asso id->@ : tab de symbols

tab:
 ____________________________________
|@			id		type		depth
|====================================
|0			i		int			1
|255		j		int			1
|128		k		int			1
|61			k		int 		2		// surcharge de var

----------- $$ ------------

Aff:
	id		=		E		;
E:
	nb

E -> nb { $$ = $1 }		// $ == E

Bien si fait l'optim directement de ligne par ligne. Mais face au prob suivant:

E <- E + E { "ADD" $1 $3}
=> Si E est un nb mais pas un registre : pas possible

Solution: $1 -> dans un registre et puis retourne ce registre

----------- $$ ------------

Hypothèse : 
	[1] TS == pile (une "{" correpond à "}" )
	[2] utilisation de variable temporaire (partout)
		E: id = E
			____|____
			|	|	|
			E	+	E
		Il faut considérer le E en haut soit dans un plus grande opération id = E * E
		Donc mettre le résultat de E + E dans un var tmp

[2] Stratégie sera comme la suite:
E -> nb {
	int adr_tmp = ts_new_tmp();
		/* mem */
	printf("AFC r0 %d\n", $1);
	printf("STORE %d r0\n, adr_tmp);
}

E -> E + E {
	// E(1) et E (2) var tmp => on affecte le résultat dans un et libère l'autre
	printf("LOAD r0 %d\n", last_tmp());
	printf("LOAD r1 %d\n", last_tmp() -1 );
	printf("ADD %d );
	... ("STORE %d R0", last_tmp() -1);
	... free_tmp();
}

----------- $$ ------------
Problème de registre: On a que 3 reg max R0 1 2
Si on doit réaliser une opération de plusieurs variables -> niqué (a = b + c + d + e + d + f;)
=> Entregistre en mémoire : LOAD, STORE __

Exemple: avec 3 lignes:
int i;
int j = 2;
i = j + 1;

En yacc:
decl: tINT tID




