min_flags = -s -O3 -pedantic -no-pie -fno-asynchronous-unwind-tables -std=c++2a \
-ffreestanding -nostdlib -fno-stack-protector -fdata-sections -ffunction-sections

linker_flags = -s --build-id=none

alert_flags = -fconcepts -Wall -Werror -Wextra

CC = g++

LINKER = ld

src = src
obj = bin

source = $(wildcard $(addprefix $(src)/*.,cpp s))
object = $(patsubst %,$(obj)/%.o, $(notdir $(basename $(source))))

target = $(obj)/bin

VPATH = $(src)
$(obj)/%.o: %.cpp
	@echo Compiling $< to $@
	@$(CC) $(min_flags) $(alert_flags) -c $< -o $@

$(obj)/%.o: %.s
	@echo Compiling $< to $@
	@$(CC) $(min_flags) $(alert_flags) -c $< -o $@

$(target): $(object)
	@echo Compiling $^ to $@
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
