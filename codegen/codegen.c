// functions for generating MIPS code given an AST of a C-- program
// from the parser

// TODO: add more includes files here as necessary
#include <stdio.h>
#include <assert.h>
#include "parser.h"
#include "codegen.h"
#include "lexer.h"
#include <stdlib.h>


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

//static void And(ast_node *node);
//static void Assign(ast_node *node);
//static void Break(ast_node *node);
//static void Char(ast_node *node);
static void Div(ast_node *node);
static void Else(ast_node *node);
//static void Eq(ast_node *node);
//static void Ge(ast_node *node);
//static void Gt(ast_node *node);
//static void Id(ast_node *node);
static void If(ast_node *node);
//static void Lbrack(ast_node *node);
static void Lt(ast_node *node);
//static void Le(ast_node *node);
static void Minus(ast_node *node);
static void Mult(ast_node *node);
//static void Ne(ast_node *node);
//static void Not(ast_node *node);
static void Num(ast_node *node);
//static void Or(ast_node *node);
static void Plus(ast_node *node);
//static void Rbrack(ast_node *node);
//static void Read(ast_node *node);
//static void Return(ast_node *node);
static void While(ast_node *node);
static void Write(ast_node *node);
static void Writeln(ast_node *node);
static void Program(ast_node *node);
static void Funclist(ast_node *node);
static void Func_def(ast_node *node);
//static void Paramlist(ast_node *node);
//static void Param(ast_node *node);
static void Block(ast_node *node);
//static void Vardeclist(ast_node *node);
//static void Vardec(ast_node *node);
static void Stmtlist(ast_node *node);
static void Stmt(ast_node *node);
//static void Expr(ast_node *node);
static void checkinfo(ast_node *node);
char *itoa (int value, char *result, int base);
table_row *create_a_row(int INSTRUCTION, int R0, int R1, int R2, char *LABLE);


static int reg[] = {$t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7, $t8, $t9, $s0, $s1, $s2, $s3,$s4};
int reg_count;
int jump_finish_count;
int finish_count;
int jump_else_count;
int else_count;
char *newline = "_newline_";

// this function will be called after your parse function
// depending on how you are storing the AST (a global or a return
// value from parse, you may need to add some parameters to this function
void codegen(ast *tree) {
	//create new codetable;
    jump_else_count = 0;
    else_count = 0;
    jump_finish_count = 0;
    finish_count = 0;
	table_count = 0;
	reg_count = 0;
	ast_node *root;
	root = tree->root;
    printf("founding root\n");
	checkinfo(root);
	//add ending
	table_row *end = create_a_row(jr, $ra, NIL, NIL, NULL);
	table_count += 1;
	add_row(end);

}


/***************************************
  get the child list of the parent node
  how to return the child list?
****************************************
static ast_node** visit(ast_node *node) {
	ast_node **child_list;
	child_list = get_childlist(node);
    return child_list;
}
***/

table_row *create_a_row(int INSTRUCTION, int R0, int R1, int R2, char *LABLE) {
	table_row *row;
	row = malloc(sizeof(table_row));

	if (row) {
		row->instruction = INSTRUCTION;
		row->r0 = R0;
		row->r1 = R1;
		row->r2 = R2;
		if (LABLE != NULL) {
			strncpy(row->label , LABLE, MAXLEXSIZE);
		}
		else {
			row->label[0] = '\0';
		}
	}
	return row;
}


/************************************************
 check current node's info and decide what to do
 ************************************************/
