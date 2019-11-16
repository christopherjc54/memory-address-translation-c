all: part1 part2 part3 runall md5
	
part1:
	gcc src/part1.c src/data.c -o output/part1 -w
part2:
	gcc src/part2.c src/program.c src/data.c src/frame.c src/pagetable.c src/phypages.c -o output/part2 -lm -w
part3:
	gcc src/part3.c src/program.c src/data.c src/frame.c src/pagetable.c src/phypages.c -o output/part3 -lm -w
runall: runpart1 runpart2 runpart3
	
runpart1:
	output/part1 "$(CURDIR)/sequences/part1sequence" output/part1-out > output/part1-console.txt
runpart2:
	output/part2 "$(CURDIR)/sequences/part2sequence" output/part2-out > output/part2-console.txt
runpart3:
	output/part3 128 4096 1024 "$(CURDIR)/sequences/part2sequence" output/part3-out > output/part3-console.txt
md5:
	md5sum output/part1-out output/part2-out output/part3-out
clean:
	rm -f output/*