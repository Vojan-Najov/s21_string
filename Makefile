NAME = s21_string.a

INCLUDES = include/s21_string.h

SRC = src/s21_memchr.c \
      src/s21_memrchr.c \
      src/s21_rawmemchr.c \
      src/s21_memcmp.c \
      src/s21_memcpy.c \
      src/s21_memmove.c \
      src/s21_memset.c \
      src/s21_strcat.c \
      src/s21_strncat.c \
      src/s21_strchr.c \
      src/s21_strrchr.c \
      src/s21_strchrnul.c \
      src/s21_strcmp.c \
      src/s21_strncmp.c \
      src/s21_strcpy.c \
      src/s21_strncpy.c \
      src/s21_strspn.c \
      src/s21_strcspn.c \
      src/s21_strlen.c \
      src/s21_strpbrk.c \
      src/s21_strstr.c \
      src/s21_strcasestr.c \
      src/s21_strtok.c \
      src/s21_strerror.c

OBJ = $(SRC:.c=.o)

TEST_SRC = tests/test.c \
           tests/test_s21_memchr.c \
           tests/test_s21_memrchr.c \
           tests/test_s21_rawmemchr.c \
           tests/test_s21_memcmp.c \
           tests/test_s21_memcpy.c \
           tests/test_s21_memmove.c \
           tests/test_s21_memset.c \
           tests/test_s21_strcat.c \
           tests/test_s21_strncat.c \
           tests/test_s21_strchr.c \
           tests/test_s21_strrchr.c \
           tests/test_s21_strchrnul.c \
           tests/test_s21_strcmp.c \
           tests/test_s21_strncmp.c \
           tests/test_s21_strcpy.c \
           tests/test_s21_strncpy.c \
           tests/test_s21_strspn.c \
           tests/test_s21_strcspn.c \
           tests/test_s21_strlen.c \
           tests/test_s21_strpbrk.c \
           tests/test_s21_strstr.c \
           tests/test_s21_strcasestr.c \
           tests/test_s21_strtok.c \
           tests/test_s21_strerror.c

TEST_OBJ = $(TEST_SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c11 -Wpedantic -I include

$(NAME): $(OBJ)
	ar rcs $(NAME) $?

test: $(NAME) $(TEST_OBJ)
	$(CC) $(TEST_OBJ) -o $@ -L. $(NAME) -lcheck

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) test

re: fclean all

.PHONY: all clean fclean re
