NAME = pixelizer

CXX = g++

CXXFLAGS = -L/usr/X11R6/lib -lm -lpthread -lX11 -I ./CImg -I includes

SRCS = srcs/main.cpp srcs/Color.cpp srcs/Args.cpp srcs/BayerMatrix.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
