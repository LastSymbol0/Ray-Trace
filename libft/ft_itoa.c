/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aillia <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:11:34 by aillia            #+#    #+#             */
/*   Updated: 2018/11/04 14:12:09 by aillia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	make_ten(int count)
{
	int res;

	res = 1;
	while (--count > 0)
		res *= 10;
	return (res);
}

static int	help_itoa(char *res, int n, int i)
{
	int	zero;

	while (n > 0)
	{
		res[i] = (n / make_ten(num_len(n))) + '0';
		zero = num_len(n) - num_len(n % make_ten(num_len(n)));
		while (zero-- >= 2)
			res[++i] = '0';
		if (num_len(n % make_ten(num_len(n))) == 1 && n % 10 == 0)
			res[++i] = '0';
		n = n % make_ten(num_len(n));
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	char	*res;

	if (n == -2147483648)
	{
		res = ft_strdup("-2147483648");
		return (res);
	}
	res = ft_strnew(num_len(n));
	if (!res)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		res[i++] = '-';
		n *= -1;
	}
	if (n == 0)
		res[i++] = '0';
	i = help_itoa(res, n, i);
	res[i] = '\0';
	return (res);
}
