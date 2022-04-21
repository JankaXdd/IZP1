default: pwcheck

setcal: pwcheck.c
	gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck 

clean:
	rm -f pwcheck