NAME := minishell

SRC_DIR := src
OBJ_DIR := obj

SRC :=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/envp.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/input_check.c \
		$(SRC_DIR)/parsing/process_info.c \
		$(SRC_DIR)/parsing/tokeniser.c \
		$(SRC_DIR)/parsing/lexing.c \
		$(SRC_DIR)/parsing/expansion.c\
		$(SRC_DIR)/parsing/redirects.c \
		$(SRC_DIR)/parsing/heredoc.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/utils/t_token_utils.c \
		$(SRC_DIR)/utils/signals.c \
		$(SRC_DIR)/utils/free_utils.c \
		$(SRC_DIR)/execution/execution.c \
		$(SRC_DIR)/execution/redirects.c \
		$(SRC_DIR)/execution/execution_utils.c \
		$(SRC_DIR)/execution/commands.c \
		$(SRC_DIR)/execution/get_binaries.c \
		$(SRC_DIR)/execution/builtin.c \
		$(SRC_DIR)/execution/builtin_helpers.c \
		$(SRC_DIR)/execution/cd_builtin.c \
		$(SRC_DIR)/execution/pwd_builtin.c \
		$(SRC_DIR)/execution/export.c \
		$(SRC_DIR)/execution/errors.c \
		$(SRC_DIR)/execution/cleaner.c


OBJ := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))
INCLUDE := inc

LIBFT := my_libft/libft/libft.a
FT_PRINTF := my_libft/ft_printf/ft_printf.a
FT_DPRINTF := my_libft/ft_dprintf/libdprintf.a
GNL := my_libft/gnl/gnl.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -gdwarf-3 -I$(INCLUDE) #-fsanitize=address,undefined

RM := rm -rf

#Name has to be the first one to be checked and executed
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(FT_DPRINTF) $(GNL)
		@$(CC) $(CFLAGS) $^ -lreadline -o $(NAME)
		
$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(OBJ_DIR)/execution
		@mkdir -p $(OBJ_DIR)/parsing
		@mkdir -p $(OBJ_DIR)/utils
		@$(CC) $(CFLAGS) -c -o $@ $^

$(LIBFT):
		@make -C my_libft/libft
		
$(FT_PRINTF): 
		@make -C my_libft/ft_printf

$(FT_DPRINTF): 
		@make -C my_libft/ft_dprintf

$(GNL):
		@make -C my_libft/gnl

#all must always be the first rule!
all: $(NAME)

v: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp -s ./minishell

clean:
		@make clean -C my_libft/libft
		@make clean -C my_libft/ft_printf
		@make clean -C my_libft/ft_dprintf
		@make clean -C my_libft/gnl
		@$(RM) $(OBJ) $(OBJ_DIR)

fclean: clean
		@make fclean -C my_libft/libft
		@make fclean -C my_libft/ft_printf
		@make fclean -C my_libft/ft_dprintf
		@make fclean -C my_libft/gnl
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 
