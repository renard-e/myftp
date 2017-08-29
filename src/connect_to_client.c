/*
** connect_to_client.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu May 18 14:26:05 2017 Gregoire Renard
** Last update Thu May 18 15:39:39 2017 Gregoire Renard
*/

#include "myftp.h"

int		connect_to_client(t_client * const client)
{
  if ((client->exchange.pe = getprotobyname("TCP")) == NULL)
    return (ERROR);
  if ((client->exchange.fd_client =
       socket(AF_INET,
	      SOCK_STREAM,
	      client->exchange.pe->p_proto)) == -1)
    return (ERROR);
  client->exchange.s_in_client.sin_family = AF_INET;
  client->exchange.s_in_client.sin_port = htons(client->exchange.port);
  client->exchange.s_in_client.sin_addr.s_addr =
    inet_addr(client->exchange.ip);
  if ((connect(client->exchange.fd_client,
	       (struct sockaddr *)&client->exchange.s_in_client,
	       sizeof(client->exchange.s_in_client))) == -1)
    return (ERROR);
  return (SUCCESS);
}
