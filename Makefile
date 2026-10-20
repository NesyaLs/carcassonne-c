IGRAPH_PATH ?= /usr/local
IGRAPH_LIBDIR = $(shell [ -e $(IGRAPH_PATH)/lib ] && \
        echo $(IGRAPH_PATH)/lib || \
        echo $(IGRAPH_PATH)/lib64)

CFLAGS = -std=gnu99 -Wall -Wextra -fPIC -g3 \
	-I$(IGRAPH_PATH)/include/igraph
LDFLAGS = -ligraph -lm -ldl -L$(IGRAPH_LIBDIR) -Wl,-rpath $(IGRAPH_LIBDIR)


#cherhceer si rpath ets une option du linker clang
S = src/

BASE_FILES = \
        deck.c

# Creating object files
%.o: src/%.c
	$(CC) $< $(CFLAGS) -c

%.o: tst/%.c
	$(CC) $< $(CFLAGS) --coverage -c

# Creating libraries
%.so:
	$(CC) $(LDFLAGS) -shared $^ -o $@

all: build install

# display: display.o
# 	$(CC) $^ $(LDFLAGS) -o $@

build: server client

server: deck.o board.o server_utils.o graph.o server.o
	$(CC) $^ $(LDFLAGS) -o $@ 

client: libplayer1.so libplayer2.so

libplayer1.so: player1.o deck.o player_utils.o graph.o board.o
libplayer2.so: player2.o deck.o player_utils.o graph.o board.o

alltests: board.o display.o graph.o player_utils.o test_board.o test_display.o test_graph.o test_project.o test_player_utils.o
	$(CC) $^ $(LDFLAGS) --coverage -o $@
	gcov $(filter test_%.o,$^)

test: alltests
	./alltests

install: server client alltests
	cp server libplayer1.so libplayer2.so alltests install/

clean:
	@rm -f *~ src/*~ *.o install/*.so install/server *.dot *.png server *.so alltests install/*.o install/alltests test*.gcov test*.gcda test*.gcno 

.PHONY: client install test clean build alltests

