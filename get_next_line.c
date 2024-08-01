#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char *ft_strchr(char *str, char c)
{
    while(*str)
    {
        if (*str == c)
            return(str);
        str++;
    }
    return (NULL);
}

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return(i);
}

void ft_strcpy(char *dst, const char *src)
{
    while(*src)
        *dst++ = *src++;
    *dst = '\0';
}

char *ft_strdup(const char *src)
{
    char *dst;

    dst = malloc((ft_strlen((char *)src) + 1));
    if (!dst)
        return(NULL);
    ft_strcpy(dst, src);
    return (dst);
}

char *ft_strjoin(char *s1, char const *s2)
{
    char *join;

    if (!s1 || !s2)
        return(NULL);
    join = malloc((ft_strlen(s1) + ft_strlen((char *)s2) + 1));
    if (!join)
        return(NULL);
    ft_strcpy(join, s1);
    ft_strcpy((join + ft_strlen(s1)), s2 );
    free(s1);
    return(join);
}

char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char *line;
    char *newline;
    int to_copy;
    int countread;

    line = ft_strdup(buf);
    while(!(newline = ft_strchr(line, '\n')) && (countread = read(fd, buf, BUFFER_SIZE)))
    {
        buf[countread] = '\0';
        line = ft_strjoin(line, buf);
    }
    if(ft_strlen(line) == 0)
        return(free(line), NULL);
    if(newline != NULL)
    {
        to_copy = newline - line + 1;
        ft_strcpy(buf, newline + 1);
    }
    else
    {
        to_copy = ft_strlen(line);
        buf[0] = '\0';
    }
    line[to_copy] = '\0';
    return(line);
}
