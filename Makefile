NAME	=	fractol

CC		=	gcc

CFLAGS	=	

SOURCE	=	source/apoll.c source/bulb.c source/cantor.c source/color.c source/draw.c source/error.c source/event_handlers.c source/main.c source/mutate.c source/serp.c source/tree.c source/utils.c

HEADERS	=	source/header.h

LIBS	=	libft/libft.a minilibx_macos/libmlx.a

OBJ		=	$(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	make -C libft;
	make -C minilibx_macos;
	$(CC) -O3 -o $(NAME) $(OBJ) ${LIBS} -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) -O3 -c $< -o $@

clean:
	make -C libft clean;
	make -C minilibx_macos clean;
	rm -f $(OBJ);

fclean: clean
	make -C libft fclean;
	rm -f $(NAME);

re: fclean all
