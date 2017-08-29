/*
** strlen_map.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed May 17 17:22:58 2017 Gregoire Renard
** Last update Wed May 17 17:54:39 2017 Gregoire Renard
*/

#include "myftp.h"

int			strlen_map(char **map)
{
  int			cpt;

  cpt = 0;
  while (map[cpt] != NULL)
    cpt++;
  return (cpt);
}
