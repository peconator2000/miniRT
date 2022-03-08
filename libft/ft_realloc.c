#include "libft.h"

void	*ft_realloc(void *old, int old_size, int size)
{
	void	*new;
	int		i;

	new = malloc(size);
	ft_bzero(new, size);
	if (!new)
		return (NULL);
	i = 0;
	while (old && i < old_size && i < size)
	{
		((char *)new)[i] = ((char *)old)[i];
		i++;
	}
	if (old)
		free(old);
	return (new);
}
