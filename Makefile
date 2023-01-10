NAME = s21_string.a
TEST = test
REPORT = gcov_report
MEMORY_TEST = memory_test

INCLD_DIR = ./include
TEST_INCLD_DIR = ./tests

SRC_DIR = ./src
TEST_SRC_DIR = ./tests

OBJ_DIR = $(SRC_DIR)/objs
TEST_OBJ_DIR = $(TEST_SRC_DIR)/test_objs

GCOV_DIR = ./gcov_report
GCOV_OBJ_DIR = $(GCOV_DIR)/objs

SRC = $(wildcard $(SRC_DIR)/s21_*.c)
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

TEST_SRC = $(wildcard $(TEST_SRC_DIR)/test*.c)
TEST_OBJ = $(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRC:.c=.o)))

GCOV_OBJ = $(addprefix $(GCOV_OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

INCLD = $(wildcard $(INCLD_DIR)/*.h)
TEST_INCLD = $(wildcard $(TEST_INCLD_DIR)/*.h)

TEST_LIBS = -lcheck -lm

CC = gcc
MKDIR = mkdir -p 
RM = rm -f
RMDIR = rm -rf
AR = ar rcs

CFLAGS = -Wall -Wextra -Werror -std=c11 -Wpedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -g -O0

$(NAME): $(OBJ)
	$(AR) $(NAME) $?

all: $(NAME) $(TEST)

$(TEST): $(NAME) $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(TEST_LIBS) -L. $(NAME) -o $@

$(REPORT): $(GCOV_OBJ) $(TEST_OBJ)
	$(CC) $(GCOV_FLAGS) $(GCOV_OBJ) $(TEST_OBJ)  \
		-o $(GCOV_DIR)/test_coverage $(TEST_LIBS)
	./$(GCOV_DIR)/test_coverage;
	@$(RM) $(GCOV_OBJ_DIR)/s21_wctomb* $(GCOV_OBJ_DIR)/s21_ullitoa* \
		$(GCOV_OBJ_DIR)/s21_llitoa* $(GCOV_OBJ_DIR)/s21_ldtoa* \
		$(GCOV_OBJ_DIR)/s21_itoa* $(GCOV_OBJ_DIR)/s21_isinteger* \
		$(GCOV_OBJ_DIR)/s21_atoi* $(GCOV_OBJ_DIR)/s21_strtol*;
	gcov $(GCOV_OBJ_DIR)/*.gcno; 
	@mv *.gcov $(GCOV_OBJ_DIR);
	lcov -c -t "s21_string" -o $(GCOV_DIR)/report.info -d $(GCOV_OBJ_DIR) \
		--rc lcov_branch_coverage=1;
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/report.info --rc lcov_branch_coverage=1

$(MEMORY_TEST): $(clean) $(NAME) $(TEST_SRC_DIR)/memory_test.c
	$(CC) $(CFLAGS) -g -I$(INCLD_DIR) $(TEST_SRC_DIR)/memory_test.c s21_string.a -o $@
	valgrind --trace-children=yes --track-origins=yes --leak-check=full \
			--show-leak-kinds=all -s ./$(MEMORY_TEST)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLD)
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -I$(INCLD_DIR) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c  $(TEST_INCLD)
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -I$(INCLD_DIR) -I$(TEST_INCLD_DIR) -c $< -o $@

$(GCOV_OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLD)
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -I$(INCLD_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RMDIR) $(OBJ_DIR)
	$(RM) $(TEST_OBJ)
	$(RMDIR) $(TEST_OBJ_DIR)
	$(RM) -r $(GCOV_OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST)
	$(RM) -r $(GCOV_DIR)
	$(RM) $(MEMORY_TEST)

re: fclean all

.PHONY: all clean fclean re
