/*
** malloc_ptr_func.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu May 11 13:54:33 2017 Gregoire Renard
** Last update Thu May 11 13:55:49 2017 Gregoire Renard
*/

#include "myftp.h"

int			malloc_ptr_func(t_info * const info)
{
  int			cpt;

  cpt = 0;
  while (cpt != MAX_CMD)
    {
      if ((info->tab[cpt].cmd = malloc(6)) == NULL)
	return (ERROR);
      cpt++;
    }
  return (SUCCESS);
}
