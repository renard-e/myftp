/*
** close_all_exchange.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May 16 20:33:02 2017 Gregoire Renard
** Last update Tue May 16 20:35:19 2017 Gregoire Renard
*/

#include "myftp.h"

void			close_all_exchange(t_client * const client)
{
  client->mode = BASE;
  close(client->exchange.fd_server);
  close(client->exchange.fd_client);
}
