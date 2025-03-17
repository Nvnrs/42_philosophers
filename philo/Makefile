SRC_DIR = /src
UTILS_DIR = $(SRC_DIR)/utils
CHECKS_DIR = $(SRC_DIR)/checks

SRC_UTILS = $(UTILS_DIR)/ft_atoi_ul.c \
			$(UTILS_DIR)/ft_putstr.c \
			$(UTILS_DIR)/ft_strlen.c

CHECKS_SRC = $(CHECKS_DIR)/checks.c \
			$(CHECKS_DIR)/is_number.c

SRC = $(SRC_DIR)/main.c \
		$(SRC_UTILS) \
		$(CHECKS_SRC)

ALLDIR = $(OBJ_DIR) \
		$(OBJ_DIR)$(SRC_DIR) \
		$(OBJ_DIR)$(UTILS_DIR) \
		$(OBJ_DIR)$(CHECKS_DIR) \

OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
CC = cc
CFLAGS += -Wall -Wextra -Werror -g -Isrc
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