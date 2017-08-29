/*
** my_read.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon May 15 14:05:15 2017 Gregoire Renard
** Last update Mon May 15 14:57:50 2017 Gregoire Renard
*/

#include "myftp.h"

char			*my_read(char const *file)
{
  struct stat		stat_ret;
  int			ret;
  int			fd;
  char			*buf;

  if ((stat(file, &stat_ret)) == -1)
    return (NULL);
  if ((buf = malloc(stat_ret.st_size + 1)) == NULL)
    return (NULL);
  if ((fd = open(file, O_RDONLY)) == -1)
    return (NULL);
  if ((ret = read(fd, buf, stat_ret.st_size)) == -1)
    return (NULL);
  buf[ret] = 0;
  return (buf);
}
