TARGET = build\onegin.exe
CPPFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE -Werror=vla

.PHONY: all
all: $(TARGET)

$(TARGET): bin\main.o bin\sorting.o bin\interface.o
	g++ bin\main.o bin\sorting.o bin\interface.o -o $(TARGET) $(CPPFLAGS)

bin\main.o: main.cpp common.h sorting.h interface.h
	g++ -c main.cpp -o bin\main.o $(CPPFLAGS)

bin\sorting.o: sorting.cpp sorting.h common.h
	g++ -c sorting.cpp -o bin\sorting.o $(CPPFLAGS)

bin\interface.o: interface.cpp interface.h common.h
	g++ -c interface.cpp -o bin\interface.o $(CPPFLAGS)