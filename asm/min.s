	.text
	call main

max:
	lw x10, 0(sp) #x
	addi sp, sp, -4
	sh x10, 2(sp) #store x

	addi x11, sp, 6 # ((short*)&a) + 1
	lh x11, 0(x11)

	sh x11, 0(sp)

	bgt x11, x10, do

	mv x10, x11
	
	addi sp, sp, 4

	ret
	
do: 
	addi sp, sp, 4
	ret



process:
	addi sp, sp, -8
	sw ra, 4(sp)
	sw x0, 0(sp) #store ra

	addi sp, sp, -8
	sw x0, 0(sp) #store i

	lw x10, 16(sp) #read n
	sw x10, 4(sp) # store n

	call for_

	lw ra, 12(sp)
	lw x10, 8(sp)

	addi sp, sp, 16

	ret

for_: 
	lw x10, 0(sp) #i
	lw x11, 4(sp) #n 

	bge x10, x11, brk

	addi sp, sp, -4 #store ra
	sw ra, 0(sp)

	lw x10, 24(sp) #w[0]
	
	lw x11, 4(sp)
	li x12, 16
	mul x11, x11, x12 # 16i

	add x10, x10, x11 #w[i]
	addi x10, x10, 8 #w[i].c 

	addi x10, x10, 4 # w[i].c + 1

	lw x10, 0(x10) # rasac vatant tfn-s 

	addi sp, sp, -4
	sw x10, 0(sp)
	
	sw x10, 32(sp)

	jalr x10

	lw x11, 16(sp)
	add x10, x10, x11 #updated res 

	sw x10, 16(sp)

	lw ra, 4(sp)

	addi sp, sp, 8

	lw x10, 0(sp)
	addi x10, x10, 2
	sw x10, 0(sp)

	j for_

brk: 
	ret


run_test_max:
	# print name
	li a0, 4
	lw a1, 4(sp)
	ecall
	la a1, RUNNING
	ecall
	# backup ra
	addi sp, sp, -4
	sw ra, 0(sp)
	# allocate stack for args + ra
	li a0, 4 # args size is 4
	addi a1, sp, 16
	li a2, 0
	sub sp, sp, a0
	mv a3, sp
copy_max:
	beq a2, a0, call_func_max
	lw a4, 0(a1)
	sw a4, 0(a3)
	addi a1, a1, 4
	addi a3, a3, 4
	addi a2, a2, 4
	j copy_max
call_func_max:
	call max
	addi sp, sp, 4 # args size is 4
	lw ra, 0(sp)
	addi sp, sp, 4
	mv a2, a0
	lw a3, 8(sp)
	li a0, 4
	lw a1, 4(sp)
	ecall
	bne a2, a3, failure
	li a0, 4
	la a1, SUCCESS
	ecall
	ret

run_test_process:
	# print name
	li a0, 4
	lw a1, 4(sp)
	ecall
	la a1, RUNNING
	ecall
	# backup ra
	addi sp, sp, -4
	sw ra, 0(sp)
	# allocate stack for args + ra
	li a0, 12 # args size is 12
	addi a1, sp, 16
	li a2, 0
	sub sp, sp, a0
	mv a3, sp
copy_process:
	beq a2, a0, call_func_process
	lw a4, 0(a1)
	sw a4, 0(a3)
	addi a1, a1, 4
	addi a3, a3, 4
	addi a2, a2, 4
	j copy_process
call_func_process:
	call process
	addi sp, sp, 12 # args size is 12
	lw ra, 0(sp)
	addi sp, sp, 4
	mv a2, a0
	lw a3, 8(sp)
	li a0, 4
	lw a1, 4(sp)
	ecall
	bne a2, a3, failure
	li a0, 4
	la a1, SUCCESS
	ecall
	ret

failure:
	li a0, 4
	la a1, FAILURE
	ecall
	ret

exit:
	li a0, 10
	ecall

TEST_1:
	addi sp, sp, -16
	la a0, TEST_1_NAME
	li a1, 1287
	li a2, 84345604
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	call run_test_max
	lw ra, 0(sp)
	addi sp, sp, 16
	ret

CONST:
	li a0, 2
	ret

INPOUT:
	lw a0, 0(sp)
	ret

TEST_2:
	addi sp, sp, -60

	addi x13, sp, 0
	li x10, 9
	li x11, 1
	li x12, 2
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi x13, sp, 16
	li x10, 10
	li x11, 3
	li x12, 4
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi x13, sp, 16
	li x10, 11
	li x11, 5
	li x12, 6
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi sp, sp, -24
	la a0, TEST_2_NAME
	li a1, 4
	li a2, 3
	addi a3, sp, 24
	la a4, CONST
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	sw a3, 16(sp)
	sw a4, 20(sp)
	call run_test_process
	lw ra, 0(sp)
	addi sp, sp, 24
	addi sp, sp, 60
	ret

TEST_3:
	addi sp, sp, -60

	addi x13, sp, 0
	li x10, 9
	li x11, 1
	li x12, 2
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi x13, x13, 16
	li x10, 10
	li x11, 3
	li x12, 4
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi x13, x13, 16
	li x10, 11
	li x11, 5
	li x12, 6
	sb x10, 8(x13)
	sb x10, 9(x13)
	sb x11, 10(x13)
	sb x11, 11(x13)
	sb x12, 12(x13)
	sb x12, 13(x13)

	addi sp, sp, -24
	la a0, TEST_3_NAME
	li a1, 134743558
	li a2, 3
	addi a3, sp, 24
	la a4, INPOUT
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	sw a3, 16(sp)
	sw a4, 20(sp)
	call run_test_process
	lw ra, 0(sp)
	addi sp, sp, 24
	addi sp, sp, 60
	ret


main:
	call TEST_1
	call TEST_2
	call TEST_3
	call exit

.data
RUNNING:
	.string "RUNNING\n"
FAILURE:
	.string "FAILURE\n\n"
SUCCESS:
	.string "SUCCESS\n\n"
TEST_1_NAME:
    .string "TEST_1: "
TEST_2_NAME:
    .string "TEST_2: "
TEST_3_NAME:
    .string "TEST_3: "
TEST_4_NAME:
    .string "TEST_4: "
TEST_5_NAME:
    .string "TEST_5: "
TEST_6_NAME:
    .string "TEST_6: "
