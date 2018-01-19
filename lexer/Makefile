#
# compiles lexer, the lexical analyzer for C-- 
#
# make depend: automatically build .o file dependencies
# make: build lexer
# make clean: removes all .o and executable files
#

# define the compiler to use
CC = gcc

# define the compiler flags
CFLAGS = -Wall -g

# path(s) to all libraries files that are not in /usr/lib
# (ex) LFLAGS = -L/home/username/lib
LFLAGS =

# list all libraries to link in
# (ex) LIBS = -lmylib -lm 
LIBS =

# path(s) to all .h files that are not in /usr/include
INCLUDES = -I../includes

# define the C source files
# if you add more source files, include them here
#
SRCS = lexemitter.c lexerror.c lexer.c main.c  

# define the object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = lexer


#  The following part of the makefile is generic; it can be used to 
#  build any executable just by changing the definitions above and by
#  deleting dependencies appended to the file from 'make depend'
#
all:    $(MAIN) 


$(MAIN):  $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
#
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

lexemitter.o: ../includes/lexer.h /usr/include/stdio.h
lexemitter.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
lexemitter.o: /usr/include/sys/_posix_availability.h
lexemitter.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
lexemitter.o: /usr/include/_types.h /usr/include/sys/_types.h
lexemitter.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
lexemitter.o: /usr/include/sys/_types/_va_list.h
lexemitter.o: /usr/include/sys/_types/_size_t.h
lexemitter.o: /usr/include/sys/_types/_null.h
lexemitter.o: /usr/include/sys/_types/_off_t.h
lexemitter.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
lexemitter.o: /usr/include/secure/_common.h
lexerror.o: /usr/include/stdlib.h /usr/include/Availability.h
lexerror.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
lexerror.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
lexerror.o: /usr/include/sys/_symbol_aliasing.h
lexerror.o: /usr/include/sys/_posix_availability.h
lexerror.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
lexerror.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
lexerror.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
lexerror.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
lexerror.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
lexerror.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
lexerror.o: /usr/include/sys/_types/_sigaltstack.h
lexerror.o: /usr/include/sys/_types/_ucontext.h
lexerror.o: /usr/include/sys/_types/_pthread_attr_t.h
lexerror.o: /usr/include/sys/_types/_sigset_t.h
lexerror.o: /usr/include/sys/_types/_size_t.h
lexerror.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
lexerror.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
lexerror.o: /usr/include/sys/_types/_int16_t.h
lexerror.o: /usr/include/sys/_types/_int32_t.h
lexerror.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
lexerror.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
lexerror.o: /usr/include/_types/_uint64_t.h
lexerror.o: /usr/include/sys/_types/_intptr_t.h
lexerror.o: /usr/include/sys/_types/_uintptr_t.h
lexerror.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
lexerror.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
lexerror.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
lexerror.o: /usr/include/libkern/_OSByteOrder.h
lexerror.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
lexerror.o: /usr/include/sys/_types/_ct_rune_t.h
lexerror.o: /usr/include/sys/_types/_rune_t.h
lexerror.o: /usr/include/sys/_types/_wchar_t.h
lexerror.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
lexerror.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
lexerror.o: /usr/include/sys/_types/_dev_t.h
lexerror.o: /usr/include/sys/_types/_mode_t.h ../includes/lexer.h
lexerror.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
lexerror.o: /usr/include/sys/_types/_off_t.h
lexerror.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
lexerror.o: /usr/include/secure/_common.h
lexer.o: /usr/include/stdlib.h /usr/include/Availability.h
lexer.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
lexer.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
lexer.o: /usr/include/sys/_symbol_aliasing.h
lexer.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
lexer.o: /usr/include/i386/_types.h /usr/include/sys/wait.h
lexer.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
lexer.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
lexer.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
lexer.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
lexer.o: /usr/include/mach/i386/_structs.h
lexer.o: /usr/include/sys/_types/_sigaltstack.h
lexer.o: /usr/include/sys/_types/_ucontext.h
lexer.o: /usr/include/sys/_types/_pthread_attr_t.h
lexer.o: /usr/include/sys/_types/_sigset_t.h
lexer.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
lexer.o: /usr/include/sys/resource.h /usr/include/stdint.h
lexer.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
lexer.o: /usr/include/sys/_types/_int32_t.h
lexer.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
lexer.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
lexer.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
lexer.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
lexer.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
lexer.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
lexer.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
lexer.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
lexer.o: /usr/include/sys/_types/_ct_rune_t.h
lexer.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
lexer.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
lexer.o: /usr/include/i386/types.h /usr/include/sys/_types/___offsetof.h
lexer.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
lexer.o: /usr/include/assert.h /usr/include/ctype.h /usr/include/runetype.h
lexer.o: /usr/include/sys/_types/_wint_t.h ../includes/lexer.h
lexer.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
lexer.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
lexer.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
main.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
main.o: /usr/include/sys/_symbol_aliasing.h
main.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
main.o: /usr/include/i386/_types.h /usr/include/sys/_types/_va_list.h
main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
main.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
main.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
main.o: /usr/include/stdlib.h /usr/include/sys/wait.h
main.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
main.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
main.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
main.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
main.o: /usr/include/mach/i386/_structs.h
main.o: /usr/include/sys/_types/_sigaltstack.h
main.o: /usr/include/sys/_types/_ucontext.h
main.o: /usr/include/sys/_types/_pthread_attr_t.h
main.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
main.o: /usr/include/sys/resource.h /usr/include/stdint.h
main.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
main.o: /usr/include/sys/_types/_int32_t.h /usr/include/sys/_types/_int64_t.h
main.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
main.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
main.o: /usr/include/sys/_types/_intptr_t.h
main.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
main.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
main.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
main.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
main.o: /usr/include/sys/_types/_ct_rune_t.h
main.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
main.o: /usr/include/machine/types.h /usr/include/i386/types.h
main.o: /usr/include/sys/_types/___offsetof.h
main.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
main.o: /usr/include/ctype.h /usr/include/runetype.h
main.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
main.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
main.o: /usr/include/strings.h /usr/include/secure/_string.h
main.o: ../includes/lexer.h
