/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oucan <oucan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:18:45 by oucan             #+#    #+#             */
/*   Updated: 2024/11/16 16:32:25 by oucan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

void	ft_putstr(const char *s, unsigned int *counter);
void	ft_putnbr(int n, unsigned int *counter);
void	ft_putunbr(unsigned int n, unsigned int *counter);
void	ft_puthex(unsigned int hex, char uppercase, unsigned int *counter);
void	ft_puthexp(unsigned long hex, unsigned int *counter);
int		ft_printf(const char *str, ...);

#endif