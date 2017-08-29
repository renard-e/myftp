/*
** my_send.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed May 10 20:15:16 2017 Gregoire Renard
** Last update Tue May 16 19:23:58 2017 Gregoire Renard
*/

#include <errno.h>
#include "myftp.h"

int			my_send(int const fd, const char *str)
{
  if ((write(fd, str, strlen(str))) == ERROR)
    return (ERROR);
  if ((write(fd, "\r\n", 2)) == ERROR)
    return (ERROR);
  return (SUCCESS);
}
