/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 10:39:23 by erintala          #+#    #+#             */
/*   Updated: 2017/10/15 10:39:29 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	print_map(t_filler *filler)
{
	int fd1;
	int i;

	fd1 = open("testing.txt", O_CREAT | O_RDWR);
	i = 0;
	while (i < filler->height)
	{
		dprintf(fd1, "%s\n", filler->map[i]);
		i++;
	}
	dprintf(fd1, "\n");
	close(fd1);
}
