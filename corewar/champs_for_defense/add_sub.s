.name           "add_sub"
.comment        "i am capable of adding and substracting, sir!"

load_values:		ld	%40, r1
					ld	%2, r2

add_sub:			add	r1, r2, r3
					sub	r1, r2, r4

store_into_memory:	st	r3, 20
					st	r4, 30
