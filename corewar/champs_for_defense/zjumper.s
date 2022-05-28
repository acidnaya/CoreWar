.name           "jumper"
.comment        "hop hop hop hop hop"

fail:		zjmp	%50

success:	ld %0, r2
			zjmp %50
