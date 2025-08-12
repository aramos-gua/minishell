
typedef struct s_token
{
	struct s_token	*prev;
	char			*proces;
	int				pid;
	int				last_pid;
	int		process_nbr;
	int				type; //e.g. command, argument, operator, file
	char			*token; //the token itself e.g. echo
	struct s_token	*next;
}				t_token;


int ft_lstsize(t_token *list)
{
  t_token *current;
  int     i;

  i = 1;
  if (!list)
    return (0);
  current = list;
  while (current->next != list)
  {
    i++;
    current = current->next;
  }
  return (i);
}

int main(void)
{
  
  t_token elem1;
  t_token elem2;

  elem1 = (t_token){
    .prev = &elem2,
    .proces = "",
    .pid = 10,
    .last_pid = 20,
    .process_nbr = 0,
    .type = 42,
    .token = ">",
    .next = &elem2
  };
  
  elem2 = (t_token){
    .prev = &elem1,
    .proces = "",
    .pid = 10,
    .last_pid = 20,
    .process_nbr = 0,
    .type = 42,
    .token = ">",
    .next = &elem1

  };

  int * ptr = (int *)0x01;

 *ptr = 42;

  t_token  *list = &elem1;

  int size = ft_lstsize(list);
    return (0);
}
