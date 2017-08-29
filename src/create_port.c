/*
** create_port.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Wed May 17 17:06:13 2017 Gregoire Renard
** Last update Thu May 18 15:06:55 2017 Gregoire Renard
*/

#include "myftp.h"

static int	change_order(t_order * const order)
{
  int		cpt;
  char		**map;

  cpt = 0;
  while (order->map[1][cpt] != '\0')
    {
      if (order->map[1][cpt] == ',')
	order->map[1][cpt] = ' ';
      else if (order->map[1][cpt] < '0'
	       || order->map[1][cpt] > '9')
	return (ERROR);
      cpt++;
    }
  if ((map = my_str_to_wordtab(order->map[1])) == NULL)
    return (ERROR);
  if ((strlen_map(map)) != 6)
    return (ERROR);
  free_map(map);
  return (SUCCESS);
}

static int	push_in_ip(t_port * const port,
			   char **map,
			   int *cpt,
			   t_client * const client)
{
  port->idx_map = 0;
  if ((client->exchange.ip =
       realloc(client->exchange.ip, strlen(client->exchange.ip)
	       + strlen(map[*cpt]) + 2)) == NULL)
    return (ERROR);
  while (map[*cpt][port->idx_map] != '\0')
    {
      client->exchange.ip[port->idx] = map[*cpt][port->idx_map];
      port->idx_map++;
      port->idx++;
    }
  client->exchange.ip[port->idx] = '.';
  client->exchange.ip[port->idx + 1] = '\0';
  port->idx++;
  (*cpt)++;
  return (SUCCESS);
}

static int	set_ip(t_port * const port,
		       char **map, int *cpt,
		       t_client * const client)
{
  if ((client->exchange.ip = malloc(1)) == NULL)
    return (ERROR);
  client->exchange.ip[0] = 0;
  port->idx = 0;
  while (*cpt != 4 && map[*cpt] != NULL)
    if ((push_in_ip(port, map, cpt, client)) == ERROR)
      return (ERROR);
  client->exchange.ip[port->idx - 1] = 0;
  return (SUCCESS);
}

static int	set_port(t_order * const order,
			 t_client * const client)
{
  t_port	port;
  char		**map;
  int		cpt;

  cpt = 0;
  if ((map = my_str_to_wordtab(order->map[1])) == NULL)
    return (ERROR);
  if ((set_ip(&port, map, &cpt, client)) == ERROR)
    return (ERROR);
  client->exchange.port = atoi(map[cpt]) * 256 + atoi(map[cpt + 1]);
  return (SUCCESS);
}

int		create_port(t_client * const client,
			    t_order * const order)
{
  if ((change_order(order)) == ERROR)
    return (ERROR);
  if ((set_port(order, client)) == ERROR)
    return (ERROR);
  if ((connect_to_client(client)) == ERROR)
    {
      free(client->exchange.ip);
      return (ERROR);
    }
  free(client->exchange.ip);
  return (SUCCESS);
}
