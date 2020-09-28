all: ScreenSaver

%: %.c
	gcc -o $@ $< -lncursesw
