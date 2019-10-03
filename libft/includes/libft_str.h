/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_str.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 11:04:28 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/05/29 17:13:13 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STR_H
# define LIBFT_STR_H

# include "libft.h"

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t len);
size_t	ft_strlcat(char *s1, const char *s2, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(const char *s, char (*f)(char));
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strequ(const char *s1, const char *s2);
int		ft_strnequ(const char *s1, const char *s2, size_t n);
char	*ft_strsub(const char *s1, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1);
char	**ft_strsplit(const char *s, char c);
void	ft_strrepl(char *str, char find, char repl);
size_t	ft_strfind(const char *str, char c);
char	*ft_strtoupper(char *str);
char	*ft_strtolower(char *str);
int		ft_strstartswith(const char *str, const char *find);
char	*ft_strshift(char *str, int shift);
char	*ft_strformat(const char *format, ...);
void	ft_strsort(char **tab, size_t len, int (*cmp)());
int		ft_strisnumber(const char *str);
size_t	ft_splitlen(char **split);
char	*ft_strtrijoin(char *a, char *b, char *c);
char	*ft_strsrepl(char *str, char *match, char *replacement);
char	*ft_strsreplall(char *str, char *match, char *replacement);
void	ft_freesplit(char **split);
size_t	ft_strcountchar(char *str, char c);
char	*ft_strndup(char *str, size_t n);
char	*ft_strtok(char *s, const char *delim);
char	*ft_strtok_r(char *s, const char *delim, char **save_ptr);
size_t	ft_strspn(const char *s, const char *charset);
size_t	ft_strcspn(const char *s, const char *charset);
t_u64	ft_strhash(char *keystring);
int		ft_strisascii(const char *str);
int		ft_strisalnum(const char *str);
void	ft_strndel(size_t n, ...);

#endif
