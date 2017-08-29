/*
** myftp.h for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/include
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May  9 08:47:31 2017 Gregoire Renard
** Last update Wed May 24 11:53:00 2017 Gregoire Renard
*/

#ifndef MYFTP_H_
#define MYFTP_H_

#define _GNU_SOURCE

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>

# define SUCCESS 1
# define ERROR -1
# define MAX_QUEUE 42
# define MAX_CMD 13

# define VALID "220 Service ready for new user"
# define MAYBE_READY "120 Service ready in nnn minutes."
# define START_TRANSFER "125 Data connection already open; transfer starting."
# define FILE_OK "150 File status okay; about to open data connection."
# define COMMAND_OK "200 Command okay."
# define HELP "214 Help message."
# define CLOSE "221 Service closing control connection."
# define CLOSE_DATA "226 Closing data connection."
# define LOGIN "230 User logged in, proceed."
# define RQT_FILE "250 Requested file action okay, completed."
# define PATH_CREA "257 PATHNAME created."
# define NEED_PASSWD "331 User name okay, need password."
# define NEED_ACCOUNT "332 Need account for login."
# define ERROR_UNLOG "530 Please login with USER and PASS."
# define ERROR_MSG "500 Unknown command."
# define ERROR_PERM "530 Permission denied."
# define LOGIN_INCO "530 Login incorrect."
# define ERROR_ARG "501 Syntax error in parameters or arguments."
# define ERROR_CMD_NO "502 Command not implemented."
# define ERROR_CHDIR "421 Service not available, closing control connection."
# define ERROR_CWD "550 Failed to change directory."
# define ERROR_DELE "550 Permission denied."
# define MODE_NEED "425 Use PORT or PASV first."
# define ILLEGAL_PORT "500 Illegal PORT command."
# define FAIL_OPEN "550 Failed to open file."
# define BAD_LINE "501 Syntax error in parameters or arguments."
# define MULTI_FILE "553 Requested action not taken."
# define ALL_HELP "214-The following commands are recognized.\nCDUP CWD DELE HELP LIST PASS PASV PORT PWD QUIT STOR USER \n214 Help OK."
# define ACTION_NO "550 Requested action not taken."
 
# define CMD_USER "USER <SP> <username> <CRLF> : Specify user for authentication"
# define CMD_PASS "PASS <SP> <password> <CRLF> : Specify password for authentication"
# define CMD_CWD "CWD <SP> <pathname> <CRLF> : Change working directory"
# define CMD_CDUP "CDUP <CRLF> : Change working directory"
# define CMD_QUIT "QUIT <CRLF> : Disconnection"
# define CMD_DELE "DELE <SP> <pathname> <CRLF> : Delete file on the server"
# define CMD_PWD "PWD <CRLF> : Print working directory"
# define CMD_PASV "PASV <CRLF> : Enable passive mode for data transfer"
# define CMD_PORT "PORT <SP> <host-port> <CRLF> : Enable active mode"
# define CMD_HELP "HELP [<SP> <string>] <CRLF> : List available commands"
# define CMD_NOOP "NOOP <CRLF> : Do nothing"
# define CMD_RETR "RETR <SP> <pathname> <CRLF> : Download file"
# define CMD_STOR "STOR <SP> <pathname> <CRLF> : Upload file from client"
# define CMD_LIST "LIST [<SP> <pathname>] <CRLF> : List files"

# define ACTIVE 10
# define PASSIVE -10
# define BASE 20

typedef struct		s_info t_info;

typedef struct		s_server
{
  int			fd_server;
  struct protoent	*pe;
  struct sockaddr_in	s_in_server;
}			t_server;

typedef struct		s_exchange
{
  int			fd_server;
  struct protoent	*pe;
  struct sockaddr_in	s_in_server;
  socklen_t		len;
  int			port;
  struct sockaddr_in	s_in_client;
  int			fd_client;
  socklen_t		s_in_size_client;
  char			*ip;
}			t_exchange;

typedef struct		s_client
{
  int			fd_client;
  socklen_t		s_in_size_client;
  struct sockaddr_in	s_in_client;
  int			login;
  int			real_login;
  char			*name;
  int			mode;
  t_exchange		exchange;
  char			*ip_serv;
}			t_client;

typedef struct		s_order
{
  char			buf[1];
  int			cpt;
  int			stop;
  int			client_stop;
  int			back;
  char			*buffer;
  char			**map;
}			t_order;

typedef	struct		s_pointer
{
  char			*cmd;
  int			(*func)(t_order * const order,
				t_client * const client,
				t_info * const info);
}			t_pointer;

typedef struct		s_info
{
  int			port;
  char			*path;
  t_pointer		tab[MAX_CMD];
}			t_info;

typedef struct		s_all
{
  int			size;
  int			cpt;
  int			x;
  int			y;
  char			**map;
}			t_all;

typedef struct		s_get_line
{
  char			buf[1];
  char			*buffer;
  int			stop;
  int			cpt;
  int			back;
}			t_get_line;

typedef struct		s_port
{
  int			idx;
  int			idx_map;
}			t_port;

int			printf_error(char *str);
int			init_info(t_info * const info, char **argv);
int			ftp_server(t_info * const info);
int			order_client(t_server * const server,
				     t_client * const client,
				     t_info * const info);
void			exit_that(t_client * const client);
int			my_get_line(t_order * const order,
				    t_client * const client,
				    t_info * const info);
int			my_send(int const fd, const char *str);
int			treatment(t_order * const order,
				  t_client * const client,
				  t_info * const info);
char			**my_str_to_wordtab(const char *str);
void			free_map(char **map);
void			print_map(char **map);
int			user_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			pass_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			cwd_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			cdup_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			dele_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			pwd_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			pasv_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			port_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			help_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			noop_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			retr_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			stor_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			list_func(t_order * const order,
				  t_client * const client,
				  t_info * const info);
int			malloc_ptr_func(t_info * const info);
void			choose_help(t_order * const order,
				    t_client * const client);
int			ls_ftp(t_order * const order,
			       t_client * const client);
char			*my_read(char const *file);
int			init_server_exchange(t_client * const client,
					     int port);
char			*compose_order(t_client * const client);
void			close_all_exchange(t_client * const client);
int			send_file(t_client * const client, char *file);
int			read_file(t_client * const client,
				  char const *file);
int			check_port(char const *port);
int			create_port(t_client * const client,
				    t_order * const order);
int			strlen_map(char **map);
void			all_help(t_client * const client);
int			connect_to_client(t_client * const client);

#endif /* !MYFTP_H_ */
