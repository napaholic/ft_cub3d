NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MFLAGS = -L ./mlx -lmlx -framework OpenGL -framework AppKit

# SRCS = 01_untextured_raycast.c
# SRCS = 02_textured_raycast.c
# SRCS = 03_img_textured_raycast.c
SRCS = 04_floor_ceiling.c 04_read_map.c
# SRCS = 05_sprite_raycast.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

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