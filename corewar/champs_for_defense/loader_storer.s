.name           "loader-storer"
.comment        "loading is cool and storing is cool"

load_value:			ld	%42, r1
load_by_index:		ld	0, r2
store_into_reg:		st	r1, r3
store_into_memory1:	st	r3, 10
store_into_memory2:	st	r2, 10
