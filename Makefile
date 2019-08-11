NAME=RT

SRC=./src/parser/*.c ./src/*.c ./libft/libft.a

OBJ=$(SRC:%.c=%.o)

FLAGS= -Wall -Wextra -Werror

INCL=-I ./ -I /usr/include/libxml2/
	
all: $(NAME)

$(NAME): 
	@make -C ./libft/
	@gcc -g -o $(NAME) $(SRC) $(FLAGS) $(INCL) -lxml2
	@echo "\x1b[32m Success build"

clean:
	@rm -f $(OBJ)
	@make fclean -C ./libft/
	@echo "\x1b[32m Success clean"

fclean: clean
	@rm -f $(NAME)

re: fclean all