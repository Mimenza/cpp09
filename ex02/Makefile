# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 13:50:11 by emimenza          #+#    #+#              #
#    Updated: 2024/09/10 20:52:08 by emimenza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#CC = c++
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98  -g
RM = rm -rf
NAME = PmergeMe

SRCS = main.cpp\
	   srcs/PmergeMe.cpp
	   
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all clean
	./$(NAME)

.PHONY: all clean fclean re run