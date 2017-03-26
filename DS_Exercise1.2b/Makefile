NAME=		DS_Exercise1.2b

CXX=		mpic++

CXXFLAGS=	-g -O0

OBJ=		$(SRC:.cpp=.o)

SRC=		DS_Exercise1.2b.cpp

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
	mpiexec -n 6 $(NAME)

.PHONY: all clean fclean re run
