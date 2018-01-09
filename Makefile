.PHONY: run build
VMFILES     := ./src/vm/vm.h ./src/vm/vm.c
LEXERFILES  := ./src/lexer/lexer.h ./src/lexer/lexer.c src/lexer/token.h src/lexer/token.c
PARSERFILES := ./src/parser/parser.h ./src/parser/parser.c
DEBUGFILES	:= ./src/utils/debug.h ./src/utils/debug.c
default:
	@echo "No command provided"
	@echo "	build: To build."
	@echo "	debug: to debug and run."
	@echo "	run: to run."

build:
	@echo "Building.."
	@gcc -g -lm -m32 ./src/main.c ./src/glob.h ${VMFILES} ${LEXERFILES} ${PARSERFILES} ${DEBUGFILES} -o ./build/jax
	
run:
	@echo "Runing.."
	@./build/jax $(file)
	@echo "Done.."

debug:
	@./build/jax -d $(file)

clean:
	@echo "Cleaning.."
	@rm -rf ./build/*
	@sleep 1
	@echo "Done.."
	@sleep 1
	@clear