static void checkinfo(ast_node *node) {
	if (node != NULL) {
		ast_info *info;
		info = node->symbol;

		if ((info -> token < 35) && (info -> token > 0)) {
            printf("check terminal");
			if (info -> token == AND) {
				//And(node);
			}
			else if (info -> token == ASSIGN) {
				//Assign(node);
			}
			else if (info -> token == BREAK) {
				//Break(node);
			}
			else if (info -> token == CHAR) {
				//Char(node);
			}
			else if (info -> token == DIV) {
				Div(node);
			}
			else if (info -> token == ELSE) {
                printf("check else");
				Else(node);
			}
			else if (info -> token == EQ) {
				//Eq(node);
			}
			else if (info -> token == GE) {
				//Ge(node);
			}
			else if (info -> token == GT) {
				//Gt(node);
			}
			else if (info -> token == ID) {
				//Id(node);
			}
			else if (info -> token == IF) {
                printf("check if");
				If(node);
			}
			else if (info -> token == LBRACK) {

			}
			else if (info -> token == LE) {
				//Le(node);
			}
			else if (info -> token == LT) {
                printf("check LT");
				Lt(node);
			}
			else if (info -> token == MINUS) {
				Minus(node);
			}
			else if (info -> token == MULT) {
				Mult(node);
			}
			else if (info -> token == NE) {
				//Ne(node);
			}
			else if (info -> token == NOT) {
				//Not(node);
			}
			else if (info -> token == NUM) {
				Num(node);
			}
			else if (info -> token == OR) {
				//Or(node);
			}
			else if (info -> token == PLUS) {
				Plus(node);
			}
			else if (info -> token == RBRACK) {

			}
			else if (info -> token == READ) {
				//Read(node);
			}
			else if (info -> token == RETURN) {
				//Return(node);
			}
			else if (info -> token == WHILE) {
				While(node);
			}
			else if (info -> token == WRITE) {
				Write(node);
			}
			else if (info -> token == WRITELN) {
				Writeln(node);
			}
			else {
				//error
			}

		}
		else if (info -> token == NONTERMINAL) {
			if (info->grammar_symbol == PROGRAM) {
                printf("find program");
				Program(node);
			}
			else if (info->grammar_symbol == funcList) {
                printf("find Funclist");
				Funclist(node);
			}
			else if (info->grammar_symbol == func_def) {
                printf("find funcdef");
				Func_def(node);
			}
			else if (info->grammar_symbol == vardec) {
				//Vardec(node);
			}
			else if (info->grammar_symbol == vardeclList) {
				//Vardeclist(node);
			}
			else if (info->grammar_symbol == paramList) {
				//Paramlist(node);
			}
			else if (info->grammar_symbol == param) {
				//Param(node);
			}
			else if (info->grammar_symbol == block) {
				Block(node);
			}
			else if (info->grammar_symbol == stmtList) {
                printf("find Stmtlist");
				Stmtlist(node);
			}
			else if (info->grammar_symbol == stmt) {
				Stmt(node);
			}
			else if (info->grammar_symbol == expr) {
				//Expr(node);
			}
			else {
				//error
			}
		}
	}
}

static void Program(ast_node *node) {
    //write main: into file
    ast_node **child_list;
    child_list = get_childlist(node);
    checkinfo(child_list[0]);
}

static void Funclist(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    checkinfo(child_list[0]);
}

static void Func_def(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    checkinfo(child_list[2]);
}

static void Block(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    checkinfo(child_list[0]);
}

static void Stmtlist(ast_node *node) {
	ast_node **child_list;
    child_list = get_childlist(node);
    int num_of_child;
    num_of_child = get_num_children(node);
    int i;
    for(i = 0; i < num_of_child; i++){
        checkinfo(child_list[i]);
    }
}

static void Write(ast_node *node){
	ast_node **child_list;
	child_list = get_childlist(node);
	checkinfo(child_list[0]);
	//create a row :move t0 to a0
	table_row *row;
	row = create_a_row(move, $a0, reg[reg_count-1], NIL, NULL);
	add_row(row);
	//create a row
	table_row *row2;
	row2 = create_a_row(li, $v0, PRINT_INT, NIL, NULL);
	add_row(row2);
	//create a row
	table_row *row3;
	row3 = create_a_row(syscall, NIL, NIL, NIL, NULL);
	add_row(row3);
}

static void Num(ast_node *node) {
	//get token value
	int numvalue;
	numvalue = atoi(node->symbol->lexeme);
	//create a new row
	table_row *row;
	row = create_a_row(li,reg[reg_count],numvalue,NIL,NULL);
	//add row to table
	reg_count = reg_count+1;
	add_row(row);
}

static void Writeln(ast_node *node) {
    table_row *row;
    row = create_a_row(la,$a0,NIL,NIL,newline);
    add_row(row);

    table_row *row1;
    row1 = create_a_row(li,$v0,PRINT_STR, NIL,NULL);
    add_row(row1);

    table_row *row2;
    row2 = create_a_row(syscall, NIL, NIL, NIL, NULL);
    add_row(row2);
}

static void Plus(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    int num_of_child;
    num_of_child = get_num_children(node);
    int i;
    for (i=0;i<num_of_child; i++) {
        checkinfo(child_list[i]);
    }
    table_row *row;
    row = create_a_row(add, reg[reg_count-2],reg[reg_count-2],reg[reg_count-1],NULL);
    add_row(row);
    reg_count = reg_count - 1;

}

