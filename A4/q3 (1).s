.pos 0x1000
code:
    #v0 = s.x[i]
    ld $v0, r0                      # r0 = address of v0
    ld $s, r1                       # r1 = address of s.x
    ld $i, r2                       # r2 = address of i
    ld (r2), r2                     # r2 = i
    ld (r1, r2, 4), r3              # r3 = s.x[i]
    st r3, (r0)                     # v0 = r3   

    #v1 = s.y[i]
    ld $v1, r0                      # r0 = address of v1
    ld $s, r1                       # r1 = address of s
    ld 0x8(r1), r2                  # r2 = s.y
    ld $i, r3                       # r3 = address of i
    ld (r3), r3                     # r3 = i
    ld (r2, r3, 4), r4              # r4 = s.x[i]
    st r4, (r0)                     # v1 = r4

    #v2 = s.z->x[i]
    ld $v2, r0                      # r0 = address of v2
    ld $s, r1                       # r1 = address of s
    ld 0xc(r1), r2                  # r2 = s.z
    ld $i, r3                       # r3 = address of i
    ld (r3), r3                     # r3 = i
    ld (r2, r3, 4), r4              # r4 = s.z->x[i]
    st r4, (r0)                     # v2 = r4

    #v3 = s.z->z->y[i]
    ld $v3, r0                      # r0 = address of v3
    ld $s, r1                       # r1 = address of s
    ld 0xc(r1), r2                  # r2 = s.z
    ld 0xc(r2), r2                  # r2 = s.z->z
    ld 0x8(r2), r2                  # r2 = s.z->z->y
    ld $i, r3                       # r3 = address of i
    ld (r4), r3                     # r3 = i
    ld (r2, r3, 4), r4              # r4 = s.z->z->y[i]
    st r4, (r0)                     # v3 = r4

.pos 0x2000
static:
i:        .long 0                   # i
v0:       .long 0                   # v0
v1:       .long 0                   # v1
v2:       .long 0                   # v2
v3:       .long 0                   # v3
s:        .long 0                   # x[0]
          .long 0                   # x[1]
          .long s_y                 # y
          .long s_z                 # z


.pos 0x3000
heap:
s_y:        .long 0                 # s.y[0]
            .long 0                 # s.y[1]

.pos 0x4000
s_z:        .long 0                 # s.z.x[0]
            .long 0                 # s.z.x[1]
            .long s_y               # s.z->y
            .long s_z               # s.z->z

.pos 0x5000
s_z_z:     .long 0                 # s.z->z->x[0]
           .long 0                 # s.z->z->x[1]
           .long s_z_z_y           # s.z->z->y
           .long 0                 # s.z->z->z

.pos 0x6000
s_z_z_y:   .long 0                 # s.z->z->y[0]
           .long 0                 # s.z->z->y[1]
