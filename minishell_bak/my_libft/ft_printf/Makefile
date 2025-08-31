NAME := ft_printf.a

SRC_DIR := src
OBJ_DIR := obj
INCLUDE := inc

SRC := $(SRC_DIR)/ft_printf_bonus.c \
	   $(SRC_DIR)/ft_print_c_bonus.c \
	   $(SRC_DIR)/ft_print_p_bonus.c \
	   $(SRC_DIR)/ft_print_u_bonus.c \
	   $(SRC_DIR)/ft_print_di_bonus.c \
	   $(SRC_DIR)/ft_print_s_bonus.c \
	   $(SRC_DIR)/ft_print_x_bonus.c \
	   $(SRC_DIR)/ft_struct_bonus.c \
	   $(SRC_DIR)/ft_utils_bonus.c \

OBJ := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -I$(INCLUDE)

AR := ar
ARFLAGS := -rcs

RM := rm -rf

$(NAME): $(OBJ)
		@$(AR) $(ARFLAGS) $(NAME) $(OBJ)

$(OBJ): $(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c -o $@ $^

all: $(NAME)

clean:
		@$(RM) $(OBJ) $(OBJ_DIR)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
