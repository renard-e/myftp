/*
** main.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May  9 08:48:01 2017 Gregoire Renard
** Last update Thu May 11 13:53:46 2017 Gregoire Renard
*/

#include "myftp.h"

static void		free_info(t_info const info)
{
  int			cpt;

  cpt = 0;
  free(info.path);
  while (cpt != MAX_CMD)
    {
      free(info.tab[cpt].cmd);
      cpt++;
    }
}

int			main(int argc, char **argv)
{
  t_info		info;

  if (argc != 3)
    return (printf_error("Usage : ./server port path"));
  if ((init_info(&info, argv)) == ERROR)
    return (ERROR);
  if ((ftp_server(&info)) == ERROR)
    return (ERROR);
  free_info(info);
  return (SUCCESS);
}
