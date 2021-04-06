# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanjongho <hanjongho@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 16:20:59 by hanjongho         #+#    #+#              #
#    Updated: 2021/04/05 00:26:54 by hanjongho        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC				=	info/info info/set_map info/parse_cub \
					cub3d/cub3d cub3d/main \
					cub3d/save cub3d/tex cub3d/window \
					libft/ft_substr libft/ft_in_set \
					libft/ft_split libft/ft_atoi \
					libft/ft_strcmp libft/ft_endwith \
					libft/ft_strdup libft/ft_strjoin libft/ft_strlen \
					raycast/camera raycast/color \
					raycast/raycast raycast/sprite \
					raycast/sprite_utils raycast/draw \
					gnl/get_next_line util/pos util/str util/util \
										
SRCS			= $(addsuffix .c, $(addprefix srcs/, $(SRC)))
OBJS			= $(SRCS:.c=.o)
NAME			= cub3D
CC				= gcc
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS			= -Lmlx_ -lmlx -framework OpenGL -framework AppKit -lm
MLX				= libmlx.dylib

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C mlx
				@mv mlx/$(MLX) .

all:			$(NAME)

clean:
				@$(MAKE) -C mlx clean
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re