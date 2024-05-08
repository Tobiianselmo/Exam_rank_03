#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int	ft_putstr(char *str)
{
	int ret = 0;
	int i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
		ret += write(1, &str[i++], 1);
	return (ret);
}

int	ft_putnbr(int num)
{
	char *base = "0123456789";
	int	ret = 0;
	long res;
	res = (long)num;
	if (res < 0)
	{
		ret += write(1, "-", 1);
		res *= -1;
	}
	if (res <= 10)
		ret += write(1, &base[res], 1);
	else if (res > 10)
	{
		ret += ft_putnbr(res / 10);
		ret += ft_putnbr(res % 10);
	}
	return (ret);
}

int	ft_hexa(unsigned int num)
{
	char *base = "0123456789abcdef";
	int	ret = 0;
	if (num <= 16)
		ret += write(1, &base[num], 1);
	else if (num > 16)
	{
		ret += ft_hexa(num / 16);
		ret += ft_hexa(num % 16);
	}
	return (ret);
}

int	conversion(va_list list, char c)
{
	int	ret = 0;
	if (c == 's')
		ret += ft_putstr(va_arg(list, char *));
	else if (c == 'd')
		ret += ft_putnbr(va_arg(list, int));
	else if (c == 'x')
		ret += ft_hexa(va_arg(list, int));
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	int	ret = 0;
	int	i = 0;
	va_list	list;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ret += conversion(list, str[++i]);
		}
		else
			ret += write(1, &str[i], 1);
		i++;
	}
	va_end(list);
	return (ret);
}
