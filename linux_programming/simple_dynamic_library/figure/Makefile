CFLAGS  = -Wall -Werror -fPIC -g
LDFLAGS = -shared
SOURCES = figure.c
OBJECTS = $(SOURCES:.c=.o)
NAME    = libfigure.so

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME)

$(OBJECTS):
	$(CC) -c $(CFLAGS) $(SOURCES)

clean:
	@rm -f $(OBJECTS)
	@rm -f $(NAME)