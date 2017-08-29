/*
** free_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu May 11 10:12:02 2017 Gregoire Renard
** Last update Thu May 11 10:12:58 2017 Gregoire Renard
*/

#include "myftp.h"

void			free_map(char **map)
{
  int			cpt;

  cpt = 0;
  while (map[cpt] != NULL)
    {
      free(map[cpt]);
      cpt++;
    }
  free(map);
}
