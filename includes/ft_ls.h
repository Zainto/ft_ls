/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 02:12:47 by cempassi          #+#    #+#             */
/*   Updated: 2019/01/23 18:03:23 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>

# define OPTIONS "l1RratG"

# define LS_L		1
# define LS_1		2
# define LS_R		4
# define LS_LOW_R	8
# define LS_A		16
# define LS_T		32
# define LS_G		64

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct passwd		t_passwd;
typedef struct group		t_group;

typedef struct				s_status
{
	char					*path;
	t_dirent				*dirent;
	t_list					*dirlist;
	t_stat					info;
	t_group					group;
}							t_status;

int		ft_ls(unsigned char flags);
void	print_list(t_list *files_list);
void	get_the_right_size(t_list *files_list, int *tab);
int		merge_sort(t_list **files_list, int (*cmp)(void *, void *));
int		parsing(int ac, char **av, unsigned char *flags);

#endif
