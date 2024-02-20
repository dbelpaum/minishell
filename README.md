# minishell
My own Shell

![](https://github.com/dbelpaum/minishell/blob/main/minishell_demo.png)

# Build
run `make` at the root of the repo.

`./minishell`

### Has its own builtins :

◦ echo with option -n

◦ cd with only a relative or absolute path

◦ pwd with no options

◦ export with no options

◦ unset with no options

◦ env with no options or arguments

◦ exit with no options

Will use your PATH environment variable to look for any other command, with execve.
