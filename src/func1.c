/*
** func1.c for  in /home/renard_e/2/systeme_unix_reseaux/PSU_2016_myftp/src
** 
** Made by Gregoire Renard
** Login   <renard_e@epitech.net>
** 
** Started on  Thu May 11 13:27:00 2017 Gregoire Renard
** Last update Thu May 18 13:52:18 2017 Gregoire Renard
*/

#include "myftp.h"

int			user_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)info;
  if (order->map[1] == NULL)
    my_send(client->fd_client, ERROR_PERM);
  else
    {
      if ((client->name = strdup(order->map[1])) == NULL)
	return (ERROR);
      my_send(client->fd_client, NEED_PASSWD);
      client->real_login = 1;
    }
  return (SUCCESS);
}

int			pass_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)info;
  (void)order;
  if (client->real_login == 0)
    my_send(client->fd_client, NEED_ACCOUNT);
  else if ((strcmp(client->name, "Anonymous")) == 0)
    {
      my_send(client->fd_client, LOGIN);
      client->login = 1;
    }
  else
    {
      client->real_login = 0;
      free(client->name);
      my_send(client->fd_client, LOGIN_INCO);
    }
  return (SUCCESS);
}

int			cwd_func(t_order * const order,
				 t_client * const client,
				 t_info * const info)
{
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else if (order->map[1] == NULL)
    my_send(client->fd_client, ERROR_CWD);
  else
    {
      if ((chdir(order->map[1])) == -1)
	my_send(client->fd_client, ERROR_CWD);
      else
	{
	  info->path = get_current_dir_name();
	  my_send(client->fd_client, RQT_FILE);
	}
    }
  return (SUCCESS);
}

int			cdup_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)order;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else
    {
      if ((chdir("..")) == -1)
	{
	  my_send(client->fd_client, ERROR_CHDIR);
	  return (ERROR);
	}
      else
	{
	  if ((info->path = get_current_dir_name()) == NULL)
	    return (ERROR);
	  my_send(client->fd_client, COMMAND_OK);
	}
    }
  return (SUCCESS);
}

int			dele_func(t_order * const order,
				  t_client * const client,
				  t_info * const info)
{
  (void)info;
  if (client->login == 0)
    my_send(client->fd_client, ERROR_UNLOG);
  else if (order->map[1] == NULL)
    my_send(client->fd_client, ERROR_DELE);
  else
    {
      if ((remove(order->map[1])) == -1)
	my_send(client->fd_client, ERROR_DELE);
      else
	my_send(client->fd_client, RQT_FILE);
    }
  return (SUCCESS);
}
