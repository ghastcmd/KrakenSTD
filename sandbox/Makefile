target = bin.exe

source = $(wildcard *.cpp *.s)

object = $(addsuffix .o,$(basename $(source)))

flags = -std=c++2a

comp_flags = -lntdll

build: $(target)

%.o: %.s
	g++ $(flags) -c $<  -o $@

%.o: %.cpp
	g++ $(flags) -c $< -o $@

$(target): $(object)
	g++ -o $@ $^ $(comp_flags)

run: clean build
	./$(target)

clean:
	rm -f $(object) $(target)