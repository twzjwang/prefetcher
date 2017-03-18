CFLAGS = -msse2 -mavx2 --std gnu99 -O0 -Wall -Wextra

GIT_HOOKS := .git/hooks/applied

all: $(GIT_HOOKS) main.c
	$(CC) $(CFLAGS) -o main main.c

test_perf: main
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./main NAI
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./main SSE
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./main SSE_PF
	perf stat --repeat 5 \
		-e cache-misses,cache-references,instructions,cycles \
		./main AVX

verify: verify.c 
	$(CC) $(CFLAGS) $^ -o $@
	./verify 8
		
cal_avr: cal_avr.c
	$(CC) $(CFLAGS) $^ -o $@
	
test_exetime: main cal_avr
	for i in `seq 1 1 5`; do \
		./main NAI; \
	done > NAI_out.txt
	for i in `seq 1 1 5`; do \
		./main SSE; \
	done > SSE_out.txt
	for i in `seq 1 1 5`; do \
		./main SSE_PF; \
	done > SSE_PF_out.txt
	for i in `seq 1 1 5`; do \
		./main AVX; \
	done > AVX_out.txt
	./cal_avr 5
    
$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(RM) main cal_avr NAI_out.txt SSE_out.txt SSE_PF_out.txt AVX_out.txt verify

