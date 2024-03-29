/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm_rdm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adietric <adietric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:18:49 by adietric          #+#    #+#             */
/*   Updated: 2019/12/12 15:19:34 by adietric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int			is_in(int i, int *value)
{
	int		r;
	
	r = -1;
	while (++r < 9)
		if (value[r] == i)
			return (1);
	return (0);
}

int			just_number(char *str)
{
	int		i;
	int		c;
	int		len;

	len = ft_strlen(str);
	i = -1;
	c = 0;
	while (str[++i])
	{
		if (str[i] != '-' && str[i] != '+' && (str[i] < 48 || str[i] > 57))
			return (0);
		if (str[i] == '-' || str[i] == '+')
			c++;
		if (i > 0 && (str[i] == '-' || str[i] == '+'))
			return (0);
	}
	if (c > 1 || i < len)
		return (0);
	return (1);
}
