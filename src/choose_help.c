/*
** choose_help.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Fri May 12 10:25:06 2017 Gregoire Renard
** Last update Thu May 18 13:49:06 2017 Gregoire Renard
*/

#include "myftp.h"

static void		choose_help2(t_order * const order,
				     t_client * const client,
				     char *str)
{
  if ((strcmp(order->map[1], "PWD")) == 0)
    str = CMD_PWD;
  else if ((strcmp(order->map[1], "PASV")) == 0)
    str = CMD_PASV;
  else if ((strcmp(order->map[1], "PORT")) == 0)
    str = CMD_PORT;
  else if ((strcmp(order->map[1], "HELP")) == 0)
    str = CMD_HELP;
  else if ((strcmp(order->map[1], "NOOP")) == 0)
    str = CMD_NOOP;
  else if ((strcmp(order->map[1], "RETR")) == 0)
    str = CMD_RETR;
  else if ((strcmp(order->map[1], "STOR")) == 0)
    str = CMD_STOR;
  else if ((strcmp(order->map[1], "LIST")) == 0)
    str = CMD_LIST;
  if (str == NULL)
    str = ERROR_CMD_NO;
  my_send(client->fd_client, str);
}

void			choose_help(t_order * const order,
				    t_client * const client)
{
  char			*str;

  str = NULL;
  if ((strcmp(order->map[1], "USER")) == 0)
    str = CMD_USER;
  else if ((strcmp(order->map[1], "PASS")) == 0)
    str = CMD_PASS;
  else if ((strcmp(order->map[1], "CWD")) == 0)
    str = CMD_CWD;
  else if ((strcmp(order->map[1], "CDUP")) == 0)
    str = CMD_CDUP;
  else if ((strcmp(order->map[1], "QUIT")) == 0)
    str = CMD_QUIT;
  else if ((strcmp(order->map[1], "DELE")) == 0)
    str = CMD_DELE;
  choose_help2(order, client, str);
}
