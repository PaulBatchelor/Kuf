default: example

kuf.c: kuf.org
	worgle -Werror -g kuf.org

example: example.c kuf.c
	$(CC) -Wall -pedantic -std=c89 $< kuf.c -o $@

clean:
	$(RM) kuf.c kuf.h
	$(RM) test
