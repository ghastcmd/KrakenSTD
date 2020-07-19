min_flags = -s -O3 -pedantic -no-pie -fno-asynchronous-unwind-tables -std=c++17 \
-ffreestanding -nostdlib -fno-stack-protector -fdata-sections -ffunction-sections

linker_flags = -s --build-id=none

alert_flags = -Wall -Werror -Wextra

CC = g++

LINKER = ld

%.o: %.cpp
	@echo Compiling $< to $@
	@$(CC) $(min_flags) $(alert_flags) -c $<

%.o: %.s
	@echo Compiling $< to $@
	@$(CC) $(min_flags) $(alert_flags) -c $<

files = $(addsuffix .o,$(basename $(wildcard *.cpp *.s)))
bin.exe: $(files)
	@echo Compiling $^ to $@
	@$(CC) $(min_flags) $^ -o $@
# @$(LINKER) $(linker_flags) $^ -o $@

build: bin.exe

run: build
	@./bin.exe

clean:
	rm -f *.o
	rm -f code.exe
	rm -f bin.exe
	rm -f a.out
