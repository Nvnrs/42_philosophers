SRC_DIR = /src
UTILS_DIR = $(SRC_DIR)/utils
CHECKS_DIR = $(SRC_DIR)/checks
DEBUG_DIR = $(SRC_DIR)/debug
INIT_DIR = $(SRC_DIR)/init
THREADS_DIR = $(SRC_DIR)/threads

SRC_UTILS = $(UTILS_DIR)/ft_atoi_ul.c \
			$(UTILS_DIR)/ft_putstr.c \
			$(UTILS_DIR)/ft_strlen.c \
			$(UTILS_DIR)/tab.c \
			$(UTILS_DIR)/philo.c

SRC_CHECKS = $(CHECKS_DIR)/checks.c \
			$(CHECKS_DIR)/is_number.c

SRC_INIT = $(INIT_DIR)/table.c \
			$(INIT_DIR)/philo.c 

SRC_DEBUG = $(DEBUG_DIR)/colors.c \
			$(DEBUG_DIR)/table.c \
			$(DEBUG_DIR)/philo.c 

SRC_THREADS = $(THREADS_DIR)/action.c \
			$(THREADS_DIR)/create.c \
			$(THREADS_DIR)/end.c \
			$(THREADS_DIR)/routine.c \
			$(THREADS_DIR)/sleep.c \
			$(THREADS_DIR)/forks.c \

SRC = $(SRC_DIR)/main.c \
		$(SRC_UTILS) \
		$(SRC_CHECKS) \
		$(SRC_DEBUG) \
		$(SRC_INIT) \
		$(SRC_THREADS) 

ALLDIR = $(OBJ_DIR) \
		$(OBJ_DIR)$(SRC_DIR) \
		$(OBJ_DIR)$(UTILS_DIR) \
		$(OBJ_DIR)$(CHECKS_DIR) \
		$(OBJ_DIR)$(DEBUG_DIR) \
		$(OBJ_DIR)$(INIT_DIR) \
		$(OBJ_DIR)$(THREADS_DIR) 

OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
CC = cc
CFLAGS += -Wall -Wextra -Werror -g -Isrc -fsanitize=address
NAME = philo

all : $(NAME)

$(ALLDIR):
	mkdir $@

$(OBJ): $(OBJ_DIR)/%.o:%.c
	$(CC) $(CFLAGS) -c $(<) -o $(@)

$(NAME) : $(MYLIB42) $(ALLDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MYLIB42) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

PHONY : clean fclean re all