/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msnow-be <msnow-be@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:45:24 by msnow-be          #+#    #+#             */
/*   Updated: 2018/12/20 14:52:42 by msnow-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_format
{
	char		data_type;
	char		num_length[2];
	int			num_base;
	char		hex_lettercase;
	int			width;
	int			precision;
	_Bool		left_align;
	char		filler;
	char		plus_indication;
	_Bool		needs_prefix;
	_Bool		scientific_notation;
}				t_format;

typedef struct	s_date
{
	int			year;
	char		*month;
	int			day;
	_Bool		is_valid;
}				t_date;

int				ft_printf(const char *str, ...);

void			get_data_type_base_lettercase(char c, t_format *format);
int				get_double_width(double n, t_format format);
void			update_num_length(const char *str, int *pos, char *length);
void			get_width_and_precision(const char *str, int *pos,
					t_format *result, va_list params);
int				get_print_width(t_format format);
int				get_signed_digits_width(long long int n, int precision);
int				get_signed_extras_width(long long int n, t_format format);
int				get_unsigned_digits_width(unsigned long long int n,
					t_format format);
int				get_unsigned_extras_width(unsigned long long int n,
					t_format format);
int				ft_atoi(const char *str);
void			ft_putstr_till_pos(char const *s, int pos);
int				put_signed_nbr(long long n, t_format format);
void			put_signed_nbr_pure(long long n);
int				put_unsigned_nbr(unsigned long long n, t_format format);
void			put_unsigned_nbr_pure(unsigned long long n, int base,
					char lettercase);
int				put_double(double n, t_format format);
int				put_long_double(long double n, t_format format);
void			ft_putchar(char c);
void			ft_putwchar(wchar_t c);
char			*ft_strchr(const char *str, int c);
char			*ft_strstr(const char *big, const char *little);
size_t			ft_strlen(const char *str);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t len);
int				print_date(char *date_str, t_format format);
int				print_pointer(void *ptr, t_format format);
int				print_chars(int c, t_format format);
int				print_string(char *str, t_format format);
int				process_float_number(va_list params, t_format format);
int				process_signed_int(va_list params, t_format format);
int				process_unsigned_int(va_list params, t_format format);
void			handle_sign_and_left_fill(long long n, t_format format,
					int diff);
void			put_fill(char filler, int diff);
void			put_sign(long long n, t_format format);
void			set_extra_parameters(t_format *format, char c, va_list params);
void			switch_formatting(const char *str, int *pos,
					int *symbols_printed);

#endif
