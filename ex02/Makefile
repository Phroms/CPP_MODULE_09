# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrimald <agrimald@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 13:30:57 by agrimald          #+#    #+#              #
#    Updated: 2025/03/20 20:50:40 by agrimald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe
CPP = c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98
RM = rm -rf
CYAN = \033[96m
YELLOW = \033[93m
RED = \033[91m
END_COLOR = \033[0m

SRC = main.cpp PmergeMe.cpp

INC = PmergeMe.hpp

OBJECTS = $(SRC:.cpp=.o)

all: banner $(NAME)

banner:
		 printf "\n"

$(NAME): $(OBJECTS)
		 printf "$(CYAN)\nCompiling!!\n$(END_COLOR)\n"
		 $(CPP) $(CPPFLAGS) -o $@ $^

%.o: %.cpp $(INC) Makefile
		 printf "$(YELLOW)Generating objects .... %s $(END_COLOR)\r\n" $@
		 $(CPP) $(CPPFLAGS) -c $< -o $@

fclean: clean
		 $(RM) $(NAME) $(OBJECTS)

clean:
		 printf "$(RED)\nRemoving!!\n$(END_COLOR)\n"
		 $(RM) $(OBJECTS)

re: fclean all

.PHONY: re clean fclean all

.SILENT:
