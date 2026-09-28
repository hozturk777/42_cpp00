NAME        = whatever
CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++98
RM          = rm -rf

SRCS        = main.cpp

OBJS        = $(SRCS:.cpp=.o)

GREEN       = \033[0;32m
RED         = \033[0;31m
YELLOW      = \033[0;33m
RESET       = \033[0m

all: $(NAME)

%.o: %.cpp
	@echo "$(YELLOW)Compiling: $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully$(RESET)"

clean:
	@$(RM) $(OBJS)
	@echo "$(RED)Object files removed.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Executable removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
