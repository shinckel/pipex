#include "../header/ft_pipex.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int main(int argc, char **argv, char **env)
{
	char *list = find_path(env);
	printf("%s\n\n", list);
	char *env_variable = getenv("PATH");
	printf("%s\n\n", env_variable);
}

