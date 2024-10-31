CC=gcc
CFLAGS=-O2 -Wall -Wformat -Wformat=2 -Wconversion -Wimplicit-fallthrough -Werror=format-security \
	-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 -D_GLIBCXX_ASSERTIONS \
	-fstrict-flex-arrays=3 -fstack-clash-protection -fstack-protector-strong \
	-Wl,-z,nodlopen -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now
VG=valgrind
VFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes
OBJECTS=$(patsubst %.c,%.o,$(wildcard *.c))
INSTALLDIR=$(HOME)/.local/bin

all: $(OBJECTS)

compile: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

test: compile
	@$(foreach obj,$(OBJECTS),$(VG) $(VFLAGS) ./$(obj);)

clean:
	-rm -f *.o

install: compile
	@$(foreach obj,$(OBJECTS),cp $(obj) $(INSTALLDIR)/rofi-$(subst .o,,$(obj));)

uninstall:
	@$(foreach obj,$(OBJECTS),rm -f $(INSTALLDIR)/$(obj);)

run:
	rofi -modes "$(MODE):./$(MODE).o" -show $(MODE) 

