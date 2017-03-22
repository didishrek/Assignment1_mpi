NAME=		DS_Exercise01

CXX=		mpic++

CXXFLAGS=	-g -O0

OBJ=		$(SRC:.cpp=.o)

SRC=		DS_Exercise1.1.cpp

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
	mpiexec -n 4 ./$(NAME)

.PHONY: all clean fclean re run
