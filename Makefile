NAME = s21_string.a

SRC = src/s21_memchr.c src/s21_memcmp.c src/s21_memcpy.c \
		src/s21_memmove.c src/s21_memset.c

OBJ = $(SRC:.c=.o)

TEST_SRC = tests/test.c tests/test_s21_memchr.c tests/test_s21_memcmp.c \
			tests/test_s21_memcpy.c tests/test_s21_memmove.c \
			tests/test_s21_memset.c

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
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
