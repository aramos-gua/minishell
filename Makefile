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
		$(SRC_DIR)/utils/parsing_utils.c \
		$(SRC_DIR)/utils/free_utils.c \
		$(SRC_DIR)/execution/execution.c \
		$(SRC_DIR)/execution/commands.c \
		$(SRC_DIR)/execution/get_binaries.c \
		$(SRC_DIR)/execution/execution_utils.c \
		$(SRC_DIR)/execution/builtin.c \
		$(SRC_DIR)/execution/cleaner.c


OBJ := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))
INCLUDE := inc

LIBFT := my_libft/libft/libft.a
FT_PRINTF := my_libft/ft_printf/ft_printf.a
GNL := my_libft/gnl/gnl.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -gdwarf-3 -I$(INCLUDE)

RM := rm -rf

#Name has to be the first one to be checked and executed
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF) $(GNL)
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

$(GNL):
		@make -C my_libft/gnl

#all must always be the first rule!
all: $(NAME)

clean:
		@make clean -C my_libft/libft
		@make clean -C my_libft/ft_printf
		@make clean -C my_libft/gnl
		@$(RM) $(OBJ) $(OBJ_DIR)

fclean: clean
		@make fclean -C my_libft/libft
		@make fclean -C my_libft/ft_printf
		@make fclean -C my_libft/gnl
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 
