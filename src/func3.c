/*
** func3.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu May 11 13:36:46 2017 Gregoire Renard
** Last update Thu May 18 15:47:46 2017 Gregoire Renard
*/

#include "myftp.h"

int			retr_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  char			*file;

  (void)info;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else if (client->mode == BASE)
    my_send(client->fd_client, MODE_NEED);
  else if (order->map[1] == NULL)
    my_send(client->fd_client, FAIL_OPEN);
  else
    {
      if ((file = my_read(order->map[1])) == NULL)
	my_send(client->fd_client, FAIL_OPEN);
      else
	send_file(client, file);
      close_all_exchange(client);
    }
  return (SUCCESS);
}

int			stor_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)info;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else if (client->mode == BASE)
    my_send(client->fd_client, MODE_NEED);
  else if (order->map[1] == NULL)
    my_send(client->fd_client, BAD_LINE);
  else
    {
      if ((access(order->map[1], R_OK)) == 1)
	my_send(client->fd_client, MULTI_FILE);
      else
	{
	  my_send(client->fd_client, FILE_OK);
	  read_file(client, order->map[1]);
	  my_send(client->fd_client, CLOSE_DATA);
	  close_all_exchange(client);
	}
    }
  return (SUCCESS);
}

int			list_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)info;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else if (client->mode == BASE)
    my_send(client->fd_client, MODE_NEED);
  else
    {
      if ((ls_ftp(order, client)) == ERROR)
	my_send(client->fd_client, ERROR_CHDIR);
      close_all_exchange(client);
    }
  return (SUCCESS);
}
