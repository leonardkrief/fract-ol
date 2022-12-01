SRCS		=	srcs/colors.c \
				srcs/init.c \
				srcs/main.c \
				srcs/mandelbrot.c \
				srcs/pixels.c \
				srcs/points.c \

OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)

FRACT-OL	=	fract-ol

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3
INCLUDE		=	-I /usr/X11/include
LIBS		=	-L /usr/X11/lib -l mlx
FRAMEWORKS	=	-framework OpenGL -framework AppKit
RM			=	rm -rf


${FRACT-OL}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBS} ${FRAMEWORKS} -o ${FRACT-OL}

all:	${FRACT-OL}

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

bonus:	${FRACT-OL}

clean:
		${RM} ${OBJS}
		${RM} ${DEPS}

fclean:	clean
		${RM} ${FRACT-OL}

re:		fclean all

-include ${DEPS}

.PHONY: all clean fclean re
