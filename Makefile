min_flags = -s -O3 -pedantic -no-pie -fno-asynchronous-unwind-tables -std=c++17\
-ffreestanding -nostdlib -fno-stack-protector -fdata-sections -ffunction-sections

linker_flags = -s --build-id=none

alert_flags = -Wall -Werror

CC = g++

LINKER = ld

%.o: %.cpp
	@echo Compiling $< to $@
	@$(CC) $(min_flags) $(alert_flags) -c $<

%.o: %.s
	@echo Compiling $< to $@
	@$(CC) $(min_flags) $(alert_flags) -c $<

bin.exe: $(addsuffix .o,$(basename $(wildcard *.cpp *.s)))
	@echo Compiling $< to $@
	@$(LINKER) $(linker_flags) $^ -o $@
#@$(CC) $(min_flags) $(alert_flags) $^ -o $@

build: bin.exe

run: build
	@./bin.exe

clean:
	rm -f *.o
	rm -f code.exe
	rm -f bin.exe
	rm -f a.out
