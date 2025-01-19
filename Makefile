PWD = $(shell pwd)

FULL_SANITIZE = -fsanitize=address -fsanitize=undefined
NO_SANITIZE =
SANITIZE = ${NO_SANITIZE}

FULL_OPTIMIZE = -O3 -flto=auto -fdevirtualize-at-ltrans -march=native -mtune=native -fmodulo-sched -fmodulo-sched-allow-regmoves -fgcse-sm -fgcse-las -fdevirtualize-at-ltrans -fgraphite-identity -floop-nest-optimize -fsched-pressure -ftree-loop-im -ftree-loop-ivcanon -fivopts
NO_OPTIMIZE = -O0
OPTIMIZE = ${NO_OPTIMIZE}

MAIN_INPUTS = main.cpp scanner.cpp tokenizer.cpp MicroGC/gc.cpp string.cpp stringbuf.cpp record.cpp term.cpp read.cpp print.cpp evaluate.cpp stack.cpp abs.cpp app.cpp ref.cpp ext.cpp shr.cpp
MAIN_HEADERS = Makefile strclone.hpp scanner.hpp tokenizer.hpp MicroGC/gc.hpp string.hpp stringbuf.hpp record.hpp term.hpp read.hpp print.hpp evaluate.hpp stack.hpp abs.hpp app.hpp ref.hpp ext.hpp shr.hpp

MAIN_NAME = main
MAIN_CDB_RECIPE = g++ -o ${MAIN_NAME} -std=c++2a ${MAIN_INPUTS}
MAIN_RECIPE = g++ -o ${MAIN_NAME} -g3 -std=c++2a ${OPTIMIZE} ${SANITIZE} ${MAIN_INPUTS}

.PHONY: compile_commands.json

${MAIN_NAME}: ${MAIN_INPUTS} ${MAIN_HEADERS}
	${MAIN_RECIPE}

compile_commands.json:
	echo "[{ \"directory\": \"${PWD}\", \"command\": \"${MAIN_CDB_RECIPE}\", \"file\": \"*.cpp\" }]" > compile_commands.json

clean:
	rm -f ${MAIN_NAME}