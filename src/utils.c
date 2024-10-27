/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/14 23:48:01 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/27 15:44:53 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str_caster;
	size_t			i;

	str_caster = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		str_caster[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] != '\0')
		i++;
	return (i);
}
