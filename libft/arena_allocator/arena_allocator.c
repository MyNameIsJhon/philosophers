/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:34:20 by jriga             #+#    #+#             */
/*   Updated: 2025/07/24 02:34:58 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include <stdlib.h>

void	arena_init(t_arena *a, size_t size)
{
	a->data = malloc(size);
	if (!a->data)
		return ;
	a->size = size;
	a->offset = 0;
}

static size_t	align_up(size_t offset, size_t alignment)
{
	return ((offset + alignment - 1) & ~(alignment - 1));
}

void	*arena_alloc(t_arena *a, size_t size, size_t alignment)
{
	size_t	aligned;
	void	*new;

	aligned = align_up(a->offset, alignment);
	if (aligned + size > a->size)
		return (NULL);
	new = a->data + aligned;
	a->offset = aligned + size;
	return (new);
}

void	arena_free(t_arena *a)
{
	free(a->data);
	a->size = 0;
	a->size = 0;
}
