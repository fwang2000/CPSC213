.pos 0x100
                 ld $array, r0
                 ld $t, r1 			  # r1 gets array address
                 ld 0x0(r0), r2			  # load r2 with array[0]
                 st r2, 0x0(r1)
                 ld 0x4(r0), r3			  # load r3 with array[1]
                 st r3, 0x0(r0)				  # store array[0] into r0
                 ld 0x0(r1), r4
                 st r4, 0x4(r0)
                 halt

.pos 0x500

t: 				 .long 0x00000001

.pos 0x1000
array:           .long 0xffffffff         # array[0]
                 .long 0x00000001         # array[1]
