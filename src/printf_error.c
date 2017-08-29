/*
** printf_error.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May  9 08:54:02 2017 Gregoire Renard
** Last update Tue May  9 08:55:53 2017 Gregoire Renard
*/

#include "myftp.h"

int			printf_error(char *str)
{
  printf("%s\n", str);
  return (ERROR);
}
