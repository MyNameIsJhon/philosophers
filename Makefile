# === CONFIG ===
NAME        := philo
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g -pthread
RM          := rm -f
MKDIR_P     := mkdir -p

# === PATHS ===
LIBFT_DIR   := libft
OBJ_DIR     := obj
SRC_DIR     := srcs

SRC         := $(wildcard $(SRC_DIR)/*.c)
OBJ         := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

INCLUDES    := -Iincludes -I$(LIBFT_DIR)/includes

# Couleurs/logos pour l’output
BOLD        := \033[1m
GREEN       := \033[0;32m
YELLOW      := \033[0;33m
CYAN        := \033[0;36m
RESET       := \033[0m

.PHONY: all prebuild clean fclean re

all: prebuild $(NAME)

prebuild:
	@echo "$(CYAN)[🔁] Compilation préalable de LIBFT et MLX…$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)[✅] Libft compilés.$(RESET)"

$(NAME): $(OBJ)
	@echo "$(CYAN)[🔗] Linking de l'exécutable $(NAME)…$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) \
		-L$(LIBFT_DIR) -lft \
		-o $@
	@echo "$(GREEN)[✅] Build complete: $(NAME)$(RESET)"

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR_P) $(dir $@)
	@echo "$(YELLOW)[⚙️] Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(CYAN)[🧹] Nettoyage des objets fdf…$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(CYAN)[🧹] Clean Libft et MinilibX…$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(CYAN)[💥] Suppression de l'exécutable $(NAME)…$(RESET)"
	@$(RM) $(NAME)
	@echo "$(CYAN)[💥] fclean Libft et MinilibX…$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
