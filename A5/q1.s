# Code - TODO: Comment and translate to C in q1()
.pos 0x1000

# C statement 1
S1:
# v0 = x[i]
ld    $i, r0            # r0 = address of i
ld    (r0), r0          # r0 = i
ld    $a, r1            # r1 = address of a
ld    (r1), r1          # r1 = a
ld    (r1), r1          # r1 = x
ld    (r1, r0, 4), r2   # r2 = x[i]
ld    $v0, r3           # r3 = address of v0
st    r2, (r3)          # v0 = x[i]

# C statement 2
S2:
#v1 = y[i]
ld    $i, r0            # r0 = address of i
ld    (r0), r0          # r0 = i
ld    $a, r1            # r1 = address of a
ld    (r1), r1          # r1 = a
inca  r1                # r1 = b / y[0]
ld    (r1, r0, 4), r2   # r2 = y[i]
ld    $v1, r3           # r3 = address of v1
st    r2, (r3)          # v1 = y[i]

# C statement 3
S3:
# v2 = x1[i]
ld    $i, r0            # r0 = address of i
ld    (r0), r0          # r0 = i
ld    $a, r1            # r1 = address of a
ld    (r1), r1          # r1 = a
ld    20(r1), r1        # r1 = address of x1[0]
ld    (r1), r1          # r1 = x1[0]
ld    (r1, r0, 4), r2   # r2 = x1[i]
ld    $v2, r3           # r3 = address of v2
st    r2, (r3)          # v2 = x1[i]

# C statement 4
S4:
# x1[0] = x0[0]
ld    $a, r1            # r1 = address of a
ld    (r1), r1          # r1 = a
st    r1, 20(r1)        # int* x1 = int* x

# C statement 5
S5:
#v3 = y1[i]
ld    $i, r0            # r0 = address of i
ld    (r0), r0          # r0 = i
ld    $a, r1            # r1 = address of a
ld    (r1), r1          # r1 = a
ld    20(r1), r1        # r1 = address of x1[0]
inca  r1                # r1 = b / y1[0]
ld    (r1, r0, 4), r2   # r2 = y1[i]
ld    $v3, r3           # r3 = address of v3
st    r2, (r3)          # v3 = y1[i]


halt


## Globals
.pos 0x2000
i:  .long 1
v0: .long 0
v1: .long 0
v2: .long 0
v3: .long 0
a:  .long d0


## Heap (these labels represent dynamic values and are thus not available to code)
.pos 0x3000
#struct A
d0: .long d1          # x
    .long 20          # b / y[0]
    .long 21          # y[1]
    .long 22          # y[2]
    .long 23          # y[3]
    .long d2          # struct A
#struct A
d2: .long d3          # x1
    .long 40          # b1 / y1[0]
    .long 41          # y1[1]
    .long 42          # y1[2]
    .long 43          # y1[3]
    .long 0           # struct A* a (NULL)
#x
d1: .long 10          # x[0]
    .long 11          # x[1]
    .long 12          # x[2]
    .long 13          # x[3]
#x1
d3: .long 30          # x1[0]
    .long 31          # x1[1]
    .long 32          # x1[2]
    .long 33          # x1[3]
