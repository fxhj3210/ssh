CFLAGS += -Werror -Wall
pam_info_show.so: example.c
	gcc $(CFLAGS) -fPIC -shared -o $@ $< -lcurl -lpam
