/*
** read_file.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Tue May 16 21:36:19 2017 Gregoire Renard
** Last update Thu May 18 15:35:37 2017 Gregoire Renard
*/

#include "myftp.h"

static int		set_get(t_get_line * const get)
{
  get->stop = 0;
  get->cpt = 0;
  get->back = 0;
  if ((get->buffer = malloc(1)) == NULL)
    return (ERROR);
  return (SUCCESS);
}

static int		create_file(t_get_line * const get,
				    char const *file)
{
  int			fd;

  if ((fd = open(file, O_WRONLY | O_TRUNC | O_CREAT,
		 S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
    return (ERROR);
  if ((write(fd, get->buffer, strlen(get->buffer))) == -1)
    return (ERROR);
  if ((write(fd, "\n", 1)) == -1)
    return (ERROR);
  get->stop = 1;
  free(get->buffer);
  return (SUCCESS);
}

static int		add_char(t_get_line * const get)
{
  get->cpt++;
  if ((get->buffer = realloc(get->buffer, get->cpt + 1)) == NULL)
    return (ERROR);
  get->buffer[get->cpt - 1] = get->buf[0];
  get->buffer[get->cpt] = 0;
  get->back = 0;
  return (SUCCESS);
}

static int		get_line_stor(t_client * const client,
				      t_get_line * const get,
				      char const *file)
{
  while (get->stop != 1)
    {
      if ((read(client->exchange.fd_client, get->buf, 1)) == -1)
	return (ERROR);
      if (get->buf[0] == '\r')
	get->back = 1;
      else if (get->buf[0] == '\n' && get->back == 1)
	{
	  if ((create_file(get, file)) == ERROR)
	    return (ERROR);
	}
      else
	if ((add_char(get)) == ERROR)
	  return (ERROR);
    }
  return (SUCCESS);
}

int			read_file(t_client * const client,
				  char const *file)
{
  t_get_line		get;

  if (client->mode == PASSIVE)
    {
      if ((client->exchange.fd_client =
	   accept(client->exchange.fd_server,
		  (struct sockaddr *)&client->exchange.s_in_client,
		  &client->exchange.s_in_size_client)) == -1)
	return (ERROR);
    }
  if ((set_get(&get)) == ERROR)
    return (ERROR);
  if ((get_line_stor(client, &get, file)) == ERROR)
    return (ERROR);
  return (SUCCESS);
}
