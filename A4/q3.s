.pos 0x1000
code:

ld $v0, r0			# r0 = address of v0
ld $i, r1			# r1 = address of i
ld (r1),  r2		# r2 = value of i
ld $s, r3			# r3 = address of s
ld (r3, r2, 4), r4 	# r4 = s.x[i]
st r4, (r0)			# v0 = s.x[i]
halt 

#v1 = s.y[i]
ld $s, r0			# r0 = s
ld $i, r1			# r1 = i
ld (r1), r1			# r1 = value of i
ld 0x8(r0), r2		# r2 = address of s.y
ld (r2, r1, 4), r3	# r3 = s.y[i]
ld $v1, r4			# r4 = address of v1
st r3, (r4)			# v1 = s.y[i]
halt

#v2 = s.z->x[i]
ld $v2, r0			# r0 = address of v2
ld $s, r1			# r1 = address of s
ld 0xc(r1), r1		# r1 = s.z
ld $i, r2			# r2 = address of i
ld (r2), r2			# r2 = i
ld (r1, r2, 4), r3	# r3 = s.z->x[i]
st r3, (r0)			# v2 = s.z->x[1]
halt

#v3 = s.z->z->y[i]
ld $v3, r0			# r0 = address of v3
ld $s, r1			# r1 = address of s
ld 0xc(r1), r1		# r1 = s.z
ld $i, r2			# r2 = address of i
ld (r2), r2			# r2 = i
ld 0xc(r1), r1		# r1 = s.z->z
ld 0x8(r1), r1		# r1 = s.z->z->y
ld (r1, r2, 4), r3	# r3 = s.z->z->y[i]
st r3, (r0)			# v3 = s.z->z->y[i]
halt

.pos 0x2000
static: 
i:  	.long 1
v0: 	.long 0
v1: 	.long 0
v2: 	.long 0
v3: 	.long 0
s:  	.long 0  	# x[0]
		.long 0  	# x[1]
		.long s_y  	# *y
		.long s_z  	# *z


.pos 0x3000
heap:
s_y:	.long 0		# y[0]
		.long 0 	# y[1]

.pos 0x4000
s_z: 	.long 0 	# s_z->x[0]
		.long 0		# s_z->x[1]
		.long 0		# s_z->y
		.long s_z_z		# s.z->z

.pos 0x5000
s_z_z:	.long 0		# s_z_z->x[0]
		.long 0 	# s_z_z->x[1]
		.long s_z_z_y 	#s.z.z->y
		.long 0

.pos 0x6000
s_z_z_y: .long 3	# s_z_z_y[0]
		 .long 2 	# s_z_z_y[1]