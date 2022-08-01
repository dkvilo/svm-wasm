CC 			:= clang
CFLAGS	:= --target=wasm32 --no-standard-libraries -Wl,--export-all -Wl,--no-entry

PHONY:
	$(CC) $(CFLAGS) -o app.wasm main.c
