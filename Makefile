# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: sreerink <sreerink@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2024/07/18 20:44:53 by sreerink      #+#    #+#                  #
#    Updated: 2024/11/04 18:05:44 by sreerink      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= 		philo

RM= 		rm -rf

FLAGS= 		-pthread # -Wall -Werror -Wextra

SRC_DIR=	src

OBJ_DIR=	obj

SRCS= 		$(addprefix $(SRC_DIR)/, main.c parsing.c error_philo.c \
			init_data.c mutex_set_get.c simulation.c philo_actions.c \
			threads.c monitor.c time.c clean_data.c utils.c)

OBJ=		$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

HEADERS=	-I ./include

all:		$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME): 	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_DIR)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
