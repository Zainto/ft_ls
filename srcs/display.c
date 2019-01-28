/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:48:35 by bwan-nan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/01/25 17:35:32 by bwan-nan         ###   ########.fr       */
=======
/*   Updated: 2019/01/26 13:02:18 by cempassi         ###   ########.fr       */
>>>>>>> sandbox
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			error_output(t_list *lst)
{
	ft_dprintf(2, "ls: %s: No such file or directory\n",(char *)lst->data);
}

void			long_output(t_list *files_list, t_prgm *glob)
{
	t_status	*tmp;
	size_t		nlink_max;
	size_t		size_max;
	size_t		total;

	nlink_max = 0;
	size_max = 0;
	total = 0;
	padding(files_list, &nlink_max, &size_max, &total);
	tmp = (t_status *)(files_list->data);
	if (!ft_strequ(glob->dir, ".") || glob->args)
		ft_printf("%s:\n", glob->dir);
	ft_printf("total %d\n", total);
	while (files_list)
	{
		tmp = (t_status *)(files_list->data);
		line_display(tmp, nlink_max, size_max);
		files_list = files_list->next;
	}
}

void			list_output(t_list *files_list, t_prgm *glob)
{
	if (!ft_strequ(glob->dir, "."))
		ft_printf("%s:\n", glob->dir);
	while (files_list)
	{
		ft_printf("%s\n", ((t_status *)(files_list->data))->name);
		files_list = files_list->next;
	}
}

void			basic_output(t_list *lst, t_prgm *glob)
{
	t_status	*tmp;
	t_display	info;

	info.total = 0;
	info.printed = 0;
	info.width = 15;
	basic_padding(lst, &info);
	tmp = (t_status *)lst->data;
	if (!ft_strequ(glob->dir, "."))
		ft_printf("%s:\n", glob->dir);
	basic_default(glob, lst, &info);
}

void			output_handler(t_list *files_list, t_prgm *glob)
{
	if (files_list)
	{
		if (glob->option & LS_L)
			long_output(files_list, glob);
		else if (glob->option & LS_1)
			list_output(files_list, glob);
		else
		{
			basic_output(files_list, glob);
			ft_putchar('\n');
		}
	}
<<<<<<< HEAD
	ft_putchar('\n');
}

static void		sorting_order(t_list **files_list, t_prgm *glob)
{
	if (glob->option & LS_T)
		merge_sort(files_list, &sort_time_modified);
	else if (glob->option & LS_U)
		merge_sort(files_list, &sort_last_access);
	else
		merge_sort(files_list, &sort_ascii);
}

void			output_handler(t_list *files_list, t_prgm *glob)
{
	sorting_order(&files_list, glob);
	if (glob->option & LS_L)
		long_output(files_list, glob);
	else if (glob->option & LS_1)
		list_output(files_list, glob);
	else
		basic_output(files_list, glob);
=======
>>>>>>> sandbox
}
