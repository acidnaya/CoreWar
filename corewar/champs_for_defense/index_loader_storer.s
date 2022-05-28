.name           "loader_storer_by_index"
.comment        "not your regular loader_storer"

load_index:			ldi	0, %0, r1
					ldi	%0, %512, r2
					ldi	r1, r2, r3
long_load_index:	lldi %0, %512, r4
store_index:		sti	r1, %30, r1
					sti	r2, %70, r1
					sti	r3, %70, r1
					sti	r4, %70, r1