static void Minus(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    int num_of_child;
    num_of_child = get_num_children(node);
    int i;
    for (i=0;i<num_of_child; i++) {
        checkinfo(child_list[i]);
    }
    table_row *row;
    row = create_a_row(sub, reg[reg_count-2],reg[reg_count-2],reg[reg_count-1],NULL);
    add_row(row);
    reg_count = reg_count - 1;

}

static void Mult(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    int num_of_child;
    num_of_child = get_num_children(node);
    int i;
    for (i=0;i<num_of_child; i++) {
        checkinfo(child_list[i]);
    }
    table_row *row;
    row = create_a_row(mult, reg[reg_count-2],reg[reg_count-1],NIL,NULL);
    add_row(row);
    table_row *row2;
    row2 = create_a_row(mflo,reg[reg_count-2],NIL,NIL,NULL);
    add_row(row2);
    reg_count = reg_count - 1;

}

static void Div(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    int num_of_child;
    num_of_child = get_num_children(node);
    int i;
    for (i=0;i<num_of_child; i++) {
        checkinfo(child_list[i]);
    }
    table_row *row;
    row = create_a_row(Divide, reg[reg_count-2],reg[reg_count-1],NIL,NULL);
    add_row(row);
    table_row *row2;
    row2 = create_a_row(mflo,reg[reg_count-2],NIL,NIL,NULL);
    add_row(row2);
    reg_count = reg_count - 1;

}

static void Lt(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    int num_of_child;
    num_of_child = get_num_children(node);
    int i;
    for (i=0;i<num_of_child; i++) {
        checkinfo(child_list[i]);
    }
    table_row *row;
    printf("%d\n",slt);
    row = create_a_row(slt,reg[reg_count-2],reg[reg_count-2],reg[reg_count-1],NULL);
    add_row(row);
    table_row *row2;

    //get label
    //char elselabel[MAXLEXSIZE];
    //itoa(jump_else_count,elselabel,10);
    char *label;
    label = "ELSE";
    //strcpy(label,elselabel);


    row2 = create_a_row(beq,reg[reg_count-2],$_0,NIL,label);
    reg_count = reg_count - 1;
    add_row(row2);

}

static void Stmt(ast_node *node) {
    ast_node **child_list;
    child_list = get_childlist(node);
    //if-else stmt
    if(child_list[0]->symbol->token == IF){
        If(child_list[0]);
        //stmt
        checkinfo(child_list[1]);

        //get the string for the jump finish label
        //char jump[MAXLEXSIZE];
        //itoa(jump_finish_count,jump,10);


        char *label;
        label = "FINISH";
        //strcpy(label,jump);
        //jump to finish
        table_row *row;
        row = create_a_row(j,NIL,NIL,NIL,label);
        add_row(row);
        jump_finish_count = jump_finish_count + 1;


        //else
        Else(child_list[2]);

        //stmt
        checkinfo(child_list[3]);

        //get the string for the finish label
        //char flabel[MAXLEXSIZE];
        //itoa(finish_count,flabel,10);
        char *label2;
        label2 = "FINISH";
        //strcpy(label2,flabel);
        table_row *row2;
        row2 = create_a_row(NIL,NIL,NIL,NIL,label2);
        add_row(row2);
        finish_count = finish_count + 1;
    }
    //while stmt
    else if(child_list[0]->symbol->token == WHILE){
        While(child_list[0]);
        checkinfo(child_list[1]);
        checkinfo(child_list[2]);
        table_row *row3;
        char *label3;
        label3 = "WHILE";
        row3 = create_a_row(j,NIL,NIL,NIL,label3);

        table_row *row4;
        char *label4;
        label4 = "FINISH";
        row4 = create_a_row(NIL,NIL,NIL,NIL,label4);
    }
    //other, error
}

static void If(ast_node *node){
    ast_node **child_list;
    child_list = get_childlist(node);
    checkinfo(child_list[0]);
}

static void Else(ast_node *node) {
    //char elselabel[MAXLEXSIZE];
    //itoa(else_count,elselabel,10);
    char *label;
    label = "ELSE";
    //strcpy(label,elselabel);
    table_row *row;
    row = create_a_row(NIL,NIL,NIL,NIL,label);
    else_count = else_count + 1;
    add_row(row);

}

static void While(ast_node *node) {
    table_row *row;
    char *label;
    label = "WHILE";
    row = create_a_row(NIL,NIL,NIL,NIL,label);
    add_row(row);
}




/***************/
char *itoa (int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}