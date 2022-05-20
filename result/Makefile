NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MFLAGS = -L ./mlx -lmlx -framework OpenGL -framework AppKit -fsanitize=address

SRCS =	$(addprefix src/, Cub3D.c \
					calculate_wall.c \
					flood_fill.c \
					get_direction.c \
					get_next_line_utils.c \
					get_next_line.c \
					hook_func.c \
					init.c \
					init2.c \
					load_texture.c \
					loop_hook.c \
					map_parse.c \
					map_parse2.c \
					map_parse3.c \
					movement.c \
					movement2.c \
					save_map.c \
					utils.c	\
					utils2.c \
					wall_cast.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	make clean

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MFLAGS)

bonus:
	make all -C $(BONUS)

clean: 
	rm -f $(OBJS)
	# make fclean -C $(BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re