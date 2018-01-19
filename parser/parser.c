/*
 * parser.c: A Recursive Descent Parser for C--
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"


// TODO: you may completely wipe out or change the contents of this file; it
//       is just an example of how to get started on the structure of the 
//       parser program.

static void program(FILE *fd, ast_node *parent);

static void parser_error(char *err_string);

static void PROG(int token, FILE *fd, ast_node *parent);

static void PROG1(int token, FILE *fd, ast_node *parent);

static void PROG2(int token, FILE *fd, ast_node *parent);

static void FDL1(int token, FILE *fd, ast_node *parent);

static void FDL(int token, FILE *fd, ast_node *parent);

static void VDL(int token, FILE *fd, ast_node *parent);

static void VDL1(int token, FILE *fd, ast_node *parent);

static void PDL(int token, FILE *fd, ast_node *parent);

static void PDL1(int token, FILE *fd, ast_node *parent);

static void PDL2(int token, FILE *fd, ast_node *parent);

static void BLOCK(int token, FILE *fd, ast_node *parent);

static void StmtList(int token, FILE *fd, ast_node *parent);

static void StmtList1(int token, FILE *fd, ast_node *parent);

static void Stmt(int token, FILE *fd, ast_node *parent);

static void Expr(int token, FILE *fd, ast_node *parent);

static void E1(int token, FILE *fd, ast_node *parent);

static void E1b(int token, FILE *fd, ast_node *parent);

static void E2(int token, FILE *fd, ast_node *parent);

static void E2b(int token, FILE *fd, ast_node *parent);

static void E3(int token, FILE *fd, ast_node *parent);

static void E3b(int token, FILE *fd, ast_node *parent);

static void E4(int token, FILE *fd, ast_node *parent);

static void E4b(int token, FILE *fd, ast_node *parent);

static void E5(int token, FILE *fd, ast_node *parent);

static void E5b(int token, FILE *fd, ast_node *parent);

static void E6(int token, FILE *fd, ast_node *parent);

static void E6b(int token, FILE *fd, ast_node *parent);

static void E7(int token, FILE *fd, ast_node *parent);

static void E8(int token, FILE *fd, ast_node *parent);

static void E8b(int token, FILE *fd, ast_node *parent);

static void assign(int token, FILE *fd, ast_node *parent);

static void ExprList(int token, FILE *fd, ast_node *parent);

static void ELb(int token, FILE *fd, ast_node *parent);

static void match(int token, FILE *fd, ast_node *parent);

static void addtobuffer(ast_node *node);

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

int num_of_vardec;
int isBrack;
int lookahead;  // stores next token returned by lexer
                // you may need to change its type to match your implementation
int count; //count the used buffer
ast_node *buffer[50];
ast ast_tree;   // the abstract syntax tree

/**************************************************************************/
/*
 *  Main parser routine: parses the C-- program in input file pt'ed to by fd, 
 *                       calls the function corresponding to the start state,
 *                       checks to see that the last token is DONE,
 *                       prints a success msg if there were no parsing errors
 *  param fd: file pointer for input
 */
void parse(FILE *fd)  {
  // TODO: here is an example of what this function might look like, 
  //       you may completely change this:
  ast_info *s;
  ast_node *n;

  // create the root AST node
  s = create_new_ast_node_info(NONTERMINAL, 0, PROGRAM, 0, 0);
  n = create_ast_node(s);
  ast_node *parent = n;
  if(init_ast(&ast_tree, n)) {
        parser_error("ERROR: bad AST\n");
  }

  // lookahead is a global variable holding the next token
  // you could also use a local variable and then pass it to program
  lookahead = lexan(fd);
  count = 0;
  num_of_vardec = 0;
  isBrack = -1;
  printf("PROGRAM\n");
  program(fd, ast_tree.root);  // program corresponds to the start state
  PROG(lookahead, fd, parent);
  //add funcList ast subtree to root
  count = 0;
  //add funclist to program

  if (lookahead != DONE) {
	  parser_error("expected end of file");
  }
  else {
	  match(DONE, fd,parent);
  }

  }

  /*
  // the last token should be DONE

  */



static void addtobuffer(ast_node *node) {
	buffer[count] = node;
	count = count + 1;
}

static void PROG(int token, FILE *fd, ast_node *parent){
    //prog -> int id PROG1
    if(token == INT){
        match(INT,fd,parent);
        //if is ID
        if (lookahead == ID) {
            match(ID,fd,parent);
            PROG1(lookahead, fd, parent);
			//printf("PROG1\n");
        }
        //if not ID, report error
        else{
            parser_error("ERROR: missing ID after type int");
        }
    }
    //prog -> char id PROG1
    else if(token == CHAR) {
		match(CHAR, fd, parent);
        //if is id
        if (lookahead == ID) {
            match(ID,fd,parent);
            PROG1(lookahead, fd, parent);
        }
        //if not ID, report error
        else{
            parser_error("ERROR: missing ID after type char");
        }
    }
    //else, report error
    else{
        parser_error("ERROR: Wrong start symbol");
    }
}

