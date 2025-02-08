NAME = cub3D

PAR = parsing
EXE = exec

SRC = main3d.c $(PAR)/parse.c $(PAR)/validate_map.c\
		get_next_line/get_next_line.c $(PAR)/map_utils.c $(PAR)/par_elem.c\
		$(PAR)/utils.c $(EXE)/handle_actions.c


OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

DEL = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx_linux
MLX = $(MLX_DIR)/libmlx.a

GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m


all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(CY)Building libft$(RC)"
	@make bonus -C $(LIBFT_DIR)

%.o: %.c cub3d.h
	@echo "$(GR)Compiling $<$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(CY)Building cub3D$(RC)"
	@$(CC) -o $@ $^ $(LIBFT)
# $(NAME): $(OBJ)

# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit

clean:
	@echo "$(YE)Cleaning all object files$(RC)\n"
	@make clean -C $(LIBFT_DIR)
	@$(DEL) $(OBJ)

fclean: clean
	@echo "$(YE)Cleaning all additional objects and libraries$(RC)\n"
	@make fclean -C $(LIBFT_DIR)
	@$(DEL) $(NAME)

re: fclean all

.PHONY: all clean fclean re