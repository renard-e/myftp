/*
** my_get_line.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed May 10 15:17:17 2017 Gregoire Renard
** Last update Fri May 19 12:20:05 2017 Gregoire Renard
*/

#include "myftp.h"

static int		prepare_treatment(t_order * const order,
					  t_client * const client,
					  t_info * const info)
{
  if ((strcasecmp(order->buffer, "QUIT")) == 0)
    {
      my_send(client->fd_client, CLOSE);
      order->client_stop = 1;
    }
  else
    if ((treatment(order, client, info)) == ERROR)
      return (ERROR);
  order->stop = 1;
  order->back = 0;
  return (SUCCESS);
}

static int		add_char(t_order * const order)
{
  char			tmp;

  tmp = order->buf[0];
  if (order->back == 1)
    {
      tmp = order->buf[0];
      order->buf[0] = '\r';
      if ((add_char(order)) == ERROR)
	return (ERROR);
      order->buf[0] = tmp;
    }
  order->cpt++;
  if ((order->buffer = realloc(order->buffer, order->cpt)) == NULL)
    return (ERROR);
  order->buffer[order->cpt - 2] = order->buf[0];
  order->buffer[order->cpt - 1] = 0;
  order->back = 0;
  return (SUCCESS);
}

int			my_get_line(t_order * const order,
				    t_client * const client,
				    t_info * const info)
{
  if ((read(client->fd_client,
	    order->buf, 1)) <= 0)
    return (ERROR);
  printf("char = *%i*\n", order->buf[0]);
  if (order->buf[0] == '\0')
    return (ERROR);
  if (order->buf[0] == '\r')
    order->back = 1;
  else if (order->buf[0] == '\n' && order->back == 1)
    {
      if ((prepare_treatment(order, client, info)) == ERROR)
	return (ERROR);
    }
  else
    if ((add_char(order)) == ERROR)
      return (ERROR);
  return (SUCCESS);
}
