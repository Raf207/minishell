NAME = minishell
BONUS_NAME = pipex_bonus

LIBFT = ./libft/libft.a

CC = gcc -fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror $(CPPFLAGS)
LINK = -lreadline $(LDFLAGS)

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/

EXECUTION = exec utils
PARSING = ast parse utils
TOOLS = exit fork
LEXER = lexer expansion utils
MAIN = main
BUILTINS = env

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
SRC = $(addprefix src/lexer/, $(addsuffix .c, $(LEXER)))\
	$(addprefix src/main/, $(addsuffix .c, $(MAIN)))\
	$(addprefix src/execution/, $(addsuffix .c, $(EXECUTION)))\
	$(addprefix src/parsing/, $(addsuffix .c, $(PARSING)))\
	$(addprefix src/tools/, $(addsuffix .c, $(TOOLS)))\
	$(addprefix src/builtins/, $(addsuffix .c, $(BUILTINS)))

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
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

clean :
	$(RM) ./libft/$(OBJ_DIR)
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) ./libft/libft.a
	$(RM) $(NAME)

re : fclean all