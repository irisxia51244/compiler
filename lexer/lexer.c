/* The lexical analyzer for the C-- Programming Language
 */
// TODO: you are welcome to completely wipe out the contents of this
// file and start from scratch

#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"



// these are likely values that will be needed by the parser, so 
// making them global variables is okay
char lexbuf[MAXLEXSIZE];  // stores current lexeme
int  tokenval=0;          // stores current token's value
                          // (may not used for every token)
int  src_lineno=1;        // current line number in source code input
char* KEY[10] = {"return","read","write","writeln","break","if","else",
    "while","int","char"};
// function prototypes:
//static void print_lineno();  // static limits its scope to only in this .c file

/*
 * when first char is letter, return KEYWORD or ID
 */
static int alpha(int c, FILE *fd){
    //while next char is '_' or letter or digit, store it and check the next
    int i = 0;
    lexbuf[i] = c;
    i = i + 1;
    c = getc(fd);
    while(c == '_' || isalnum(c)!=0){
        lexbuf[i] = c;
        i = i + 1;
        c = getc(fd);
        
    }
    //after the loop, c is not '_' or letter or digit
    //store the token value
    //printf("%d\n",tokenval);
    tokenval = (int)lexbuf;
    //printf("%d\n",tokenval);
    //put-back one char
    c = ungetc(c,fd);
    int k;
    //check whether it is a keyword
    if((k = strcmp(lexbuf,KEY[0]))==0){
        return RETURN;
    }
    else if((k = strcmp(lexbuf,KEY[1]))==0){
        return READ;
    }
    else if((k = strcmp(lexbuf,KEY[2]))==0){
        return WRITE;
    }
    else if((k = strcmp(lexbuf,KEY[3]))==0){
        return WRITELN;
    }
    else if((k = strcmp(lexbuf,KEY[4]))==0){
        return BREAK;
    }
    else if((k = strcmp(lexbuf,KEY[5]))==0){
        return IF;
    }
    else if((k = strcmp(lexbuf,KEY[6]))==0){
        return ELSE;
    }
    else if((k = strcmp(lexbuf,KEY[7]))==0){
        return WHILE;
    }
    else if((k = strcmp(lexbuf,KEY[8]))==0){
        return INT;
    }
    else if((k = strcmp(lexbuf,KEY[9]))==0){
        return CHAR;
    }
    //if not, return as an identifier
    //printf("%s\n",lexbuf);
    
    return ID;
}

/*
 * when first char is digit, return NUM
 */
static int digit(int c, FILE *fd){
    //while next char is digit, store it and check the next
    int i = 0;
    lexbuf[i]=c;
    i = i+1;
    c = getc(fd);
    while(isdigit(c) != 0){
        lexbuf[i] = c;
        i = i + 1;
        c = getc(fd);
    }
    //after the loop, c is not a digit
    //store the token value
    tokenval = (int)lexbuf;
    //put-back one char
    c = ungetc(c,fd);
    return NUM;
}

/*
 * when first char is quote, if there is only one char inside, return NUM;
 */
static int quote(int c, FILE *fd){
    //record all the chars before the next '"'
    int i = 0;
    lexbuf[i]=c;
    i = i+1;
    c = getc(fd);
    //while not next '''
    while(c != '\''){
        //if can not find '"' or exceed the maxlexsize, return error
        if(c == EOF || i >= MAXLEXSIZE){
            return LEXERROR;
        }
        //else, save the char
        else{
            lexbuf[i] = c;
            i = i + 1;
            c = getc(fd);
        }
    }
    //after the loop, c is '"'
    //store the token value
    lexbuf[i]=c;
    tokenval = (int)lexbuf;
    //c = getc(fd);
    return NUM;

}



/***************************************************************************/
/*
 *  Main lexer routine:  returns the next token in the input
 *
 *  param fd: file pointer for reading input file (source C-- program)
 *            TODO: you may want to add more parameters
 *
 *  returns: the next token or 
 *           DONE if there are no more tokens 
 *           LEXERROR if there is a token parsing error 
 */
