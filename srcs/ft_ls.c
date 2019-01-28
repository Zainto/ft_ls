/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 23:07:43 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/25 17:46:01 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		backtrack(t_list *files_list, t_prgm *glob)
{
	t_status	*tmp;
	DIR			*current;

	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		if (S_ISDIR(tmp->info.st_mode) && !ft_strequ(tmp->name, ".")
				&& !ft_strequ(tmp->name, ".."))
		{
			current = opendir(tmp->path);
			ft_strcpy(glob->dir, tmp->path);
			create_list(current, tmp->path, &tmp->dirlist, glob);
			if (tmp->dirlist)
			{
				ft_putchar('\n');
				output_handler(tmp->dirlist, glob);
				backtrack(tmp->dirlist, glob);
				ft_lstdel(&(tmp->dirlist), del_node);
			}
			closedir(current);
		}
		files_list = files_list->next;
	}
	return (0);
}

int		list_directory(t_prgm *glob, char *path)
{
	DIR			*current;
	t_list		*files_list;

	current = opendir(path);
	files_list = NULL;
	ft_strcpy(glob->dir, path);
	create_list(current, path, &files_list, glob);
	output_handler(files_list, glob);
	if(glob->option & LS_RR)
		backtrack(files_list, glob);
	ft_lstdel(&files_list, del_node);
	closedir(current);
	return (0);
}

int		list_files(t_prgm *glob, char *path)
{
	DIR			*current;
	t_list		*files_list;
	t_list		*sub_file_list;
	t_list		*sub_dir_list;

	current = opendir(path);
	files_list = NULL;
	ft_strcpy(glob->dir, path);
	create_list(current, path, &files_list, glob);
	sub_file_list = ft_lstfilter(files_list, glob, file_filter);
	sub_dir_list = ft_lstfilter(files_list, glob, dir_filter);
	output_handler(sub_file_list, glob);
	output_handler(sub_dir_list, glob);
	ft_lstdel(&sub_dir_list, NULL);
	ft_lstdel(&sub_file_list, NULL);
	ft_lstdel(&files_list, del_node);
	closedir(current);
	return (0);
}

