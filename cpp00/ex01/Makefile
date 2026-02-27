NAME        = phonebook
CC          = c++
FLAGS       = -Wall -Wextra -Werror -std=c++98
RM          = rm -rf

SRCS        = main.cpp \
				Contact.cpp

OBJS        = $(SRCS:.cpp=.o) 

GREEN       = \033[0;32m
RESET       = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) başarıyla derlendi!$(RESET)"

clean:
	@$(RM) $(OBJS)
	@echo "Obje dosyaları temizlendi."

fclean: clean
	@$(RM) $(NAME)
	@echo "Executable (program) silindi."

re: fclean all

.PHONY: all clean fclean re