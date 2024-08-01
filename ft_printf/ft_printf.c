#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *str, int *res)
{
	if (!str)
		str = "(null)";
	while (*str)
		*res += write(1, str++, 1);
}

void	ft_putnbr(long long int nbr, int base, int *res)
{
	char *b = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr *= -1;
		*res += write(1, "-", 1);
	}
	if (nbr >= base)
		ft_putnbr((nbr / base), base, res);
	*res += write(1, &b[nbr % base], 1);
}

int ft_printf(const char *str, ...)
{
	int res = 0;
	va_list	element;

	va_start(element, str);
	while (*str)
	{
		if (*str == '%' && ((*(str + 1) == 's') || (*(str + 1) == 'd') || (*(str + 1) == 'x')))
		{
			str++;
			if (*str == 's')
				ft_putstr(va_arg(element, char *), &res);
			else if (*str == 'd')
				ft_putnbr((long long int)va_arg(element, int), 10, &res);
			else if (*str == 'x')
				ft_putnbr((long long int)va_arg(element, unsigned int), 16, &res);
		}
		else
			res += write(1, str, 1);
		str++;
	}
	va_end(element);
	return (res);
}
