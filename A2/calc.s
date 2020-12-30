.pos 0x100
                 ld $i, r0                        # r0 = address of i
                 ld $x, r1			  # r1 = address of x
                 ld $y, r2                        # r2 = address of y
                 ld $data, r3                     # r3 = address of data  
                 ld 0x0(r0), r7   
                 ld (r3, r7, 4), r4               # r4 = ith index of data
                 inc r7
                 ld (r3, r7, 4), r5
                 add r4, r5			  # load r2 with array[0]
                 st r5, (r2)
                 ld $0xff, r6
                 and r6, r5
                 st r1, (r5)

.pos 0x500

i: 	     .long 0x00000001
x:           .long 0x00000002
y:           .long 0x00000003

.pos 0x1000
data:           .long 0xffffffff         # data[0]
                .long 0xffffffff         # data[1]
                .long 0xffffffff         # data[2]
                .long 0xffffffff         # data[3]

