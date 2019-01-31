/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 07:04:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/01 00:11:06 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		listonedir(t_prgm *glob, DIR *current,  t_status *tmp, int flag)
{
	if (flag == 0)
		glob->dir[0] = '\0';
	else
		ft_strcpy(glob->dir, tmp->path);
	create_list(current, tmp->path, &tmp->dirlist, glob);
	sort_list(&tmp->dirlist, glob);
	if (tmp->dirlist)
	{
		output_handler(tmp->dirlist, glob);
		if (flag >= 2 && glob->args_count <= 0 && S_ISDIR(tmp->info.st_mode))
			ft_putchar('\n');
		if (glob->option & LS_RR)
			listalldir(glob, tmp->dirlist, NULL);
		ft_lstdel(&(tmp->dirlist), del_node);
	}
	closedir(current);
}

int			listalldir(t_prgm *glob, t_list *files_list, t_status *tmp)
{
	DIR			*current;
	int			flag;

	while (files_list && (tmp = (t_status *)(files_list->data)))
	{
		flag = S_ISDIR(tmp->info.st_mode);
		if (flag && !ft_strequ(tmp->name, ".") && !ft_strequ(tmp->name, ".."))
		{
			if ((current = opendir(tmp->path)))
				listonedir(glob, current, tmp, 2);
			else
				error(tmp);
		}
		files_list = files_list->next;
	}
	return (0);
}

int			list_directory(t_prgm *glob, char *path)
{
	DIR			*current;
	t_list		*files_list;
	
	current = opendir(path);
	files_list = NULL;
	ft_strcpy(glob->dir, path);
	create_list(current, path, &files_list, glob);
	sort_list(&files_list, glob);
	output_handler(files_list, glob);
	if (glob->option & LS_RR)
		listalldir(glob, files_list, NULL);
	ft_lstdel(&files_list, del_node);
	closedir(current);
	return (0);
}
