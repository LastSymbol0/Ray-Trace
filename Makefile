NAME=RT

SRC=./src/parser/*.c ./src/vec/*.c ./src/*.c ./libft/libft.a


SDL_IMAGE = -I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers -F ~/Library/Frameworks/ -framework SDL2_image

SDL_TTF=-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers -F ~/Library/Frameworks/ -framework SDL2_ttf

SDL_MIXER= -I ~/Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers -F ~/Library/Frameworks/ -framework SDL2_mixer

SDL= -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers -F ~/Library/Frameworks/ -framework SDL2 $(SDL_IMAGE) $(SDL_TTF) $(SDL_MIXER)

OpenCL= -framework OpenCL

LIB_XML= -I /usr/include/libxml2/ -lxml2 

OBJ=$(SRC:%.c=%.o)

FLAGS= -Wall -Wextra -Werror

INCL=-I ./ 
	
all: $(NAME)

$(NAME): 
	@make -C ./libft/
	@gcc -g -o $(NAME) $(SRC) $(FLAGS) $(INCL) $(LIB_XML) $(SDL) $(OpenCL)
	@echo "\x1b[32m Success build"

clean:
	@rm -f $(OBJ)
	@make fclean -C ./libft/
	@echo "\x1b[32m Success clean"

fclean: clean
	@rm -f $(NAME)

re: fclean all