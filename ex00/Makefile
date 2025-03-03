# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrimald <agrimald@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 20:42:30 by agrimald          #+#    #+#              #
#    Updated: 2025/03/03 21:01:13 by agrimald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc
CPP = c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98
RM = rm -rf
CYAN = \033[96m
YELLOW = \033[93m
RED = \033[91m
END_COLOR = \033[0m

SRC = BitcoinExchange.cpp main.cpp

INC =  BitcoinExchange.hpp

OBJECTS = $(SRC:.cpp=.o)

all: banner $(NAME)

banner:
		 @printf "\n"

$(NAME): $(OBJECTS)
		 @printf "$(CYAN)\nCompiling!!\n$(END_COLOR)\n"
		 @$(CPP) $(CPPFLAGS) -o $@ $^

%.o: %.cpp $(INC) Makefile
		 @printf "$(YELLOW)Generatong objects .... %s $(END_COLOR)\r\n" $@
		 @$(CPP) $(CPPFLAGS) -c $< -o $@

fclean: clean
		 @$(RM) $(NAME) $(OBJECTS)

clean:
		 @printf "$(RED)\nRemoving!!\n$(END_COLOR)\n"
		 @$(RM) $(OBJECTS)

re: fclean all

.PHONY: re clean fclean all
