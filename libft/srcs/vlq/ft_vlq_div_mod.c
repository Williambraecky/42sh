/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_div_mod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:42:58 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/28 17:07:09 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
#include <stdio.h>

 * if D = 0 then error(DivisionByZeroException) end
 * Q := 0                  -- Initialize quotient and remainder to zero
 * R := 0
 * for i := n − 1 .. 0 do  -- Where n is number of bits in N
 *   R := R << 1           -- Left-shift R by 1 bit
 *   R(0) := N(i)          -- Set the least-significant bit of R equal to bit i of the numerator
 *   if R ≥ D then
 *      R := R − D
 *      Q(i) := 1
 *   end
 * end


typedef struct s_test	t_test;
struct s_test
{
	int	Q;
	int	R;
};

int msb(unsigned int i)
{
	int j = 32;
	while (j--)
		if (i >> j)
			return (j + 1);
	return (j);
}

t_test divide(unsigned int i, unsigned int j)
{
	t_test	t;
	int		bits;

	t.Q = 0;
	t.R = 0;
	bits = msb(i);
	while (bits--)
	{
		t.R = t.R << 1;
		t.R |= (i >> bits) & 1;
		if (t.R >= j)
		{
			t.R = t.R - j;
			t.Q |= 1 << bits;
		}
	}
	return (t);
}

int main(int argc, const char *argv[])
{
	t_test test = divide(17, 5);
	printf("Q:%d\nR:%d\n", test.Q, test.R);
	return 0;
}
*/
