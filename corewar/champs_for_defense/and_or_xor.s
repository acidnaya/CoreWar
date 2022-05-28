.name           "and_or_xor"
.comment        "i'm your bitwise daddy"

load_values:		ld	%5, r1
					ld	%3, r2

add_sub:			and	r1, r2, r3
					or	%5, %5, r4
					xor	-1, 2, r5

store_into_memory:	st	r3, 50
					st	r4, 60
					st	r5, 70
