# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfandres <hfandres@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 10:36:28 by hfandres          #+#    #+#              #
#    Updated: 2025/05/07 11:38:55 by hfandres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

AR = ar rsc

RM = rm -rf

CFLAG = -Wall -Wextra -Werror

SRCS = srcs/ft_printf.c \
		srcs/ft_utility.c \
		srcs/ft_display_char.c \
		srcs/ft_display_str.c \
		srcs/ft_display_nbr.c \
		srcs/ft_display_nbru.c \
		srcs/ft_display_ptr.c \
		srcs/ft_display.c \
		srcs/ft_display_hex.c \

BONUS_SRCS = srcs/ft_printf_bonus.c \
		srcs/ft_utility_bonus.c \
		srcs/ft_display_char_bonus.c \
		srcs/ft_display_str_bonus.c \
		srcs/ft_display_nbr_bonus.c \
		srcs/ft_display_nbru_bonus.c \
		srcs/ft_display_ptr_bonus.c \
		srcs/ft_display_bonus.c \
		srcs/ft_flags_bonus.c \
		srcs/ft_display_hex_bonus.c \

OBJS_LFT = libft/ft_isalpha.o \
		libft/ft_isdigit.o \
		libft/ft_isalnum.o \
		libft/ft_isascii.o \
		libft/ft_isprint.o \
		libft/ft_strlen.o \
		libft/ft_memset.o \
		libft/ft_bzero.o \
		libft/ft_memcpy.o \
		libft/ft_memmove.o \
		libft/ft_strlcpy.o \
		libft/ft_strlcat.o \
		libft/ft_toupper.o \
		libft/ft_tolower.o \
		libft/ft_strchr.o \
		libft/ft_strrchr.o \
		libft/ft_strncmp.o \
		libft/ft_memchr.o \
		libft/ft_memcmp.o \
		libft/ft_strnstr.o \
		libft/ft_atoi.o \
		libft/ft_substr.o \
		libft/ft_strjoin.o \
		libft/ft_strtrim.o \
		libft/ft_calloc.o \
		libft/ft_strdup.o \
		libft/ft_split.o \
		libft/ft_itoa.o \
		libft/ft_strmapi.o \
		libft/ft_striteri.o \
		libft/ft_putchar_fd.o \
		libft/ft_putstr_fd.o \
		libft/ft_putendl.o \
		libft/ft_putnbr_fd.o \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(BONUS_SRCS:.c=.o)

NAME = libftprintf.a

all : $(NAME)

LFT = libft/libft.a

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(LFT) $(OBJS)
	$(AR) -o $(NAME) $(OBJS) $(OBJS_LFT)

bonus: $(LFT) $(OBJS_BONUS)
	@make -s clean_a
	$(AR) -o $(NAME) $(OBJS_BONUS) $(OBJS_LFT)

clean :
	make -C libft clean
	$(RM) $(OBJS) $(OBJS_BONUS)

$(LFT) :
	make -C libft

fclean : clean
	make -C libft clean
	$(RM) -rf libft/libft.a
	$(RM) $(NAME)

re : fclean
	make

clean_a :
	$(RM) $(NAME)

.PHONY : bonus clean fclean re all 
