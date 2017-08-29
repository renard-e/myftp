/*
** check_port.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed May 17 09:12:41 2017 Gregoire Renard
** Last update Thu May 18 08:55:49 2017 Gregoire Renard
*/

#include "myftp.h"

int			check_port(char const *port)
{
  int			cpt;
  int			count;

  cpt = 0;
  count = 0;
  while (port[cpt] != '\0')
    {
      if (port[cpt] == ',')
	count++;
      cpt++;
    }
  if (count != 5)
    return (ERROR);
  return (SUCCESS);
}
