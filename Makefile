# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atok <atok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/28 15:42:17 by atok              #+#    #+#              #
#    Updated: 2022/12/31 00:56:09 by atok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minitalk.a
CC		= gcc
RM		= rm -rf
AR 		= ar rcs
CFLAGS	= -Wall -Wextra -Werror

SRC		= server.c client.c
OBJS	= $(SRC:.c=.o) #need .o just to make .a

SRCS_BONUS = server_bonus.c client_bonus.c
OBJS_BONUS = $(SRC:.c=.o)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME) bonus
	$(CC) $(CFLAGS) server.c -o server #compile without .o
	$(CC) $(CFLAGS) client.c -o client 
	$(RM) $(OBJS) # removed after making .a

bonus: $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS_BONUS)	
	$(CC) $(CFLAGS) server_bonus.c -o server_bonus
	$(CC) $(CFLAGS) client_bonus.c -o client_bonus
	$(RM) $(OBJS_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) server client server_bonus client_bonus #removed everything except .a
	
fclean: clean
	$(RM) $(NAME) #removed everythign include .a

re: fclean all