static void PROG1(int token, FILE *fd, ast_node *parent){
    if (token == SEMI) {
        match(SEMI,fd, parent);
		//create vardec node
		ast_info *vdinfo;
		ast_node *vdnode;
		vdinfo = create_new_ast_node_info(NONTERMINAL, 0, vardec, 0, src_lineno);
		vdnode = create_ast_node(vdinfo);
		//add type and id to vdnode
		add_child_node(vdnode, buffer[count - 2]);
		add_child_node(vdnode, buffer[count - 1]);
		printf("add vd to vdnode\n");
		count = 0;
		//add vdnode to root
		add_child_node(parent, vdnode);
		printf("add vdnode to root\n");
		PROG(lookahead, fd, parent);
    }
    //PROG1 -> [num];PROG
    else if(token == LBRACK){
	
        match(LBRACK,fd,parent); 
        //if next token is num, continue
        if(lookahead == NUM){
            match(NUM, fd,parent); 
            if(lookahead == RBRACK){
                match(RBRACK, fd, parent);
                //if next token is SEMI, continue
                if (lookahead == SEMI) {
					match(SEMI, fd, parent);
					//create vardec node
					ast_info *vdinfo;
					ast_node *vdnode;
					vdinfo = create_new_ast_node_info(NONTERMINAL, 0, vardec, 0, src_lineno);
					vdnode = create_ast_node(vdinfo);
					//add type and id to vdnode
					add_child_node(vdnode, buffer[count - 5]);
					add_child_node(vdnode, buffer[count - 4]);
					add_child_node(vdnode, buffer[count - 3]);
					add_child_node(vdnode, buffer[count - 2]);
					add_child_node(vdnode, buffer[count - 1]);
					printf("add vd to vdnode\n");
					count = 0;
					//add vdnode to root
					add_child_node(parent, vdnode);
					printf("add vdnode to root\n");
			
                    PROG(lookahead, fd, parent);
                }
                //else, report error
                else{
                    parser_error("ERROR: missing ; after ]");
                }
            }
            //else, report error
            else{
                parser_error("ERROR: missing ] after NUM");
            }
        }
		else {
			parser_error("ERROR: missing NUM after [");
		}
    }
	//PROG1->PROG2
	else if (token == LPAREN) {
		//add funcdeflist node to root
		ast_info *fdlinfo;
		ast_node *fdlnode;
		fdlinfo = create_new_ast_node_info(NONTERMINAL, 0, funcList, 0, src_lineno);
		fdlnode = create_ast_node(fdlinfo);
		add_child_node(parent, fdlnode);
		printf("add fdlnode to root\n");

		PROG2(lookahead, fd, fdlnode);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for PROG1");
	}
}

