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
	addi $sp, $sp, -40
	addi $sp, $sp, -4
	li $t0, 0
	sw $t0, 0($sp)
	addi $sp, $sp, -4
	li $t0, 1
	sw $t0, 0($sp)
	lw $t0, 0($sp)
	sw $t0, 8($sp)
	addi $sp, $sp, -4
	li $t0, 1
	sw $t0, 0($sp)
	addi $sp, $sp, -4
	li $t0, 2
	sw $t0, 0($sp)
	lw $t0, 0($sp)
	sw $t0, 12($sp)
	addi $sp, $sp, -4
	li $t0, 2
	sw $t0, 0($sp)
	addi $sp, $sp, -4
	li $t0, 1
	sw $t0, 0($sp)
	addi $sp, $sp, -4
	li $t0, 2
	sw $t0, 0($sp)
	addi $sp, $sp, -4
	lw $t0, 28($sp)
	lw $t1, 24($sp)
	add $t0, $t0, $t1
	sw $t0, 0($sp)
	lw $t0, 0($sp)
	sw $t0, 24($sp)
	addi $sp, $sp, -4
	li $t0, 0
	sw $t0, 0($sp)
	move $v0, $0
	jr $ra
