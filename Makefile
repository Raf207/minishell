NAME = minishell
BONUS_NAME = pipex_bonus

LIBFT = ./libft/libft.a

CC = gcc -fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror
LINK = -lreadline -L /Users/$(shell whoami)/homebrew/opt/readline/lib -I /Users/$(shell whoami)/homebrew/opt/readline/include

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/

EXECUTION = exec utils

PARSING = ast parse utils

TOOLS = exit fork

SRC_FILES = main lexer env 

OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))\
	$(addprefix src/execution/, $(addsuffix .c, $(EXECUTION)))\
	$(addprefix src/parsing/, $(addsuffix .c, $(PARSING)))\
	$(addprefix src/tools/, $(addsuffix .c, $(TOOLS)))\


HEAD = ./include/

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@echo "\033[0;33m\nCOMPILING MINISHELL...\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LINK) -o $(NAME)
	@echo "\033[1;32m./minishell created\n"

$(LIBFT)	:
	@echo "\033[0;33m\nCOMPILING LIBFT\n"
	@make -C ./libft
	@echo "\033[1;32mLIBFT created\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(LINK) -I $(HEAD) -c $< -o $@

clean :
	$(RM) ./libft/$(OBJ_DIR)
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) ./libft/libft.a
	$(RM) $(NAME)

re : fclean all