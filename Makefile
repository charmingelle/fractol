# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/01 19:56:59 by grevenko          #+#    #+#              #
#    Updated: 2018/02/01 19:57:00 by grevenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

INCFLAGS	=	$(addprefix -I, includes libft minilibx_macos)

SRCDIR		=	source

INCDIR		=	includes

SRC			=	apoll.c apoll2.c cantor.c color.c draw.c draw2.c error.c event_handlers.c event_handlers2.c event_handlers3.c fill_fract_image.c fract_data.c fract_data2.c main.c serp.c tree.c utils.c utils2.c

HEADERS		=	$(addprefix $(INCDIR)/, header.h)

LIBS		=	libft/libft.a minilibx_macos/libmlx.a

OBJDIR		=	obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C minilibx_macos
	$(CC) -O3 -o $(NAME) $(OBJ) ${LIBS} -framework OpenGL -framework AppKit -framework opencl $(INCFLAGS)

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCFLAGS)

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
