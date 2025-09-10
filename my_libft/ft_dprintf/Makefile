# Text styles
DEL_LINE =		\033[2K
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m

# Basic bright colors
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m

# Other colors
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m

SRC = \
	dprintf_atoi.c\
	dprintf_memset.c\
	dprintf_putchar.c\
	dprintf_putstr.c\
	dprintf_strjoin.c\
	dprintf_strlcat.c\
	dprintf_strlcpy.c\
	dprintf_strlen.c\
	dprintf_toupper.c\
	ft_hxtoa.c\
	ft_printf_itoa.c\
	ft_printf_utoa.c\
	ft_dprintf/ft_dprintf.c\
	ft_dprintf/parsing.c\
	ft_dprintf/apply_specifiers.c\
	ft_dprintf/ft_printf_c_s_u.c\
	ft_dprintf/ft_printf_d_i.c\
	ft_dprintf/ft_printf_x_p.c\

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
OBJ_DIR = build
CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC
NAME = libdprintf.a

# Compile libft
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "\n${GREEN} Created $(NAME) ${DEF_COLOR}\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "${MAGENTA} ~ ${BROWN} Compiling... ${MAGENTA}-> ${CYAN}$<${DEF_COLOR}"
	@$(CC) $(CFLAGS) -c $< -o $@

# Targets
all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN} Cleaned $(OBJ_DIR) directory ${DEF_COLOR}"

fclean: clean
	@rm -f $(NAME)
	@echo "${GREEN} Cleaned $(NAME) library ${DEF_COLOR}"

re: fclean all
