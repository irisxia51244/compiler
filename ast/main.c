//
// An example program that uses the ast library.
// This builds the ast top-down, however, when you build an ast
// as part of the parsing step, you will be building it from the
// leaf nodes up.
//
// (thanks to Tia Newhall)
//
#include <stdio.h>
#include <stdlib.h>
#inclde "lexer.h"
#include "ast.h"

typedef enum {
	STARTTOKEN,
	AND,
	ASSIGN,
	BREAK,
	CHAR,
	COMMA,
	DIV,
	ELSE,
	EQ,
	GE,
	GT,
	ID,
	IF,
	INT,
	LBRACE,
	LBRACK,
	LE,
	LPAREN,
	LT,
	MINUS,
	MULT,
	NE,
	NOT,
	NUM,
	OR,
	PLUS,
	RBRACE,
	RBRACK,
	READ,
	RETURN,
	RPAREN,
	SEMI,
	WHILE,
	WRITE,
	WRITELN,
	DONE,
	ERROR = -1,
	ENDTOKEN
} tokenT;
#define NONTERM 100 
#define PROGRAM 101
#define funcList 102
#define func_def 103
#define paramList 104
#define param 105
#define block 106
#define vardeclList 107
#define vardec 108
#define stmtList 109
#define stmt 110
#define expr 111
#define PROGRAMSTR "PROGRAM"
#define funcListSTR "funcList"
#define func_defSTR "func_def"
#define paramListSTR "paramList"
#define paramSTR "param"
#define blockSTR "block"
#define vardeclListSTR "vardecList"
#define vardecSTR "vardec"
#define stmtListSTR "stmtList"
#define stmtSTR "stmt"
#define exprSTR "expr"

static char *token_strings[] = {
						"&&","=","break","char",",","/","else","==",">=",
						">","ID","if","int","num","{","[","<=","(","<",
						"-","!=","!","||","+","}","]","read","return",")",
						";","while","write","writeln"
                };

void print_token(ast_info *t);

int main(int argc, char *argv[]) {

  ast atree;
  int i, j, k, p;
  ast_info *s;
  ast_node *n;
  char lexeme[MAX_LEXEME_SIZE];

  // create and init new ast node
  s = create_new_ast_node_info(NONTERM, 0, PROGRAM, 0, 0);
  n = create_ast_node(s);
  init_ast(&atree, n);

  for(i=0; i < 3; i++) {
        sprintf(lexeme, "t_%d", i);  
        s = create_new_ast_node_info(i, i, NONE,lexeme,0);
        n = create_ast_node(s);
        if(s == NULL || n==NULL) { printf("ERROR token create\n"); exit(1); }
        add_child_node(atree.root, n);
  }

  for(i=0; i < 3; i++) {
    for(j=0; j < 8; j++) {
        sprintf(lexeme, "t_%d_%d", i,j);  
        s = create_new_ast_node_info(j, i*10+j, NONE, lexeme, 0);
        n = create_ast_node(s);
        if(s == NULL || n==NULL) { printf("ERROR token create\n"); exit(1); }
        add_child_node((atree.root->childlist[i]), n);

        for(k=0; k < 5; k++) {
          sprintf(lexeme, "t_%d_%d_%d", i,j,k);  
          s = create_new_ast_node_info(k, (i*100)+j*10+k, NONE, lexeme, 0);
          n = create_ast_node(s);
          if(s==NULL || n==NULL) { printf("ERROR token create\n"); exit(1); }
          add_child_node((atree.root->childlist[i]->childlist[j]), n);
          for(p=0; p < 4; p++) {
            sprintf(lexeme, "t_%d_%d_%d_%d", i,j,k,p);  
            s = create_new_ast_node_info(p,(i*1000+j*100+k*10+p),NONE,lexeme,0);
            n = create_ast_node(s);
            if(s==NULL || n==NULL){printf("ERROR token create\n"); exit(1);}
            // in a parser, you would be in a call to a parser function
            // that takes a pointer to the current ast node or to its
            // parent, so you would not have this really long string of .'s 
            // to access the right node to pass to add_child_node:
            add_child_node(
                atree.root->childlist[i]->childlist[j]->childlist[k], n);
          }
        }
    }
  }

  // let's just add another one that could be how you would 
  // add one for a non-terminal grammar symbol
  s = create_new_ast_node_info(NONTERM, 0, FUNCTION, 0, 0);
  n = create_ast_node(s);
  add_child_node(atree.root, n);
         
  print_ast(atree, print_token); 

  // clean up all malloced ast state
  destroy_ast(&atree); 
  exit(0);
}


//**********************************************************************
// This is a print function that is passed to the ast_print function.
// The user of the ast library provides this function since the
// particular tokens are defined by the user and will likely differ
// from one source to another...the ast library is more generic this
// way.  Your print function must have the same prototye as this one.
void print_token(ast_info *t) {

  if(t != NULL) {

    if((t->token < ENDTOKEN) && (t->token > STARTTOKEN)) {
        printf("%s:%d", token_strings[t->token], t->value); 
    }

    else if (t->token == NONTERM) {
      if(t->grammar_symbol == PROGRAM){
        printf("%s:%d", PROGRAMSTR, t->value);
      } else if(t->grammar_symbol == funcList){
        printf("%s:%d", funcListSTR, t->value);
      } else if(t->grammar_symbol == func_def){
	    printf("%s:%d", func_defSTR, t->value)
	  } else if(t->grammar_symbol == paramList){
		printf("%s:%d", paramListSTR, t->value)
	  } else if(t->grammar_symbol == param){
		printf("%s:%d", paramSTR, t->value)
	  } else if(t->grammar_symbol == block){
		printf("%s:%d", blockSTR, t->value)
	  } else if(t->grammar_symbol == vardeclList){
		printf("%s:%d", vardeclListSTR, t->value)
	  } else if(t->grammar_symbol == vardec){
		printf("%s:%d", vardecSTR, t->value)
	  } else if(t->grammar_symbol == stmtList){
		printf("%s:%d", stmtListSTR, t->value)
	  } else if(t->grammar_symbol == stmt){
		printf("%s:%d", stmtSTR, t->value)
	  } else if(t->grammar_symbol == expr){
		printf("%s:%d", exprSTR, t->value)
	  } else{
		  printf("unknown token");
	  }
    }
    else {
      printf("unknown token");
    }
  }
  else {
    printf("NULL token\n");
  }
  if(strlen(t->lexeme)) {
        printf(":%s", t->lexeme);
  }
}

