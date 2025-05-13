##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC	=	$(shell find -name "*.c")

OBJ	=	$(SRC:.c=.o)

TEST_SRC    =    $(shell find -name "*.c" ! -name "main.c")
TEST_OBJ    =    $(TEST_SRC:.c=.o)

CFLAGS    =    -W -Wall -Wextra -g3
CPPFLAGS    =    -I include/
LDFLAGS    =    --coverage -lcriterion

NAME    =    42sh
NAME_TEST    =    unit_tests

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(TEST_OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) $(NAME_TEST)

re: fclean all

tests_run: fclean $(NAME_TEST)
	./$(NAME_TEST)
	gcovr . --exclude tests/
	gcovr . --exclude tests/ --branch

$(NAME_TEST): CFLAGS += $(LDFLAGS)

$(NAME_TEST): $(TEST_OBJ)
	$(CC) -o $(NAME_TEST) $(TEST_OBJ)
