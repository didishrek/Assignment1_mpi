NAME=		DS_Exercise04

CXX=		mpic++

CXXFLAGS=	-g -O0

OBJ=		$(SRC:.cpp=.o)

SRC=		DS_Exercise1.4.cpp

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME)

clean:
	rm -vf $(OBJ)
	rm -vf *~

fclean:	clean
	rm -vf $(NAME)

re: fclean all

run:
	mpiexec -n 50 $(NAME)

.PHONY: all clean fclean re run
