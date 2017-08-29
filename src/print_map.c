/*
** print_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu May 11 10:17:34 2017 Gregoire Renard
** Last update Thu May 11 10:46:31 2017 Gregoire Renard
*/

#include "myftp.h"

void			print_map(char **map)
{
  int			cpt;

  cpt = 0;
  while (map[cpt] != NULL)
    {
      printf("*%s*\n", map[cpt]);
      cpt++;
    }
}
