NAME = s21_string.a

SRC = src/s21_memchr.c src/s21_strlen.c

OBJ = $(SRC:.c=.o)

TEST_SRC = tests/test_s21_memchr.c tests/test.c

TEST_OBJ = $(TEST_SRC:.c=.o)

CCFLAGS = -Wall -Wextra -Werror -I include

$(NAME): $(OBJ)
	ar rcs $(NAME) $?

test: $(NAME) $(TEST_OBJ)
	gcc $(CCFLAGS) $(TEST_OBJ) -o $@ -L. $(NAME) -lcheck

.c.o:
	gcc $(CCFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
