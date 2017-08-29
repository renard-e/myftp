/*
** send_file.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May 16 20:46:02 2017 Gregoire Renard
** Last update Thu May 18 15:10:05 2017 Gregoire Renard
*/

#include "myftp.h"

int			send_file(t_client * const client,
				  char *file)
{
  if (client->mode == PASSIVE)
    {
      if ((client->exchange.fd_client =
	   accept(client->exchange.fd_server,
		  (struct sockaddr *)&client->exchange.s_in_client,
		  &client->exchange.s_in_size_client)) == -1)
	return (ERROR);
    }
  my_send(client->fd_client, FILE_OK);
  write(client->exchange.fd_client, file, strlen(file));
  my_send(client->fd_client, CLOSE_DATA);
  close_all_exchange(client);
  free(file);
  return (SUCCESS);
}
