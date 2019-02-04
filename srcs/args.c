/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:49:01 by cempassi          #+#    #+#             */
/*   Updated: 2019/02/04 20:55:07 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			option_cancel(unsigned int *option, char c)
{
	*option &= ~(LS_1 + LS_C + LS_X + LS_L);
	if (c == 'l' || c == '1')
	{
		*option &= ~(LS_M);
		*option |= c == 'l' ? LS_L : LS_1;
	}
	else if (c == 'C')
		*option |= LS_C;
	else if (c == 'x')
		*option |= LS_X;
	else if (c == 'm')
		*option |= LS_M;
}

static unsigned int	get_option(int ac, char **av, t_opt *opt, t_prgm *glob)
{
	int				c;
	unsigned int	option;

	option = 0;
	while ((c = ft_getopt(ac, av, OPTION)) != -1)
	{
		if (c == 0)
			return (0);
		else if (c < 0 && (glob->optopt = -c))
			return ('?');
		else if (ft_strchr("lxC1m", c))
			option_cancel(&option, c);
		else
			option |= opt[c];
	}
	return (option);
}

unsigned int		options(int ac, char **av, t_prgm *glob)
{
	t_opt		opt[127];

	opt['l'] = E_L;
	opt['1'] = E_1;
	opt['R'] = E_RR;
	opt['a'] = E_A;
	opt['t'] = E_T;
	opt['G'] = E_G;
	opt['m'] = E_M;
	opt['S'] = E_S;
	opt['r'] = E_R;
	opt['T'] = E_TT;
	opt['f'] = E_F;
	opt['x'] = E_X;
	opt['C'] = E_C;
	return (get_option(ac, av, opt, glob));
}

unsigned int		get_env(char **env, t_prgm *glob)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], "LSCOLORS=", 8))
			glob->ls_colors = ft_strsub(env[i], 9, ft_strlen(&env[i][4]));
		i++;
	}
	if (!glob->ls_colors)
		glob->option &= ~(LS_G);	
	return (1);
}
