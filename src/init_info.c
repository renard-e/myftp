/*
** init_info.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May  9 09:04:11 2017 Gregoire Renard
** Last update Wed May 17 09:19:05 2017 Gregoire Renard
*/

#include "myftp.h"

static void		assign_func2(t_info *const info)
{
  info->tab[6].cmd = "PASV";
  info->tab[6].func = &pasv_func;
  info->tab[7].cmd = "PORT";
  info->tab[7].func = &port_func;
  info->tab[8].cmd = "HELP";
  info->tab[8].func = &help_func;
  info->tab[9].cmd = "NOOP";
  info->tab[9].func = &noop_func;
  info->tab[10].cmd = "RETR";
  info->tab[10].func = &retr_func;
  info->tab[11].cmd = "STOR";
  info->tab[11].func = &stor_func;
  info->tab[12].cmd = "LIST";
  info->tab[12].func = &list_func;
}

static void		assign_func(t_info * const info)
{
  info->tab[0].cmd = "USER";
  info->tab[0].func = &user_func;
  info->tab[1].cmd = "PASS";
  info->tab[1].func = &pass_func;
  info->tab[2].cmd = "CWD";
  info->tab[2].func = &cwd_func;
  info->tab[3].cmd = "CDUP";
  info->tab[3].func = &cdup_func;
  info->tab[4].cmd = "DELE";
  info->tab[4].func = &dele_func;
  info->tab[5].cmd = "PWD";
  info->tab[5].func = &pwd_func;
  assign_func2(info);
}

static int		assign_path(t_info * const info,
				    const char *path)
{
  DIR			*dir;

  if ((dir = opendir(path)) == NULL)
    return (ERROR);
  free(dir);
  if ((info->path = strdup(path)) == NULL)
    return (ERROR);
  if ((chdir(path)) == -1)
    return (ERROR);
  if ((info->path = get_current_dir_name()) == NULL)
    return (ERROR);
  return (SUCCESS);
}

static int		assign_port(t_info * const info,
				    const char *port)
{
  int			cpt;

  cpt = 0;
  while (port[cpt] != '\0')
    {
      if (port[cpt] < '0' || port[cpt] > '9')
	return (ERROR);
      cpt++;
    }
  if (cpt > 6)
    return (ERROR);
  info->port = atoi(port);
  return (SUCCESS);
}

int			init_info(t_info * const info,
				  char **argv)
{
  if ((assign_port(info, argv[1])) == ERROR)
    return (printf_error("Error : bad port"));
  if ((assign_path(info, argv[2])) == ERROR)
    return (printf_error("Error : bad path"));
  if ((malloc_ptr_func(info)) == ERROR)
    return (ERROR);
  assign_func(info);
  return (SUCCESS);
}