static void PROG2(int token, FILE *fd, ast_node *parent){
	//PROG2 -> (FDL1
	if (token == LPAREN) {
		match(LPAREN, fd, parent);
		FDL1(lookahead, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing ( for PROG2");
	}
}

static void FDL1(int token, FILE *fd, ast_node *parent){
    //FDL1 -> PDL){BLOCK FDL
	if (token == INT || token == CHAR || token == RPAREN) {
		//create new fundef node and add to fundeflist
		ast_info *fdinfo;
		ast_node *fdnode;
		fdinfo = create_new_ast_node_info(NONTERMINAL, 0, func_def, 0, src_lineno);
		fdnode = create_ast_node(fdinfo);
		add_child_node(parent, fdnode);
		printf("add fdnode to fclnode\n");
		//add type and id to fdnode
        int i;
        for(i = 0; i < count;i++){
            add_child_node(fdnode,buffer[i]);
        }
		printf("add type id fdnode\n");
		count = 0;
		PDL(token, fd, fdnode);
		//if num of param > 0, create paramlist node
		if (count > 0) {
			ast_info *pmlinfo;
			ast_node *pmlnode;
			pmlinfo = create_new_ast_node_info(NONTERMINAL, 0, paramList, 0, src_lineno);
			pmlnode = create_ast_node(pmlinfo);
			add_child_node(fdnode, pmlnode);
			printf("add pmlnode to fdnode\n");
			//add param to paramlist
			int i;
			for (i = 0; i < count; i= i+1) {
				add_child_node(pmlnode,buffer[i]);
			}
			count = 0;
		}

		//if next token is ),continue
		if(lookahead == RPAREN){
	
			
			match(RPAREN, fd, parent);
			//if next token is {, continue
			if (lookahead ==  LBRACE) {
				match(LBRACE, fd, parent);
				//create block node
				ast_info  *blinfo;
				ast_node  *blnode;
				blinfo = create_new_ast_node_info(NONTERMINAL,0,block,0,src_lineno);
				blnode = create_ast_node(blinfo);
				add_child_node(fdnode, blnode);
				printf("add blnode to fdnode\n");
				BLOCK(lookahead, fd, blnode);
				count = 0;
                printf("start finding FDL");
				FDL(lookahead, fd, parent);
			}
			//else, report error
			else {
				parser_error("ERROR: missing { in FDL1");
			}
		}
		//else, report error
		else {
			parser_error("ERROR: missing ) in FDL1 ");
		}
	}
	//else, report error
	else {
		parser_error("ERROR: missing INT or CHAR or RPAREN for FDL1");
	}
}

static void FDL(int token, FILE *fd, ast_node *parent) {
	//FDL - > int id (FDL1
	if (token == INT) {
		match(INT, fd, parent);
        printf("int found");
		//if next token is id, continue
		if (lookahead == ID) {
			match(ID, fd, parent);
			//if next token is (, continue
			if (lookahead == LPAREN) {
				
				match(LPAREN, fd, parent);
				FDL1(lookahead,fd,parent);
			}
			//else, report error
			else {
				parser_error("ERROR: missing ( after id");
			}
		}
		//else, report error
		else {
			parser_error("ERROR: missing ID after INT");
		}
	}
	//FDL -> char id (FDL1
	else if (token == CHAR) {
		match(INT, fd, parent);
		//if next token is id, continue
		if (token == ID) {
			match(ID, fd, parent);
			//if next token is (, continue
			if (lookahead == LPAREN) {
			
				match(LPAREN, fd, parent);
				FDL1(lookahead,fd,parent);
			}
			//else, report error
			else {
				parser_error("ERROR: missing ( after id");
			}
		}
		//else, report error
		else {
			parser_error("ERROR: missing ID after CHAR");
		}
	}
	//FDL -> epsilon
	else if (token == DONE) {
        //add fun_def sub tree to funcList sub tree
        //create fun_def
    

	}
    else{
       parser_error("ERROR: missing token for FDL");
    }
}

static void VDL(int token, FILE *fd, ast_node *parent){
    
	//VDL -> int id VDL1
	if (token == INT) {
        
		match(INT, fd, parent);
		//if next token is id, continue
		if (lookahead == ID) {
			match(ID, fd, parent);
			VDL1(lookahead,fd,parent);
		}
		//else, report error
		else {
			parser_error("ERROR: missing ID after INT");
		}
	}
	//VDL -> char id VDL1
	else if (token == CHAR) {
		match(CHAR, fd, parent);
		//if next token is id, continue
		if (lookahead == ID) {
			match(ID, fd, parent);
			VDL1(lookahead,fd,parent);
		}
		//else, report error
		else {
			parser_error("ERROR: missing ID after CHAR");
		}
	}
	//VDL -> epsilon
	else if(token == SEMI || token == LBRACE || token == LPAREN ||token == MINUS||token == NOT||token == RETURN ||token == READ||token == WRITE||token ==WRITELN||token == BREAK || token == IF ||  token == WHILE || token == NUM || token == ID){
	}
    //else, report error
    else{
        parser_error("ERROR: missing token for VDL");
    }
}

static void VDL1(int token, FILE *fd, ast_node *parent){
    //VDL1 -> ;VDL
	if (token == SEMI) {
		match(SEMI, fd, parent);
		//num_of_vardec = num_of_vardec + 1;
		//add type id to vardec;
		ast_info *vdinfo;
		ast_node *vdnode;
		vdinfo = create_new_ast_node_info(NONTERMINAL, 0, vardec, 0, src_lineno);
		vdnode = create_ast_node(vdinfo);
		add_child_node(vdnode, buffer[count - 2]);
		add_child_node(vdnode, buffer[count - 1]);
		printf("add vd to vdnode\n");
		count = count - 2;
		addtobuffer(vdnode);
		printf("add vdnode to buffer\n");
		VDL(lookahead,fd,parent);
	}
	//VDL1 -> [num];VDL
	else if (token == LBRACK) {
		
		match(LBRACK, fd, parent);

		
		if(lookahead == NUM){
			match(NUM, fd, parent);
			
			if (lookahead == RBRACK) {
				match(RBRACK, fd, parent);
				
				if (lookahead == SEMI) {
                   	num_of_vardec = num_of_vardec + 1;
					match(SEMI, fd, parent);
					ast_info *vdinfo;
					ast_node *vdnode;
					vdinfo = create_new_ast_node_info(NONTERMINAL, 0, vardec, 0, src_lineno);
					vdnode = create_ast_node(vdinfo);
					add_child_node(vdnode, buffer[count - 5]);
					add_child_node(vdnode, buffer[count - 4]);
					add_child_node(vdnode, buffer[count - 3]);
					add_child_node(vdnode, buffer[count - 2]);
					add_child_node(vdnode, buffer[count - 1]);
					printf("add vd to vdnode\n");
                    printf("%d\n",count);
					count = count - 5;
                    printf("%d\n",count);
					addtobuffer(vdnode);
					printf("add vdnode to buffer\n");
					VDL(lookahead,fd,parent);
					printf("VarDeclList\n");
				}
				//else, report error
				else {
					parser_error("ERROR: missing ; after ]");
				}
			}
			//else, report error
			else {
				parser_error("ERROR: missing ] after NUM");
			}
		}
		//else, report error
		else{
			parser_error("ERROR: missing NUM after [");
		}
	}
	//else, report error
	else {
		parser_error("ERROR: missing ; or [ for VDL1");
	}
}

static void PDL(int token, FILE *fd, ast_node *parent){
	//PDL -> char id PDL1
	if (token == CHAR) {
		//create char node
		//add to paramDeclList node
        match(CHAR, fd, parent);
        //if next token is id, continue
        if(lookahead == ID){
			//create add node
			//add to paramDeclList node
            match(ID, fd, parent);
            PDL1(lookahead,fd,parent);
        }
        //else, report error
        else{
            parser_error("ERROR: missing ID after CHAR");
        }

	}
	//PDL -> int id PDL1
	else if (token == INT) {
        match(INT, fd, parent);
        //if next token is id, continue
        if(lookahead == ID){
            match(ID, fd, parent);
            PDL1(lookahead,fd,parent);
        }
        //else, report error
        else{
            parser_error("ERROR: missing ID after INT");
        }
	}
	//epsilon
	else if(token == RPAREN){
	}
    //report error
    else{
        parser_error("ERROR: missing token for PDL");
    }
    
}

static void PDL1(int token, FILE *fd, ast_node *parent){
	printf("PDL1\n");
    //PDL1 -> [] PDL2
    if(token == LBRACK){

        match(LBRACK,fd,parent);
		//add lbrack to pdNode
        //if next token is ], continue
        if(lookahead == RBRACK){
            match(RBRACK, fd, parent);
			isBrack = 1;
            PDL2(lookahead,fd,parent);
        }
        //else, report error
        else{
            parser_error("ERROR: missing ] after [");
        }
    }
    //PDL1 -> PDL2
    else if(token ==  COMMA || token == RPAREN){

        PDL2(token, fd, parent);
    }
    else{
        parser_error("ERROR: missing [ or , for PDL1");
    }
}

static void PDL2(int token, FILE *fd, ast_node *parent){
	printf("PDL2\n");
    //PDL2 -> , PDL
    if(token == COMMA){
		
        match(COMMA,fd,parent);
		//create pdnode
		//add to pdnode
		ast_info *pminfo;
		ast_node *pmnode;
		pminfo = create_new_ast_node_info(NONTERMINAL, 0, param, 0, src_lineno);
		pmnode = create_ast_node(pminfo);
		if (isBrack == 1) {
			add_child_node(pmnode, buffer[count - 4]);
			add_child_node(pmnode, buffer[count - 3]);
			add_child_node(pmnode, buffer[count - 2]);
			add_child_node(pmnode, buffer[count - 1]);
            printf("%d\n",count);
			count = count - 4;
            printf("%d\n",count);
			addtobuffer(pmnode);
			isBrack = -1;
			printf("add pm to pmnode\n");
		}
		else {
			add_child_node(pmnode, buffer[count - 2]);
			add_child_node(pmnode, buffer[count - 1]);
            printf("%d\n",count);
			count = count - 2;
			addtobuffer(pmnode);
            printf("%d\n",count);
			printf("add pm to pmnode\n");

		}
        PDL(lookahead,fd,parent);
    }
    //PDL2 -> epsilon
    else if(token == RPAREN){
		ast_info *pminfo;
		ast_node *pmnode;
		pminfo = create_new_ast_node_info(NONTERMINAL, 0, param, 0, src_lineno);
		pmnode = create_ast_node(pminfo);
		if (isBrack) {
			add_child_node(pmnode, buffer[count - 4]);
			add_child_node(pmnode, buffer[count - 3]);
			add_child_node(pmnode, buffer[count - 2]);
			add_child_node(pmnode, buffer[count - 1]);
            printf("%d\n",count);
			count = count - 4;
            printf("%d\n",count);
			addtobuffer(pmnode);
			isBrack = -1;
			printf("add pm to pmnode\n");
		}
		else {
			add_child_node(pmnode, buffer[count - 2]);
			add_child_node(pmnode, buffer[count - 1]);
            printf("%d\n",count);
			count = count - 2;
            printf("%d\n",count);
			addtobuffer(pmnode);
			printf("add pm to pmnode\n");

		}
		
    }
    //else, report error
    else{
        parser_error("ERROR: missing token for PDL2");
    }
}

static void BLOCK(int token, FILE *fd, ast_node *parent){
	printf("BLOCK\n");
  
    //block -> VDL StmtList
    if(token == INT || token == CHAR || token == SEMI || token == LBRACE || token == LPAREN || token == NOT || token == MINUS || token == IF || token == WHILE || token == NUM || token == ID || token == RETURN || token == READ || token == WRITE ||token == WRITELN || token == BREAK){
		printf("VarDecList\n");
		VDL(token, fd, parent);
		//if there is vardec,create vardec list
		if (count > 0) {
			ast_info *vdlinfo;
			ast_node *vdlnode;
			vdlinfo = create_new_ast_node_info(NONTERMINAL,0,vardeclList,0,src_lineno);
			vdlnode = create_ast_node(vdlinfo);
			add_child_node(parent, vdlnode);
			printf("add vdlnode to block\n");
			int i;
            for (i = 0; i < count; i = i + 1) {
				add_child_node(vdlnode, buffer[i]);
			}
            printf("add vardec to vdlnode");
            printf("%d\n",count);
			count = 0;
            printf("%d\n",count);

		}
       //create node for stmtlist
		ast_info *slinfo;
		ast_node *slnode;
		slinfo = create_new_ast_node_info(NONTERMINAL, 0, stmtList, 0, src_lineno);
		slnode = create_ast_node(slinfo);
		add_child_node(parent, slnode);
        printf("add slnode to parent");

        StmtList(lookahead,fd,slnode);
	

    }
    else{
        parser_error("ERROR: missing token for BLOCK");
    }
}

static void StmtList(int token, FILE *fd, ast_node *parent){
	printf("StmtList\n");
    //StmtList -> Stmt StmtList1
    if(token == SEMI|| token == LBRACE || token == LPAREN || token == RETURN || token == READ || token == WRITE || token == WRITELN || token ==BREAK || token == IF ||token == WHILE || token == NUM || token == ID || token == NOT || token == MINUS){
        Stmt(token, fd, parent);
        StmtList1(lookahead, fd, parent);
    }
    //else, report error
    else{
        parser_error("ERROR: missing token for StmtList");
    }
}

static void StmtList1(int token, FILE *fd, ast_node *parent){

    //StmtList1 -> }
    if(token == RBRACE){
		        match(RBRACE,fd,parent);
		//add block sub tree to fun_def sub tree
		
    }
    //StmtList1 -> StmtList
    else if(token == SEMI||token == LBRACE ||token == LPAREN || token == MINUS || token == NOT || token == IF || token == WHILE || token == NUM || token == ID || token == RETURN || token ==  READ || token == WRITE || token == WRITELN || token == BREAK){
        StmtList(token, fd, parent);
    }
    //else, report error
    else{
        parser_error("ERROR: missing token for StmtList1");
    }
}

static void Stmt(int token, FILE *fd, ast_node *parent){
	printf("Stmt\n");
    //Stmt -> ;
    if (token == SEMI) {
        match(SEMI,fd,parent);
    }
    //Stmt ->return Expr;
    else if(token == RETURN){
        match(RETURN,fd,parent);
        Expr(lookahead, fd, parent);	
        //if next token is ;,continue
        if(lookahead == SEMI){
     		//add expr to return
			add_child_node(buffer[0], buffer[1]);
			printf("add expr to return\n");
			add_child_node(parent, buffer[0]);
			printf("add return to stmt\n");
            printf("%d\n",count);
			count = 0;
            printf("%d\n",count);
            match(SEMI,fd,parent);
        }
        //else, report error
        else{
            parser_error("ERROR: missing ; after expression");
        }
    }
    //Stmt -> read id;
    else if(token == READ){
        match(READ, fd, parent);
        //if next token is id, continue
        if(lookahead == ID){
            match(ID,fd,parent);
            add_child_node(buffer[0], buffer[1]);
            printf("add id to read\n");
            add_child_node(parent, buffer[0]);
            printf("add read to stmtlist");
            printf("%d\n",count);
            count = 0;
            printf("%d\n",count);
            //if next token is ;, continue
            if(lookahead == SEMI){
				//add id to read

				match(SEMI, fd, parent);
            }
            //else, report error
            else{
                parser_error("ERROR: missing ; after ID");
            }
        }
        //else, report error
        else{
            parser_error("ERROR: missing id after return");
        }
    }
    //Stmt -> write Expr;
    else if(token == WRITE){
        match(WRITE,fd,parent);
		
        Expr(lookahead, fd, parent);
		
        //if next token is ;, continue
        if(lookahead ==  SEMI){
			
			add_child_node(buffer[0], buffer[1]);
			printf("add Expr to write\n");
			add_child_node(parent, buffer[0]);
			printf("add write to stmtlist");
            printf("%d\n",count);
			count = 0;
            printf("%d\n",count);
			match(SEMI, fd, parent);
        }
        //else, report error
        else{
            parser_error("ERROR: missing ; after expression");
        }
    }
    //Stmt -> writeln;
    else if(token == WRITELN){
        match(WRITELN,fd,parent);
	
        //if next token is ;, continue
        if(lookahead == SEMI){
		
            match(SEMI,fd,parent);
			add_child_node(parent, buffer[0]);
            printf("%d\n",count);
			count = 0;
            printf("%d\n",count);
			printf("add writeln to stmtlist\n");
        }
        //else, report error
        else{
            parser_error("ERROR: missing ; after writeln");
        }
    }
    //Stmt -> break;
    else if(token == BREAK){

        match(BREAK,fd,parent);
	
        //if next token is ;, continue
        if(lookahead == SEMI){
		    match(SEMI,fd,parent);
			add_child_node(parent, buffer[0]);
            printf("%d\n",count);
			count = 0;
            printf("%d\n",count);
			printf("add break to stmtlist\n");
        }
        //else, report error
        else{
            parser_error("ERROR: missing ; after break");
        }
    }
    //Stmt -> if (Expr) Stmt else Stmt
    else if(token == IF){
		//create a new stmt node
		ast_info *sinfo;
		ast_node *snode;
		sinfo = create_new_ast_node_info(NONTERMINAL, 0, stmt, 0, src_lineno);
		snode = create_ast_node(sinfo);
		add_child_node(parent, snode);
		printf("add stmt to stmtlist\n");
        match(IF,fd,parent);
		add_child_node(snode, buffer[0]);
        printf("add if to ifstmt");
        printf("%d\n",count);
		count = 0;
        printf("%d\n",count);
        //if next token is (, continue
        if(lookahead == LPAREN){
            match(LPAREN,fd,parent);
            Expr(lookahead, fd, snode);
			ast_node **snodechild;
			snodechild = get_childlist(snode);
			ast_node *ifnode;
			ifnode = snodechild[0];
			add_child_node(ifnode, buffer[0]);
            printf("add expr to ifstmt");
            printf("%d\n",count);
			count = 0;
            printf("%d\n",count);
            //if next token is ),continue
            if(lookahead == RPAREN){
                match(RPAREN,fd,parent);
                Stmt(lookahead, fd, snode);
                printf("add stmt to ifstmt");
				//add_child_node(snode, buffer[0]);
                printf("%d\n",count);
				count = 0;
                printf("%d\n",count);
                //if next token is else, continue
                if(lookahead == ELSE){
                    match(ELSE,fd,parent);
					add_child_node(snode, buffer[0]);
                    printf("add else to ifstmt");
                    printf("%d\n",count);
					count = 0;
                    printf("%d\n",count);
                    Stmt(lookahead, fd, snode);

                    printf("add stmt to ifstmt");
                    printf("%d\n",count);
					count = 0;
                    printf("%d\n",count);
					

                }
                //else, report error
                else{
                    parser_error("ERROR: missing else after stmt");
                }
            }
            //else, report error
            else{
                parser_error("ERROR: missing ) after expression");
            }
        }
        //else, report error
        else{
            parser_error("ERROR: missing ( after if");
        }
    }
    //Stmt -> while (Expr) Stmt
    else if(token == WHILE){
		ast_info *sinfo;
		ast_node *snode;
		sinfo = create_new_ast_node_info(NONTERMINAL, 0, stmt, 0, src_lineno);
		snode = create_ast_node(sinfo);
		add_child_node(parent, snode);
		printf("add stmtnode to stmtlistnode");
        match(WHILE,fd,parent);
		add_child_node(snode, buffer[0]);
        printf("add while to whilestmt");
        printf("%d\n",count);
		count = 0;
        printf("%d\n",count);
        //if next token is (, continue
        if(lookahead == LPAREN){
            match(LPAREN, fd, parent);
            Expr(lookahead, fd, snode);
			add_child_node(snode, buffer[0]);
            printf("add expr to whilestmt");
            printf("%d\n",count);
			count = 0;
            printf("%d\n",count);
            //if next token is ), continue
            if(lookahead == RPAREN){
                match(RPAREN,fd,parent);
                Stmt(lookahead, fd, snode);

                printf("add stmt to whilestmt");
                printf("%d\n",count);
				count = 0;
                printf("%d\n",count);
			
            }
            //else, report error
            else{
                parser_error("ERROR: missing ) after expression");
            }
        }
        //else, report error
        else{
            parser_error("ERROR: missing ( after while");
        }
    }
    
    //Stmt -> { BLOCK
    else if(token == LBRACE){
        match(LBRACE,fd,parent);
		ast_info *blinfo;
		ast_node *blnode;
		blinfo = create_new_ast_node_info(NONTERMINAL, 0, block, 0, src_lineno);
		blnode = create_ast_node(blinfo);
		add_child_node(parent, blnode);
        printf("add block to parent");
        BLOCK(lookahead, fd, blnode);
    }
    //Stmt -> Expr;
    else if(token == LPAREN || token == NUM || token == ID || token == MINUS || token == NOT){
		Expr(lookahead, fd, parent);
        //if next token is ;,continue
        if(lookahead == SEMI){
            match(SEMI, fd, parent);
			add_child_node(parent, buffer[count-1]);
            printf("%d\n",count);
            printf("add expr to parent");
			count = 0;
            printf("%d\n",count);
        }
        //else, report error
        else{
            parser_error("ERROR: missing ; after expression");
        }
    }
    //else, report error
    else{
        parser_error("ERROR: missing token for statement");
    }
}

static void Expr(int token, FILE *fd, ast_node *parent) {
	printf("Expr\n");
	//Expr -> E0
	if (token == LPAREN || token == MINUS || token == NOT || token == NUM || token == ID) {
		E1(token, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for Expr");
	}

}

/*static void E0(int token, FILE *fd, ast_node *parent){
//E0 -> E1E0'
if(token == LPAREN || token == MINUS || token == NOT || token == NUM || token == ID){
E1(token, fd, parent);
E0b(lookahead, fd, parent);
}
//else, report error
else{
parser_error("ERROR: missing token for E0");
}
}

static void E0b(int token, FILE *fd, ast_node *parent){
//E0' -> = Expr
if(token == ASSIGN){
match(ASSIGN, fd,parent);
Expr(lookahead, fd, parent);
//add child node to assign
add_child_node(buffer[count - 2], buffer[count - 3]);
printf("add x to =,\n");
add_child_node(buffer[count - 2], buffer[count - 1]);
printf("add 5 to =,\n")
count = count - 3;
//add assign to buffer
addtobuffer(buffer[count + 1]);
printf("add = to buffer, \n")
}
//E0' -> epsilon
else if(token == COMMA || token == SEMI || token == RBRACK || token == RPAREN){
}
//else, report error
else{
parser_error("ERROR: missing token for E0b");
}
}

*/
static void E1(int token, FILE *fd, ast_node *parent) {
	//E1 -> E2E1'
	if (token == LPAREN || token == MINUS || token == NOT || token == NUM || token == ID) {
		E2(token, fd, parent);
		E1b(lookahead, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E1");
	}
}

static void E1b(int token, FILE *fd, ast_node *parent) {
	//E1b -> ||E2E1'
	if (token == OR) {
		match(OR, fd, parent);
		E2(lookahead, fd, parent);
		E1b(lookahead, fd, parent);
		add_child_node(buffer[count - 2], buffer[count - 3]);
		add_child_node(buffer[count - 2], buffer[count - 1]);
        printf("%d\n",count);
		count = count - 3;
        printf("%d\n",count);
		addtobuffer(buffer[count + 1]);
        printf("add or");

	}
	//E1b -> epsilon
	else if (token == COMMA || token == SEMI || token == RBRACK || token == RPAREN) {
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E1b");
	}

}

static void E2(int token, FILE *fd, ast_node *parent) {
	//E2 -> E3E2'
	if (token == LPAREN || token == MINUS || token == NOT || token == NUM || token == ID) {
		E3(token, fd, parent);
		E2b(lookahead, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E2");
	}
}

static void E2b(int token, FILE *fd, ast_node *parent) {
	//E2' -> &&E3E2'
	if (token == AND) {
		match(AND, fd, parent);
		E3(lookahead, fd, parent);
		E2b(lookahead, fd, parent);
		add_child_node(buffer[count - 2], buffer[count - 3]);
		add_child_node(buffer[count - 2], buffer[count - 1]);
        printf("%d\n",count);
		count = count - 3;
        printf("%d\n",count);
        printf("add and");
		addtobuffer(buffer[count + 1]);
		
	}
	//E2' -> epsilon
	else if (token == COMMA || token == SEMI || token == RBRACK || token == RPAREN || token == OR) {

	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E2b");
	}
}

static void E3(int token, FILE *fd, ast_node *parent) {
	//E3 -> E4E3'
	if (token == LPAREN || token == MINUS || token == NOT || token == NUM || token == ID) {
		E4(token, fd, parent);
		E3b(lookahead, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E3");
	}
}

static void E3b(int token, FILE *fd, ast_node *parent) {
	//E3' -> == E4E3'
	if (token == EQ) {
		match(EQ, fd, parent);
		E4(lookahead, fd, parent);
		E3b(lookahead, fd, parent);
		add_child_node(buffer[count - 2], buffer[count - 3]);
		add_child_node(buffer[count - 2], buffer[count - 1]);
        printf("%d\n",count);
		count = count - 3;
        printf("%d\n",count);
        printf("add EQ");
		addtobuffer(buffer[count + 1]);

	}
	//E3' -> != E4E3'
	else if (token == NE) {
		match(NE, fd, parent);
		E4(lookahead, fd, parent);
		E3b(lookahead, fd, parent);
		add_child_node(buffer[count - 2], buffer[count - 3]);
		add_child_node(buffer[count - 2], buffer[count - 1]);
        printf("%d\n",count);
		count = count - 3;
        printf("%d\n",count);
        printf("add NE");
		addtobuffer(buffer[count + 1]);

	}
	//E3' -> epsilon
	else if (token == COMMA || token == SEMI || token == RBRACK || token == RPAREN || token == OR || token == AND) {
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E3b");
	}
}

static void E4(int token, FILE *fd, ast_node *parent) {
	//E4 -> E5E4'
	if (token == LPAREN || token == MINUS || token == NOT || token == NUM || token == ID) {
		E5(token, fd, parent);
		E4b(lookahead, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E4");
	}
}
static void E4b(int token, FILE *fd, ast_node *parent) {
	//E4' -> < E5E4'
	//E4' -> <= E5E4'
	//E4' -> > E5E4'
	//E4' -> >= E5E4'
	if (token == LT || token == LE || token == GT || token == GE) {
		match(token, fd, parent);
		E5(lookahead , fd, parent);
		E4b(lookahead, fd, parent);
		add_child_node(buffer[count - 2], buffer[count - 3]);
		add_child_node(buffer[count - 2], buffer[count - 1]);
        printf("%d\n",count);
		count = count - 3;
        printf("%d\n",count);
        printf("add inequality");
		addtobuffer(buffer[count + 1]);
		
	}
	//E4' -> epsilon
	else if (token == COMMA || token == SEMI || token == RBRACK || token == RPAREN || token == OR || token == AND || token == EQ || token == NE) {
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E4b");
	}
}
static void E5(int token, FILE *fd, ast_node *parent) {
	//E5 -> E6E5'
	if (token == LPAREN || token == MINUS || token == NOT || token == NUM || token == ID) {
		E6(token, fd, parent);
		E5b(lookahead, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E5");
	}
}

static void E5b(int token, FILE *fd, ast_node *parent) {
	//E5' -> + E6E5'
	//E5' -> - E6E5'
	if (token == PLUS || token == MINUS) {
		match(token, fd, parent);
		E6(lookahead, fd, parent);
		E5b(lookahead, fd, parent);
		add_child_node(buffer[count - 2], buffer[count - 3]);
		add_child_node(buffer[count - 2], buffer[count - 1]);
        printf("%d\n",count);
		count = count - 3;
        printf("%d\n",count);
        printf("add +/-");
		addtobuffer(buffer[count + 1]);

	}
	//E5' -> epsilon
	else if (token == COMMA || token == SEMI || token == RBRACK || token == RPAREN || token == OR || token == AND || token == EQ || token == NE || token == LT || token == LE || token == GT || token == GE) {
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E5b");
	}
}

static void E6(int token, FILE *fd, ast_node *parent) {
	//E6 -> E7E6'
    printf("%d\n",token);
	if (token == LPAREN || token == MINUS || token == NOT || token == NUM || token == ID) {
		E7(token, fd, parent);
		E6b(lookahead, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E6");
	}
}

static void E6b(int token, FILE *fd, ast_node *parent) {
	//E6' -> * E7E6'
	//E6' -> / E7E6'
    printf("%d\n",token);
	if (token == MULT || token == DIV) {
		match(token, fd, parent);
		E7(lookahead, fd, parent);
		E6b(lookahead, fd, parent);
		add_child_node(buffer[count - 2], buffer[count - 3]);
		add_child_node(buffer[count - 2], buffer[count - 1]);
        printf("%d\n",count);
		count = count - 3;
        printf("%d\n",count);
        printf("add *//");
		addtobuffer(buffer[count + 1]);

	}
	//E6' -> epsilon
	else if (token == COMMA || token == SEMI || token == RBRACK || token == RPAREN || token == OR || token == AND || token == EQ || token == NE || token == LT || token == LE || token == GT || token == GE || token == PLUS || token == MINUS) {
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E6b");
	}
}

static void E7(int token, FILE *fd, ast_node *parent) {
	//E7 -> !E7E8
	//E7 -> -E7E8
	if (token == NOT || token == MINUS) {
		match(token, fd, parent);
		E7(lookahead, fd, parent);
		E8(lookahead, fd, parent);
		add_child_node(buffer[count-2],buffer[count-1]);
        printf("%d\n",count);
		count = count - 1;
        printf("%d\n",count);
        printf("add !/-");
	}
	//E7 -> E8
	else if (token == NUM || token == ID || token == LPAREN) {
		E8(token, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E7");
	}

}

static void E8(int token, FILE *fd, ast_node *parent) {
	//E8 -> NUM
	if (token == NUM) {
		match(NUM, fd, parent);
	}
	//E8 ->(Expr)
	else if (token == LPAREN) {
		match(LPAREN, fd, parent);
		Expr(lookahead, fd, parent);
		//if next token is ), continue
		if (lookahead == RPAREN) {
			match(RPAREN, fd, parent);
		}
		//else, report error
		else {
			parser_error("ERROR: missing ) after expression");
		}
	}
	//E8 -> id E8'
	else if (token == ID) {
		match(ID, fd, parent);
		E8b(lookahead, fd, parent);
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for E8");
	}
}

static void E8b(int token, FILE *fd, ast_node *parent) {
    printf("%d\n",token);
	//E8' -> (ExprList)
	if (token == LPAREN) {
		match(LPAREN, fd, parent);
		ExprList(lookahead, fd, parent);
		//if next token is ), continue
		if (lookahead == RPAREN) {
			match(RPAREN, fd, parent);
		}
		//else, report error
		else {
			parser_error("ERROR: missing ) after expression list");
		}
	}
	//E8' -> [Expr]Assign
	else if (token == LBRACK) {
		match(LBRACK, fd, parent);
		Expr(lookahead, fd, parent);
		//if next token is ], continue
		if (lookahead == RBRACK) {
			match(RBRACK, fd, parent);
			ast_info *einfo;
			ast_node *enode;
			einfo = create_new_ast_node_info(NONTERMINAL,0,expr,0,src_lineno);
			enode = create_ast_node(einfo);
			int i;
			for (i = 4; i > 0; i = i - 1) {
				add_child_node(enode, buffer[count-i]);
			}
            printf("%d\n",count);
			count = count - 4;
            printf("%d\n",count);
            printf("add id[expr]");
			addtobuffer(enode);
			//if next token is assign, continue
			assign(lookahead, fd, parent);


		}
		else {
			parser_error("ERROR: missing ] in E8b");
		}
	}
	//E8' -> ASSIGN
	else if (token == COMMA || token == SEMI || token == RBRACK || token == RPAREN || token == OR || token == AND || token == EQ || token == NE || token == LT || token == LE || token == GT || token == GE || token == PLUS || token == MINUS||token == MULT || token == DIV||token == ASSIGN) {
		assign(lookahead, fd, parent);

	}
	//else, report error
	else {
		parser_error("ERROR: missing token E8b");
	}
}

static void assign(int token, FILE *fd, ast_node *parent) {
	//Assign -> = Expr
	if (token == ASSIGN) {
		match(ASSIGN, fd, parent);
		Expr(lookahead, fd, parent);
        printf("%d\n",count);

		add_child_node(buffer[count - 2], buffer[count - 3]);
		add_child_node(buffer[count - 2], buffer[count - 1]);
        printf("%d\n",count);
		count = count - 3;
        printf("%d\n",count);
        printf("add =");
		addtobuffer(buffer[count + 1]);
        printf("%d\n",count);
	}
	//Assign -> Epsilon
	else if (token == COMMA || token == SEMI || token == RBRACK || token == RPAREN || token == OR || token == AND || token == EQ || token == NE || token == LT || token == LE || token == GT || token == GE || token == PLUS || token == MINUS || token == MULT||token == DIV) {
	}
	//else, report error
	else {
		parser_error("ERROR: missing token for Assign");
	}
}


static void ExprList(int token, FILE *fd, ast_node *parent){
    //ExprList -> Expr EL'
    if (token == MINUS || token == NOT || token == NUM || token == ID || token == LPAREN) {
        Expr(token, fd, parent);
        ELb(lookahead, fd, parent);
    }
    //ExprList -> epsilon
    else if(token == RPAREN){
    }
    //else, report error
    else{
        parser_error("ERROR: missing token for ExprList");
    }
}

static void ELb(int token, FILE *fd, ast_node *parent){
    //EL' -> , ExprList
    if (token == COMMA) {
        match(COMMA, fd, parent);
        ExprList(lookahead, fd, parent);
    }
    //EL' -> epsilon
    else if(token == RPAREN){
    }
    //else, report error
    else{
        parser_error("ERROR: missing token for ELb");
    }
}


static void match(int token, FILE *fd, ast_node *parent){
    //match and printout
    printf("match: ");
    lexer_emit(token, tokenval,lexbuf);
	if (token != SEMI && token != COMMA && token != LBRACE && token != LPAREN &&
		token != RBRACE && token != RPAREN) {
		ast_info *newInfo;
		ast_node *newNode;
		newInfo = create_new_ast_node_info(token, 0, 0, lexbuf, src_lineno);
		newNode = create_ast_node(newInfo);
		addtobuffer(newNode);
	}
    //get next token
    lookahead = lexan(fd);
}


/**************************************************************************/
static void parser_error(char *err_string) {
  if(err_string) {
    printf("%s\n", err_string);
  }
  exit(1);
}  
/**************************************************************************/
/*
 *  this function corresponds to the start symbol in the LL(1) grammar
 *  when this function returns, the full AST tree with parent node "parent"
 *  will be constructed
 *         fd: the input stream
 *     parent: the parent ast node  (it should be a ROOT)
 */
static void program(FILE *fd, ast_node *parent) {


  parser_debug0("in program\n");

   //assert is useful for testing a function's pre and post conditions
  assert(parent->symbol->token == NONTERMINAL);
  assert(parent->symbol->grammar_symbol == PROGRAM);


}


