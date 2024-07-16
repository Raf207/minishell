NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

AR = ar -rcs

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC_FILES = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint \
            ft_itoa ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd ft_putendl_fd \
            ft_putnbr_fd ft_putstr_fd ft_split ft_strchr ft_strdup ft_striteri ft_strjoin ft_strlcat \
            ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr ft_strtrim ft_substr \
            ft_tolower ft_toupper ft_strlcat ft_toupper ft_tolower ft_lstnew_bonus ft_lstadd_front_bonus \
			ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus \
			ft_lstiter_bonus ft_lstmap_bonus get_next_line ft_strstr

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

HEAD = ./include/

all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

$(NAME)	: $(OBJ)
	@$(AR) $(NAME) $(OBJ)

clean :
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all