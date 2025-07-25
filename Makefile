CC      = cc
RM      = rm -rf
CFLAGS  = -Wall -Wextra -Werror -Ift_printf/includes
LFTPRINTF = ft_printf/libftprintf.a

CLIENT  = client
SERVER  = server

CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJ) $(LFTPRINTF)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LFTPRINTF) -o $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(LFTPRINTF)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LFTPRINTF) -o $(SERVER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(CLIENT) $(SERVER)

re: fclean all