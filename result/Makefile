NAME = Cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MFLAGS = -L ./mlx -lmlx -framework OpenGL -framework AppKit -fsanitize=address

SRCS =	$(addprefix src/, Cub3D.c \
					get_next_line.c \
					get_next_line_utils.c \
					map_parse.c \
					movement.c \
					init.c \
					loop_hook.c \
					calculate_floor.c \
					calculate_wall.c \
					wall_cast.c \
					draw_floor.c \
					load_texture.c \
					save_map.c \
					hook_func.c \
					utils.c)
					# engine_run.c \
					# texture_set.c \
					# draw_floor.c \

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