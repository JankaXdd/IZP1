default: setcal

setcal: setcal.c
	gcc -std=c99 -Wall -Wextra -Werror setcal.c -o setcal 

clean:
	rm -f setcalls