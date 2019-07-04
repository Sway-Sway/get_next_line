#include "get_next_line.h"

int		main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac == 1)
		fd = 0;
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	if (ac == 2)
		close(fd);
}
