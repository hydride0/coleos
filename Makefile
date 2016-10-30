build: src/koleos.c
	@$$CC -lreadline -o koleos src/{koleos,utils,cd}.c
