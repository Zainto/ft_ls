/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 07:04:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/01 20:52:04 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	listonedir(t_prgm *glob, DIR *current, t_status *tmp)
{
	create_list(current, tmp->path, &tmp->dirlist, glob);
	sort_list(&tmp->dirlist, glob);
	if (tmp->dirlist)
	{
		if (glob->args_count == 2)
			ft_putchar('\n');
		output_handler(tmp->dirlist, glob);
		if (glob->option & LS_RR)
			listalldir(glob, tmp->dirlist, NULL);
		ft_lstdel(&(tmp->dirlist), del_node);
	}
	closedir(current);
}

int			listalldir(t_prgm *glob, t_list *lst, t_status *tmp)
{
	DIR			*current;
	int			flag;

	while (lst && (tmp = (t_status *)(lst->data)))
	{
		flag = S_ISDIR(tmp->info.st_mode);
		if (flag && !ft_strequ(tmp->name, ".") && !ft_strequ(tmp->name, ".."))
		{
			ft_strcpy(glob->dir, tmp->path);
			if ((current = opendir(tmp->path)))
				listonedir(glob, current, tmp);
			else
			{
				ft_putchar('\n');
				error(glob, tmp);
			}
		}
		lst = lst->next;
	}
	return (0);
}

static void	list_directory_args(t_prgm *glob, t_list *dir_lst)
{
	DIR			*current;
	t_status	*tmp;
	t_list		*dir;

	dir = dir_lst;
	while (dir_lst)
	{
		tmp = (t_status *)(dir_lst->data);
		ft_strcpy(glob->dir, tmp->path);
		if ((current = opendir(tmp->path)))
			listonedir(glob, current, tmp);
		else
			error(glob, tmp);
		dir_lst = dir_lst->next;
	}
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

int			list_files(t_prgm *glob)
{
	t_list		*file;
	t_list		*dir;
	int			flag;

	file = NULL;
	dir = NULL;
	flag = -1;
	generate_lists(glob, &file, &dir);
	sort_list(&dir, glob);
	sort_list(&file, glob);
	output_handler(file, glob);
	if (glob->args->next && file && dir)
		glob->args_count = 2;
	else if (glob->args->next)
		glob->args_count = 1;
	list_directory_args(glob, dir);
	ft_lstdel(&file, del_node);
	ft_lstdel(&dir, del_node);
	return (0);
}
