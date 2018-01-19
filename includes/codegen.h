#ifndef _CODEGEN_H
#define _CODEGEN_H
#define MAXVALUE 500
#define PRINT_INT 1
#define PRINT_STR 4
#define NIL 1000

#define STARTREG 599
#define $t0 600
#define $t1 601
#define $t2 602
#define $t3 603
#define $t4 604
#define $t5 605
#define $t6 606
#define $t7 607
#define $t8 608
#define $t9 609
#define $s0 611
#define $s1 612
#define $s2 613
#define $s3 614
#define $s4 615
#define ARG_START 616
#define $a0 616
#define $a1 617
#define $a2 618
#define $a3 619
#define ARG_END 619
#define $v0 620
#define $v1 621
#define $ra 622
#define $_0 623
#define ENDREG 624


#define INSTRUCTION_START 625
#define add 626
#define sub 627
#define mult 628
#define Divide  629
#define mflo 630
#define mfhi 631
#define addi 632
#define move 633
#define li 634
#define la 635
#define lw 636
#define sw 637
#define syscall 638
#define j 639
#define jal 640
#define jr 641
#define beq 642
#define bne 643
#define blt 644
#define bgt 645
#define ble 646
#define bge 647
#define slt 648
#define INSTRUCTION_END 649

#define ALIGN_WIDTH 15

// you likely will need to include other 
// header files from your compiler here
#include "parser.h"
#include "lexer.h"

// add all definitions exported by your code gen modules here


struct table_row{
    int instruction;
    int r0;
    int r1;
    int r2;
    char label[MAXLEXSIZE];
};
typedef struct table_row table_row;

extern int reg_count;
int table_count;
table_row *table[MAXVALUE];
extern char *newline;
void add_row(table_row *row);

extern void codegen(ast *tree);

extern void generate_from_codetable(FILE *out);
#endif
