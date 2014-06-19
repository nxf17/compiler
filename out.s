.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
	li $v0,4
	la $a0,_prompt
	syscall
	li $v0,5
	syscall
	jr $ra

write:
	li $v0,1
	syscall
	li $v0,4
	la $a0,_ret
	syscall
	move $v0,$0
	jr $ra

main:
	addi $sp, $sp, 4
	addi $sp, $sp, 4
	li $t0, 0
	sw $t0, 0($sp)
	move $v0, $0
	jr $ra
