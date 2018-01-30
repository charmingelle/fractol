NAME	=	fractol

CC		=	gcc

CFLAGS	=	

SRCDIR	=	source

INCDIR	=	includes

SRC		=	apoll.c cantor.c color.c draw.c error.c event_handlers.c fract_data.c main.c mand_jul_ship_tri.c mutate.c serp.c tree.c utils.c

HEADERS	=	$(addprefix $(INCDIR)/, header.h)

LIBS	=	libft/libft.a minilibx_macos/libmlx.a

OBJDIR	=	obj

OBJ		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C minilibx_macos
	$(CC) -O3 -o $(NAME) $(OBJ) ${LIBS} -framework OpenGL -framework AppKit -framework opencl -I $(INCDIR)

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	make -C libft clean;
	make -C minilibx_macos clean;
	rm -rf $(OBJDIR);

fclean: clean
	make -C libft fclean;
	rm -f $(NAME);

re: fclean all
