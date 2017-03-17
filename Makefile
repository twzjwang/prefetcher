CFLAGS = -msse2 --std gnu99 -O0 -Wall -Wextra

GIT_HOOKS := .git/hooks/applied

EXEC = naive_transpose sse_transpose sse_prefetch_transpose

all: $(GIT_HOOKS) main.c $(EXEC)

naive_transpose: main.c
	$(CC) $(CFLAGS) -DNAI -o $@ main.c
    
sse_transpose: main.c
	$(CC) $(CFLAGS) -DSSE -o $@ main.c
    
sse_prefetch_transpose: main.c
	$(CC) $(CFLAGS) -DSSE_PF -o $@ main.c

test: $(EXEC)
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./naive_transpose
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./sse_transpose
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./sse_prefetch_transpose  
    
$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(RM) $(EXEC)
