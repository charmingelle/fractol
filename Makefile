NAME	=	fractol

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

SOURCE	=	source/color.c source/complex.c source/error.c source/event_handlers.c source/main.c

HEADERS	=	source/header.h

LIBS	=	libft/libft.a minilibx_macos/libmlx.a

OBJ		=	$(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	make -C libft;
	make -C minilibx_macos;
	${CC} -o $(NAME) $(OBJ) ${LIBS} -framework OpenGL -framework AppKit
	
clean:
	make -C libft clean;
	make -C minilibx_macos clean;
	rm -f $(OBJ);

fclean: clean
	make -C libft fclean;
	rm -f $(NAME);

re: fclean all
