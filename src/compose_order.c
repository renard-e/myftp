/*
** compose_order.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Mon May 15 20:31:55 2017 Gregoire Renard
** Last update Tue May 16 19:30:22 2017 Gregoire Renard
*/

#include "myftp.h"

static int		remp_data_info(t_client * const client,
				       char **data_info)
{
  char			*tmp;

  if ((tmp = malloc(7)) == NULL)
    return (ERROR);
  sprintf(tmp, "%i", client->exchange.port / 256);
  strcat(*data_info, tmp);
  strcat(*data_info, ",");
  sprintf(tmp, "%i", client->exchange.port % 256);
  strcat(*data_info, tmp);
  return (SUCCESS);
}

char			*compose_order(t_client * const client)
{
  char			*data_info;
  int			cpt;

  cpt = 0;
  if ((data_info = malloc(61)) == NULL)
    return (NULL);
  strcpy(data_info, "227 Entering Passive Mode (");
  strcat(data_info, client->ip_serv);
  while (data_info[cpt] != '\0')
    {
      if (data_info[cpt] == '.')
	data_info[cpt] = ',';
      cpt++;
    }
  strcat(data_info, ",");
  if ((remp_data_info(client, &data_info)) == ERROR)
    return (NULL);
  strcat(data_info, ").");
  return (data_info);
}
