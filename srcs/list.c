/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 10:03:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/25 15:37:01 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		name_filter(void *data, void *filter)
{
	t_status	*current;
	t_prgm		*glob;	
	int			i;

	i = 0;
	current = (t_status *)data;
	glob = (t_prgm *)filter;
	while (glob->args[i])
	{
		if(ft_strequ(current->name, glob->args[i]))
			return (1);
		i++;
	}
	return (0);
}

int		create_list(DIR *current, char *path, t_list **files_list, t_prgm *glob)
{
	t_status	file;
	t_dirent	*get_file;

	if (!(get_file = readdir(current)))
		return (1);
	if (!(glob->option & LS_A) && get_file->d_name[0] == '.')
		return (create_list(current, path, files_list, glob));
	file.path = NULL;
	file.dirlist = NULL;
	file.name = ft_strdup(get_file->d_name);
	file.inode = get_file->d_ino;
	ft_asprintf(&file.path, "%s/%s", path, file.name);
	stat(file.path, &file.info);
	ft_lstaddback(files_list, ft_lstnew(&file, sizeof(t_status)));
	return (create_list(current, path, files_list, glob));
}

void	del_node(void **data)
{
	t_status *tmp;

	tmp = (t_status *)(*data);
	ft_strdel(&tmp->path);
	ft_strdel(&tmp->name);
}
