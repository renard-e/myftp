/*
** func2.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu May 11 13:32:36 2017 Gregoire Renard
** Last update Thu May 18 13:40:10 2017 Gregoire Renard
*/

#include "myftp.h"

int			pwd_func(t_order * const order,
				 t_client * const client,
				 t_info * const info)
{
  char			*str;

  (void)order;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else
    {
      if ((info->path = get_current_dir_name()) != NULL)
	{
	  if ((str = malloc(strlen(info->path) + 18)) == NULL)
	    return (ERROR);
	  strcpy(str, "257 \"");
	  strcat(str, info->path);
	  strcat(str, "\" created.");
	  my_send(client->fd_client, str);
	  free(str);
	}
      else
	my_send(client->fd_client, ACTION_NO);
    }
  return (SUCCESS);
}

int			pasv_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  char			*data_info;

  (void)order;
  (void)info;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else
    {
      if ((init_server_exchange(client, -1)) == ERROR)
	my_send(client->fd_client, ERROR_CHDIR);
      client->mode = PASSIVE;
      if ((data_info = compose_order(client)) == NULL)
	return (ERROR);
      my_send(client->fd_client, data_info);
      free(data_info);
    }
  return (SUCCESS);
}

int			port_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)info;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else if (order->map[1] == NULL)
    my_send(client->fd_client, ILLEGAL_PORT);
  else
    {
      if ((check_port(order->map[1])) == ERROR)
	my_send(client->fd_client, ILLEGAL_PORT);
      else
	if ((create_port(client, order)) == ERROR)
	  my_send(client->fd_client, ILLEGAL_PORT);
	else
	  {
	    client->mode = ACTIVE;
	    my_send(client->fd_client, COMMAND_OK);
	  }
    }
  return (SUCCESS);
}

int			help_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)info;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else
    {
      if (order->map[1] != NULL)
	choose_help(order, client);
      else
	my_send(client->fd_client, ALL_HELP);
    }
  return (SUCCESS);
}

int			noop_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)info;
  (void)order;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else
    my_send(client->fd_client, COMMAND_OK);
  return (SUCCESS);
}
