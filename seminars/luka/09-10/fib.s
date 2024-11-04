.text


# int fib(int n)
# {
#     if (n <= 1) {
#         return n;
#     }
#     int y = fib(n - 1);
#     int z = fib(n - 2);
#     return y + z;
# }
# 
# int main()
# {
#     int x = fib(5);
#     printf("%d\n", x);
#     return 0;
# }

li x10, 7
addi sp, sp, -4
sw x10, 0(sp)
call fib
li x10, 1
mv x11, x20
ecall
li x10, 10
ecall

fib: 
    lw x10, 0(sp)
    addi x11, x0, 1
    bgt x10, x11, else
    mv x20, x10
    ret

else: 
    addi sp, sp, -8
    sw ra, 4(sp)
    lw x10, 8(sp)
    addi x10, x10, -1
    sw x10, 0(sp)
    call fib
    addi sp, sp, -4
    sw x20, 0(sp)
    addi sp, sp, -4
    lw x10, 8(sp)
    addi x10, x10, -1
    sw x10, 0(sp)
    call fib
    addi sp, sp, 4
    lw x10, 0(sp)
    add x20, x10, x20
    addi sp, sp, 8
    lw ra, 0(sp)
    addi sp, sp, 4
    ret