int lexan(FILE *fd) {
    memset(lexbuf,0,MAXLEXSIZE);
    //get the first char
    int c = getc(fd);
    //iterate while not at the end of the file
    while(c!=EOF){
        //printf("%c\n",c);
        //if char is '\n', increments the line
        if(c == '\n'||c == '\r'){
            src_lineno = src_lineno + 1;
            //printf("2.%d\n",src_lineno);
            c = getc(fd);
            continue;
        }
        //if char is other white space char, skip it
        else if(c == ' '||c == '\t'||c == '\f'||c == '\r'||c == '\v'){
            //printf("is space\n");
            c = getc(fd);
            continue;
        }
        //if char is '_' or letter
        else if(isalpha(c)!=0||c == '_'){
            return alpha(c, fd);
        }
        
        //if char is digit
        else if(isdigit(c)){
            return digit(c,fd);
        }
        
        //if char is '\''
        else if(c == '\''){
            return quote(c,fd);
        }
        
        //if char is a punctuation
        else if(ispunct(c)){
            //if it is a comment
            if(c == '/'){
                //printf("/\n");
                //get the next char
                c = getc(fd);
                //if it is a single line comment
                if(c == '/'){
                    //printf("/\n");
                    //skip all the chars up to '\n'
                    c = getc(fd);
                    while(c != '\n' && c != EOF && c != '\r'){
                        c = getc(fd);
                   }
                    
                    //after the loop, c is '\n'
                    src_lineno = src_lineno + 1;
                    //printf("3.%d\n",src_lineno);
                   
                    //printf("is single line comment\n");
                    c = getc(fd);
                    continue;
                }
                //if it is a several lines comment
                else if(c == '*'){
                    //printf("the punct is.%c\n",c);
                    c = getc(fd);
                    //skip all the chars up to next
                    while(c != '*' && c != EOF){
                        if(c == '\n' || c == '\r'){
                            src_lineno = src_lineno + 1;
                             //printf("4.%d\n",src_lineno);
                        }
                        c = getc(fd);
                    }
                    //find the next , skip them
                    c = getc(fd);
                    if(c == '/'){
                        c = getc(fd);
                        continue;
                    }
                    //if cannot find, reprot error
                    else{
                        return LEXERROR;
                    }
                    
                }
                else{
                    c = ungetc(c,fd);
                    lexbuf[0] = c;
                    tokenval = (int)lexbuf;
                    return DIV;
                }
        
        }
        
            //if it is a operator
            //+
            else if(c == '+'){
                lexbuf[0] = c;
                tokenval = (int)lexbuf;
                return PLUS;
            }
            else if(c == '-'){
                lexbuf[0] = c;
                tokenval = (int)lexbuf;
                return MINUS;
            }
            else if(c == '*'){
                lexbuf[0] = c;
                tokenval = (int)lexbuf;
                return MULT;
            }
            //operators may with two chars
            //'!''!=' or '<''<=' or '>''>=' or '=''=='
            else if(c == '!'){
                lexbuf[0] = c;
                c = getc(fd);
                if(c == '='){
                    lexbuf[1] = c;
                    tokenval = (int)lexbuf;
                    c = getc(fd);
                    return NE;
                }
                else{
                    tokenval = (int)lexbuf;
                    return NOT;
                }
            }
            else if(c == '<'){
                lexbuf[0] = c;
                c = getc(fd);
                if(c == '='){
                    lexbuf[1] = c;
                    tokenval = (int)lexbuf;
                    return LE;
                }
                else{
                    tokenval = (int)lexbuf;
                    ungetc(c,fd);
                    return LT;
                }
            }
            else if(c == '>'){
                lexbuf[0] = c;
                c = getc(fd);
                if(c == '='){
                    lexbuf[1] = c;
                    tokenval = (int)lexbuf;
                    return GE;
                }
                else{
                    tokenval = (int)lexbuf;
                    ungetc(c,fd);
                    return GT;
                }
            }
            else if(c == '='){
                lexbuf[0] = c;
                c = getc(fd);
                if(c == '='){
                    lexbuf[1] = c;
                    tokenval = (int)lexbuf;
                    return EQ;
                }
                else{
                    tokenval = (int)lexbuf;
                    ungetc(c,fd);
                    return ASSIGN;
                }

            }

            //'||'
            else if(c == '|'){
                lexbuf[0] = c;
                c = getc(fd);
                
                if(c == '|'){
                    lexbuf[1] = c;
                    tokenval = (int)lexbuf;
                                       return OR;
                }
                else{
                    ungetc(c,fd);
                    return LEXERROR;
                }
            }
            else if(c == '&'){
                lexbuf[0] = c;
                c = getc(fd);
                
                if(c == '&'){
                    lexbuf[1] = c;
                    tokenval = (int)lexbuf;
                                       return AND;
                }
                else{
                    ungetc(c,fd);
                    return LEXERROR;
                }

            }
            //others
            else{
                
                lexbuf[0] = c;
                tokenval = (int)lexbuf;
                //c = getc(fd);
                if (c == ',') {
                    return COMMA;
                }
                else if(c == '{'){
                    return LBRACE;
                }
                else if(c == '['){
                    return LBRACK;
                }
                else if(c == '('){
                    return LPAREN;
                }
                else if(c == '}'){
                    return RBRACE;
                }
                else if(c == ']'){
                    return RBRACK;
                }
                else if(c == ')'){
                    return RPAREN;
                }
                else if(c == ';'){
                    return SEMI;
                }
                return LEXERROR;
            }
        
    }
        else{
            return LEXERROR;
        }

    }
                  return DONE;
   
    }




  // here is an example of how to use the debug macros defined in lexer.h
  //   uncomment #define DEBUG_LEXER, and recompile to see debug output 
  //   comment #define DEBUG_LEXER, and recompile to see debug output 
  //
 /* lexer_debug0("in lexan\n");
  lexer_debug1("in lexan, lineno = %d\n", src_lineno);
  lexer_debug1("in lexan, message = %s\n", "hello there");
*/
  // bogus code:
//  if(src_lineno < 5) {
//  src_lineno++;
//  return IF;
//  }
//  print_lineno();
//  return DONE;
//}
/***************************************************************************/
// A function for demonstrating that functions should be declared static
// if they are to be used only in the file in which they are defined.
// Static limits the scope to only this .c file
//static void print_lineno() {
  
// printf("line no = %d\n", src_lineno);

//}


