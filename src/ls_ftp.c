/*
** ls_ftp.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon May 15 09:30:48 2017 Gregoire Renard
** Last update Thu May 18 15:48:32 2017 Gregoire Renard
*/

#include "myftp.h"

static int		go_to_list(t_client * const client,
				   DIR *fd)
{
  struct dirent		*ret;

  if (client->mode == PASSIVE)
    {
      client->exchange.s_in_size_client =
	sizeof(client->exchange.s_in_client);
      if ((client->exchange.fd_client =
	   accept(client->exchange.fd_server,
		  (struct sockaddr *)&client->exchange.s_in_client,
		  &client->exchange.s_in_size_client)) == -1)
	return (ERROR);
    }
  my_send(client->fd_client, FILE_OK);
  while ((ret = readdir(fd)) != NULL)
    if ((my_send(client->exchange.fd_client, ret->d_name))
	== ERROR)
      return (ERROR);
  closedir(fd);
  my_send(client->fd_client, CLOSE_DATA);
  return (SUCCESS);
}

int			ls_ftp(t_order * const order,
			       t_client * const client)
{
  DIR			*fd;

  if (order->map[1] == NULL)
    {
      if ((fd = opendir(".")) == NULL)
	my_send(client->fd_client, ERROR_PERM);
    }
  else
    if ((fd = opendir(order->map[1])) == NULL)
      my_send(client->fd_client, ERROR_PERM);
  if (fd != NULL)
    if ((go_to_list(client, fd)) == ERROR)
      return (ERROR);
  return (SUCCESS);
}
