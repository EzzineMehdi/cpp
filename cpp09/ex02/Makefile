CXXFLAGS = -std=c++98
CXXFLAGS += -Wall -Wextra -Werror
# CXXFLAGS += -fsanitize=address -g

CXX = c++

SRC = main.cpp PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

NAME = PmergeMe

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
