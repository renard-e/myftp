/*
** init_server_exchange.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon May 15 16:08:44 2017 Gregoire Renard
** Last update Wed May 17 09:10:17 2017 Gregoire Renard
*/

#include "myftp.h"

static void		init_exchange(t_client * const client, int port)
{
  if (port == -1)
    client->exchange.s_in_server.sin_port = 0;
  else
    client->exchange.s_in_server.sin_port = htons(port);
  client->exchange.s_in_server.sin_family = AF_INET;
  client->exchange.s_in_server.sin_addr.s_addr = INADDR_ANY;
}

int			init_server_exchange(t_client * const client,
					     int port)
{
  client->exchange.len = sizeof(client->exchange.s_in_server);
  if ((client->exchange.pe = getprotobyname("TCP")) == NULL)
    return (ERROR);
  if ((client->exchange.fd_server =
       socket(AF_INET, SOCK_STREAM, client->exchange.pe->p_proto)) == -1)
    return (ERROR);
  init_exchange(client, port);
  if (((bind(client->exchange.fd_server,
	     (const struct sockaddr *)&client->exchange.s_in_server,
	     sizeof(client->exchange.s_in_server))) == -1)
      || ((listen(client->exchange.fd_server, MAX_QUEUE)) == -1)
      || ((getsockname(client->exchange.fd_server,
		       (struct sockaddr *)&client->exchange.s_in_server,
		       &client->exchange.len)) == -1))
    {
      close(client->exchange.fd_server);
      return (ERROR);
    }
  if (port == -1)
    client->exchange.port = ntohs(client->exchange.s_in_server.sin_port);
  return (SUCCESS);
}
