#include "codegen.h"
#include "parser.h"
#include "ast.h"
#include "lexer.h"
// functions to add, remove, modify entries in code table and
// to write codetable to MIPS output file

static void generate_table_start(FILE *out); //hard code start part
static void print_table_row(FILE *out, table_row *table_row);//print each row of the table
static void print_table(FILE *out);
static void destroy_table_row(table_row *table);


static char *reg_strings[] = { "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
"$t8","$t9","$s0","$s1","$s2","$s3","$s4","arg_start","$a0","$a1","$a2","$a3","$v0",
"$v1","$ra","$0","endreg"};

static char *instr_strings[] = { "add","sub","mult","div",
"mflo","mfhi","addi","move","li","la","lw","sw","syscall","j","jal","jr","beq","bne",
"blt","bgt","ble","bge","slt" };

void add_row(table_row *row) {
	table[table_count] = row;
	table_count++;
}


void generate_from_codetable(FILE *out) {
	generate_table_start(out);
	print_table(out);
}


void destroy_table() {
	int i;
	for (i = 0; i < table_count; i++) {
		destroy_table_row(table[i]);
	}
}

static void destroy_table_row(table_row *table_row) {
	if (table_row != NULL) {
		free(table_row);
	}
}

static void generate_table_start(FILE *out) {
	fprintf(out, "%*s\n", ALIGN_WIDTH, ".data");
	fprintf(out, "_newline_:%*s", ALIGN_WIDTH, ".ascii \" \\n\" \n");
	fprintf(out, "%*s\n",ALIGN_WIDTH,".align 2");
	fprintf(out, "%*s\n", ALIGN_WIDTH, ".text");
	fprintf(out, "%s: \n", "main");
}

static void print_table(FILE *out) {
	int i;
	for (i = 0; i < table_count; i++) {
		if (table[i] != NULL) {
			print_table_row(out, table[i]); 
		}
	}
}

static void print_table_row(FILE *out, table_row *row) {
	if(row -> instruction != NIL){


		char *instr = instr_strings[row->instruction - INSTRUCTION_START -1];
       		fprintf(out, "%*s", -ALIGN_WIDTH / 3, instr);
	}
	if (row -> r0 != NIL) {
		if (row->r0 >= STARTREG && row->r0 <= ENDREG) {
			char *r0_string = reg_strings[row->r0 - STARTREG - 1];
			fprintf(out, "%s", r0_string);
		}
		else {
			fprintf(out, "%d", row->r0);
		}
	}
	if (row->r1 != NIL) {
		if (row->r1 >= STARTREG && row->r1 <= ENDREG) {
			char *r1_string = reg_strings[row->r1 - STARTREG - 1];
			fprintf(out, ",%s", r1_string);
		}
		else {
			fprintf(out, ",%d", row->r1);
		}
	}
	if (row->r2 != NIL) {
		if (row->r2 >= STARTREG && row->r2 <= ENDREG) {
			char *r2_string = reg_strings[row->r2 - STARTREG - 1];
			fprintf(out, ",%s", r2_string);
		}
		else {
			fprintf(out, ",%d", row->r2);
		}
	}
	if (row->label[0] != '\0') {
		if (row->instruction == NIL && row->r0 == NIL && row->r1 == NIL &&
			row->r2 == NIL) {
			fprintf(out, "\n%s:", row->label);
		}
		else if (row->instruction != NIL && row->r0 == NIL && row->r1 == NIL
			&&row->r2 == NIL) {
			fprintf(out, "%s", row->label);
		}
		else {
			fprintf(out, ",%s", row->label);
		}
	}
	fprintf(out, "\n");
}