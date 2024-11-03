CXXFLAGS = -Wall -Wextra -Werror
CXXFLAGS += -std=c++98

CXX = c++

SRC = main.cpp BitcoinExchange.cpp

OBJ = $(SRC:.cpp=.o)

NAME = btc

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all