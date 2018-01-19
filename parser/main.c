/*
 *  Main function for C-- compiler: now launches parser and prints AST
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

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

void print_my_ast_node(ast_info *t);
void print_nltk_ast_node(FILE *out, ast_info *t); 

int main(int argc, char *argv[]) {

  FILE *fd = 0;

  if(argc != 2 && argc != 3) { 
    printf("usage: parser filename.c-- <nltk_outfile>\n");
    exit(1);
  }

  if(!(fd = fopen(argv[1], "rw")) ) {
    perror("no such file\n");
    exit(1);
  }

  // parser_init();  // if you need to init any global parser state
  
  parse(fd);
  printf("**********************************************\n");
  print_ast(ast_tree, print_my_ast_node);
  fclose(fd);

  // print AST in nltk format to output file
  // TODO: for a single node AST (only root) the output file is 
  //       not in correct format...once you add some child nodes, it
  //       will be fine)
  if(argc == 3) {
    if(!(fd = fopen(argv[2], "w")) ) {
      perror("no such file:\n");
    } else {
      create_nltk(fd, ast_tree, print_nltk_ast_node);
    }
    fclose(fd);
  }

  destroy_ast(&ast_tree);
  exit(0);     /*  successful termination  */
  
}
/*********************************************************************/

// this is an example of how to define output strings corresponding to 
// different ast node state that is used by the print_ast_node function:
static char *t_strings[] = {"AND","ASSIGN","break","char","COMMA","DIV","else","EQ","GE",
    "GT","id:","if","int","LBRACE","LBRACK","LE","LPAREN","LT",
    "MINUS","MULT","NE","NOT","num:","OR","PLUS","RBRACE","RBRACK","read","return","RPAREN",
    "SEMI","while","write","writeln"
};

static char *non_term_strings[] = {"PROGRAM","funcList","func_def","paramList","param","block","vardecList","vardec","stmtList","stmt","expr"};

//
// This is the function that is passed to print_ast, to print information
// that is stored in an ast node
//
// TODO: you will need to add more functionality than is currently here
//       and you may need to change what is here to match with the way you
//       defined tokens in your lexer implementation.
//
void print_my_ast_node(ast_info *t) {

  if(t != NULL) {
    if((t->token >= AND) && (t->token <= WRITELN)) {
       
      printf("%s", t_strings[(t->token)-1]);
      if((t->token == ID) || (t->token == NUM)){
            printf("%s",t->lexeme);
      }

    }
    else if (t->token == NONTERMINAL) {
       if((t->grammar_symbol >= PROGRAM)
          && (t->grammar_symbol <= expr)){
           printf("%s", non_term_strings[(t->grammar_symbol - PROGRAM)]);
       }
       else {
           printf("unknown grammar symbol %d", t->grammar_symbol);
       }
    }
    else {
      printf("unknown token %d", t->token);
    }
  }
  else {
    printf("NULL token\n");
  }
}
/*********************************************************************/
//
// This is the function that is passed to create_nltk, that prints out
// the AST in nltk format to a file
// (it will likely be identical to print_my_ast_node except that it
//  calls fprint to a file vs. printf to stdout)
// TODO: you will need to add more functionality than is currently here
//       and you may need to change what is here to match with the way you
//       defined tokens in your lexer implementation.
//
void print_nltk_ast_node(FILE *out, ast_info *t) {


  if(t != NULL) {
    if((t->token >= AND) && (t->token <= WRITELN)) {

      fprintf(out,"%s", t_strings[(t->token - 1)]);
	  if ((t->token == ID) || (t->token == NUM)) {
		  fprintf(out,"%s", t->lexeme);
	  }

    }
    else if (t->token == NONTERMINAL) {
       if((t->grammar_symbol >= PROGRAM)
           && (t->grammar_symbol <= expr))
       {
           fprintf(out,"%s", 
                non_term_strings[(t->grammar_symbol - PROGRAM)]);
       }
       else {
           fprintf(out,"unknown grammar symbol %d", t->grammar_symbol);
       }
    }
    else {
      fprintf(out,"unknown token %d", t->token);
    }
  }
  else {
    fprintf(out,"NULL token\n");
  }
}
