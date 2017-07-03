ldr r1,=0x20200004
ldr r2,=0x40000
str r2,[r1]
ldr r1,=0x10000
ldr r3,=0x20200028
ldr r4,=0x2020001c
loop:
ldr r2,=0
str r1,[r3]
onloop:
add r2,r2,#1
cmp r2,#0x880000
blt onloop
str r1,[r4]
offloop:
add r2,r2,#1
cmp r2,#0xFF0000
blt offloop
b loop


