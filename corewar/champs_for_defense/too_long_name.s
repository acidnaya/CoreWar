.name "our champ just enough power to mess it up just enough power to mess it up just enough power to mess it up just enough power to mess it up just enough power to mess it up just enough power to mess it up just enough power to mess it up just enough power to mess it up just enough power to mess it up just enough power to mess it up"
.comment "just enough power to mess it up"

start:
	sti	r1, %:live_loop, %1
	sti	r1, %:live, %1
	ld	%1, r3

forks: #пока во втором регистре число меньше 16, кэрри = фолс
	add	r2, r3, r2
	xor	r2, %10, r4

live:
	live 	%4
	zjmp	%:turn_on_carry #первые 10 проходок не можем прыгнуть сюда и форкаемся
	fork	%:forks
	ld	%0, r4
	zjmp	%:forks

turn_on_carry:
	ld	%0, r4

live_loop:
	live %4 # на шестнадцатый раз уходим в вечный лайв
	zjmp %:live_loop

