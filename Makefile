NAME        = cub3D
BNS_NAME    = cub_bonus

CC          = cc
FLAGS       = -fsanitize=address -g

SRC         = mandatory/src/cub.c \
              mandatory/src/parsing/get_next_line_utils.c mandatory/src/parsing/get_next_line.c \
              mandatory/src/utils/gcollector.c mandatory/src/utils/utils3.c mandatory/src/utils/utils1.c \
              mandatory/src/utils/ft_split.c mandatory/src/utils/utils2.c mandatory/src/rendering/textures_helpers.c \
              mandatory/src/rendering/draw_utils.c mandatory/src/rendering/map2D.c mandatory/src/rendering/raycasting.c \
              mandatory/src/rendering/map3D.c mandatory/src/rendering/rays_utils.c mandatory/src/rendering/dist_utils.c \
              mandatory/src/rendering/ray_directions.c mandatory/src/movement/p_hooks.c \
              mandatory/src/parsing/parsing.c mandatory/src/parsing/parsing_helpers1.c mandatory/src/parsing/parsing_helpers2.c \
              mandatory/src/parsing/parsing_helpers3.c mandatory/src/parsing/parsing_helpers4.c mandatory/src/parsing/parsing_helpers5.c \
              mandatory/src/init/init.c mandatory/src/parsing/parsing_helpers6.c mandatory/src/parsing/parsing_helpers7.c \
              mandatory/src/rendering/textures.c

BNS_SRCS    = bonus/bonus_src/bonus_cub.c \
              bonus/bonus_src/bonus_parsing/bonus_get_next_line_utils.c \
              bonus/bonus_src/bonus_parsing/bonus_get_next_line.c \
              bonus/bonus_src/bonus_utils/bonus_gcollector.c \
              bonus/bonus_src/bonus_utils/bonus_utils1.c \
              bonus/bonus_src/bonus_utils/bonus_ft_split.c \
              bonus/bonus_src/bonus_rendering/bonus_draw_utils.c \
              bonus/bonus_src/bonus_rendering/bonus_map2D.c \
              bonus/bonus_src/bonus_rendering/bonus_raycasting.c \
              bonus/bonus_src/bonus_rendering/bonus_map3D.c \
              bonus/bonus_src/bonus_rendering/bonus_rays_utils.c \
              bonus/bonus_src/bonus_rendering/bonus_dist_utils.c \
              bonus/bonus_src/bonus_rendering/bonus_ray_directions.c \
              bonus/bonus_src/bonus_movement/bonus_p_hooks.c \
              bonus/bonus_src/bonus_parsing/bonus_parsing.c \
              bonus/bonus_src/bonus_parsing/bonus_parsing_helpers1.c \
              bonus/bonus_src/bonus_parsing/bonus_parsing_helpers2.c \
              bonus/bonus_src/bonus_parsing/bonus_parsing_helpers3.c \
              bonus/bonus_src/bonus_parsing/bonus_doors_parsing.c \
              bonus/bonus_src/bonus_parsing/bonus_parsing_helpers5.c \
              bonus/bonus_src/bonus_parsing/bonus_parsing_helpers6.c \
              bonus/bonus_src/bonus_parsing/bonus_parsing_helpers7.c \
              bonus/bonus_src/bonus_parsing/bonus_parsing_helpers4.c \
              bonus/bonus_src/sprites/sprites.c \
              bonus/bonus_src/bonus_rendering/textures.c \
              bonus/bonus_src/bonus_rendering/textures_helpers.c \
              bonus/bonus_src/bonus_utils/bonus_utils2.c \
              bonus/bonus_src/bonus_utils/bonus_utils3.c \
              bonus/bonus_src/bonus_init/bonus_init1.c \
              bonus/bonus_src/bonus_init/bonus_init2.c \
              bonus/bonus_src/bonus_init/bonus_init3.c \
              bonus/bonus_src/bonus_movement/bonus_hook.c

LIBMLX      = MLX/build/libmlx42.a

# Detect platform
UNAME_S     := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    GLFW_DIR = /usr/include
    MLXFLG   = -IMLX/include -Iinclude -I$(GLFW_DIR) -ldl -lglfw -pthread -lm
else
    GLFW_DIR = /Users/$(USER)/.brew/opt/glfw
    MLXFLG   = -IMLX/include -Iinclude -L$(GLFW_DIR)/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif

INCLUDES    = -IMLX/include -Iinclude -I$(GLFW_DIR)
LIBS        = -LMLX/build -L$(GLFW_DIR)/lib -lmlx42 -lglfw -lGL -lX11 -lm

OBJ         = $(SRC:%.c=%.o)
BNS_OBJ     = $(BNS_SRCS:%.c=%.o)

HEADER      = mandatory/includes/cub.h \
              bonus/bonus_includes/bonus_cub.h

NPROC       = $(shell nproc 2>/dev/null || sysctl -n hw.ncpu)

all: $(NAME)

$(LIBMLX):
	@cmake -S MLX -B MLX/build
	@make -C MLX/build -j$(NPROC)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "🛠️ Compiling: $<"

$(NAME): $(OBJ) $(LIBMLX)
	@$(CC) $(FLAGS) $(OBJ) $(MLXFLG) $(LIBMLX) $(LIBS) -o $(NAME)
	@echo "✅ Built: $(NAME)"

bonus: $(BNS_NAME)

$(BNS_NAME): $(BNS_OBJ) $(LIBMLX)
	@$(CC) $(FLAGS) $(BNS_OBJ) $(MLXFLG) $(LIBMLX) $(LIBS) -o $(BNS_NAME)
	@echo "✨ Built Bonus: $(BNS_NAME)"

clean:
	@rm -f $(OBJ) $(BNS_OBJ)
	@echo "🧹 Cleaning object files."

fclean: clean
	@rm -f $(NAME) $(BNS_NAME)
	@echo "💥 Full clean done."

re: fclean all

.PHONY: all clean fclean re bonus
