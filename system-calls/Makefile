all: compile run pid info cleanup

compile: daemon.c
	@$(CC) -o testDaemon $?

run:
	@./testDaemon

pid:
	@$(eval PID=$(shell pgrep testDaemon))

info:
	@ps -p $(PID) -o "user pid ppid pgid sid tty command"

cleanup:
	@rm testDaemon