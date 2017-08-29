/*
** order_client.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May  9 23:36:40 2017 Gregoire Renard
** Last update Wed May 17 09:25:45 2017 Gregoire Renard
*/

#include "myftp.h"

static int		init_order(t_order * const order)
{
  if ((order->buffer = malloc(1)) == NULL)
    return (ERROR);
  order->buffer[0] = 0;
  order->cpt = 1;
  order->stop = 0;
  return (SUCCESS);
}

static int		get_order(t_client * const client,
				  t_info * const info)
{
  t_order		order;

  order.client_stop = 0;
  client->login = 0;
  client->real_login = 0;
  client->mode = BASE;
  while (order.client_stop == 0)
    {
      if ((init_order(&order)) == ERROR)
	return (ERROR);
      while (order.stop == 0)
	if ((my_get_line(&order, client, info)) == ERROR)
	  return (ERROR);
      free(order.buffer);
    }
  return (SUCCESS);
}

static void		client_starter(t_client * const client,
				       t_info * const info)
{
  if ((my_send(client->fd_client, VALID)) == ERROR)
    exit_that(client);
  if ((get_order(client, info)) == ERROR)
    exit_that(client);
  exit_that(client);
}

int			order_client(t_server * const server,
				     t_client * const client,
				     t_info * const info)
{
  int			ret;

  while (1)
    {
      if ((client->fd_client =
	   accept(server->fd_server,
		  (struct sockaddr *)&client->s_in_client,
		  &client->s_in_size_client)) == -1)
	return (ERROR);
      if ((getsockname(client->fd_client,
		       (struct sockaddr *)&client->s_in_client,
		       &client->s_in_size_client)) == -1)
	return (ERROR);
      client->ip_serv = inet_ntoa(client->s_in_client.sin_addr);
      if ((ret = fork()) == 0)
	client_starter(client, info);
      else if (ret == -1)
	return (ERROR);
      else
	close(client->fd_client);
    }
  return (SUCCESS);
}
