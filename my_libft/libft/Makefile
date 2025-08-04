NAME := libft.a

SRC_DIR := src
OBJ_DIR := obj
INCLUDE := inc

SRC := $(SRC_DIR)/ft_atoi.c \
	   $(SRC_DIR)/ft_bzero.c \
	   $(SRC_DIR)/ft_calloc.c \
	   $(SRC_DIR)/ft_isalnum.c \
	   $(SRC_DIR)/ft_isalpha.c \
	   $(SRC_DIR)/ft_isascii.c \
	   $(SRC_DIR)/ft_isdigit.c \
	   $(SRC_DIR)/ft_isprint.c \
	   $(SRC_DIR)/ft_itoa.c \
	   $(SRC_DIR)/ft_memchr.c \
	   $(SRC_DIR)/ft_memcmp.c \
	   $(SRC_DIR)/ft_memcpy.c \
	   $(SRC_DIR)/ft_memmove.c \
	   $(SRC_DIR)/ft_memset.c \
	   $(SRC_DIR)/ft_putchar_fd.c \
	   $(SRC_DIR)/ft_putendl_fd.c \
	   $(SRC_DIR)/ft_putnbr_fd.c \
	   $(SRC_DIR)/ft_putstr_fd.c \
	   $(SRC_DIR)/ft_split.c \
	   $(SRC_DIR)/ft_strchr.c \
	   $(SRC_DIR)/ft_strdup.c \
	   $(SRC_DIR)/ft_striteri.c \
	   $(SRC_DIR)/ft_strjoin.c \
	   $(SRC_DIR)/ft_strlcat.c \
	   $(SRC_DIR)/ft_strlcpy.c \
	   $(SRC_DIR)/ft_strlen.c \
	   $(SRC_DIR)/ft_strmapi.c \
	   $(SRC_DIR)/ft_strncmp.c \
	   $(SRC_DIR)/ft_strnstr.c \
	   $(SRC_DIR)/ft_strrchr.c \
	   $(SRC_DIR)/ft_strtrim.c \
	   $(SRC_DIR)/ft_substr.c \
	   $(SRC_DIR)/ft_tolower.c \
	   $(SRC_DIR)/ft_toupper.c \
	   $(SRC_DIR)/ft_isspace.c \
	   $(SRC_DIR)/del_char.c \
	   $(SRC_DIR)/sub_char.c \

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
