/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:45:12 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/07/08 07:35:30 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (n--)
	{
		*p++ = (unsigned char)value;
	}
	return (ptr);
}

/*
int main(void)
{
    char buffer[20];
    
    // Test 1: Fill with 'A' (65)
    ft_memset(buffer, 'A', 10);
    buffer[10] = '\0';  // Null terminate for printing
    printf("Test 1: %s\n", buffer);
    
    // Test 2: Fill with zeros
    ft_memset(buffer, 0, sizeof(buffer));
    printf("Test 2: Buffer cleared\n");
    
    // Test 3: Fill with 42
    ft_memset(buffer, 42, 5);
    for (int i = 0; i < 5; i++)
        printf("buffer[%d] = %d\n", i, (unsigned char)buffer[i]);
    
    // Test 4: Compare with standard memset
    char std_buffer[10];
    char ft_buffer[10];
    
    memset(std_buffer, 'X', 8);
    ft_memset(ft_buffer, 'X', 8);
    
    if (memcmp(std_buffer, ft_buffer, 8) == 0)
        printf("✓ Matches standard memset\n");
    else
        printf("✗ Differs from standard memset\n");
    
    return (0);
}
*/
