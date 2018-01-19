          .data
_newline_: .ascii " \n" 
       .align 2
          .text
main: 

WHILE:
li   $t0,1
li   $t1,2
slt  $t0,$t0,$t1
beq  $t0,$0,ELSE
li   $t1,1
move $a0,$t1
li   $v0,1
syscall
li   $t2,2
li   $t3,3
slt  $t2,$t2,$t3
beq  $t2,$0,ELSE
li   $t3,2
move $a0,$t3
li   $v0,1
syscall
j    FINISH

ELSE:

FINISH:
jr   $ra
