/*
** exit_that.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May  9 23:53:26 2017 Gregoire Renard
** Last update Mon May 15 19:39:33 2017 Gregoire Renard
*/

#include "myftp.h"

void			exit_that(t_client * const client)
{
  close(client->fd_client);
  exit(0);
}
