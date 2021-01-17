min_flags = -s -O3 -pedantic -no-pie -fno-asynchronous-unwind-tables -std=c++2a \
-ffreestanding -nostdlib -fno-stack-protector -fdata-sections -ffunction-sections

linker_flags = -s --build-id=none

alert_flags = -Wall -Werror -Wextra
comp_flags = -std=c++2a -fconcepts

CC = g++

LINKER = ld

src = src
obj = bin

source = $(wildcard $(addprefix $(src)/*.,cpp s))
object = $(patsubst %,$(obj)/%.o, $(notdir $(basename $(source))))

target = $(obj)/bin

VPATH = $(src)
$(obj)/%.o: %.cpp
	@echo Compiling intermediate $< to $@
	@$(CC) $(min_flags) $(comp_flags) $(alert_flags) -c $< -o $@

$(obj)/%.o: %.s
	@echo Compiling intermediate $< to $@
	@$(CC) $(min_flags) $(comp_flags) $(alert_flags) -x assembler-with-cpp -c $< -o $@

$(target): $(object)
	@echo Compiling target $@ from $^
	@$(CC) $(min_flags) $^ -o $@
# @$(LINKER) $(linker_flags) $^ -o $@

build: $(target)

run: build
	@$(target)

help:
	@echo $(source)
	@echo $(object)

clean:
	@echo Cleaning object files
	@rm -f $(obj)/*.o
	@echo Cleaning target binary
	@rm -f $(target)
