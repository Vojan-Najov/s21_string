NAME = s21_string.a

SRC = src/s21_memchr.c \
      src/s21_memrchr.c \
      src/s21_rawmemchr.c \
src/s21_memcmp.c src/s21_memcpy.c \
		src/s21_memmove.c src/s21_memset.c src/s21_strcat.c \
		src/s21_strncat.c src/s21_strlen.c src/s21_strcpy.c \
		src/s21_strcmp.c

OBJ = $(SRC:.c=.o)

TEST_SRC = tests/test.c \
           tests/test_s21_memchr.c \
           tests/test_s21_memrchr.c \
           tests/test_s21_rawmemchr.c \
tests/test_s21_memcmp.c \
			tests/test_s21_memcpy.c tests/test_s21_memmove.c \
			tests/test_s21_memset.c tests/test_s21_strcat.c \
			tests/test_s21_strncat.c tests/test_s21_strcmp.c

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
