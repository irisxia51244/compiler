//
// Error routines
//
#include <stdlib.h>
#include "lexer.h"

//
// generates an error message
//
void lexer_error(char *m, int src_lineno)  {
  fprintf(stderr, "line %d: %s\n", src_lineno, m);
  exit(1);   /*   unsuccessful termination  */
}
