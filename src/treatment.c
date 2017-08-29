/*
** treatment.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed May 10 21:56:52 2017 Gregoire Renard
** Last update Thu May 18 08:58:25 2017 Gregoire Renard
*/

#include "myftp.h"

int		treatment(t_order * const order,
			  t_client * const client,
			  t_info * const info)
{
  int		cpt;

  cpt = 0;
  if ((order->map = my_str_to_wordtab(order->buffer)) == NULL)
    return (ERROR);
  if (order->map[0] != NULL)
    {
      while (cpt != MAX_CMD)
	{
	  if ((strcasecmp(order->map[0], info->tab[cpt].cmd)) == 0)
	    {
	      if ((info->tab[cpt].func(order, client, info)) == ERROR)
		return (ERROR);
	      return (SUCCESS);
	    }
	  cpt++;
	}
    }
  if (client->login == 1)
    my_send(client->fd_client, ERROR_MSG);
  else
    my_send(client->fd_client, ERROR_UNLOG);
  free_map(order->map);
  return (SUCCESS);
}
