##
## Makefile for  in /home/renard_e/poubelle_test/test_strace
## 
## Made by Gregoire Renard
## Login   <renard_e@epitech.net>
## 
## Started on  Mon Apr  3 11:33:34 2017 Gregoire Renard
## Last update Thu May 18 14:48:31 2017 Gregoire Renard
##

CC	=	gcc -Iinclude

RM	=	rm -fr

SRCS	=	main.c \
		src/printf_error.c \
		src/init_info.c \
		src/ftp_server.c \
		src/order_client.c \
		src/exit_that.c \
		src/my_get_line.c \
		src/my_send.c \
		src/treatment.c \
		src/my_str_to_wordtab.c \
		src/free_map.c \
		src/print_map.c \
		src/func1.c \
		src/func2.c \
		src/func3.c \
		src/malloc_ptr_func.c \
		src/choose_help.c \
		src/ls_ftp.c \
		src/my_read.c \
		src/init_server_exchange.c \
		src/compose_order.c \
		src/close_all_exchange.c \
		src/send_file.c \
		src/read_file.c \
		src/check_port.c \
		src/create_port.c \
		src/strlen_map.c \
		src/connect_to_client.c \

OBJS	=	$(SRCS:.c=.o)

NAME	=	server

CFLAGS	=	-W -Werror -Wall -Wextra

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(SRCS)

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all re clean fclean

