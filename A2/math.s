.pos 0x100
                 ld $a, r0
                 ld $b, r1 			  # r1 gets array address
                 ld 0x0(r0), r2
                 ld 0x0(r1), r3
                 ld 0x0(r1), r4
                 inc r3			  # load r2 with array[0]
                 inca r3
                 shr $1, r3
                 and r3, r4
                 shl $2, r4
                 st r4, (r0)
                 halt

.pos 0x500

a: 	     .long 0x00000001

.pos 0x1000
b:           .long 0xffffffff         # array[0]
