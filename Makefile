CFLAGS = -msse2 --std gnu99 -O0 -Wall -Wextra

GIT_HOOKS := .git/hooks/applied

all: $(GIT_HOOKS) main.c
	$(CC) $(CFLAGS) -o main main.c

test: main
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./main NAI
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./main SSE
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./main SSE_PF
    
$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(RM) main
