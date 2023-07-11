SRCDIR = src
OBJDIR = points_o

SRCS = main.c \
	utils.c \
	repas.c \
	checker.c \
	routine.c \
	verif_mort.c \
	creation_thread.c \

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra -pthread

NAME = philosophers

all : $(NAME)

$(NAME): $(OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "🧚 tout est prêt 🧚"

$(OBJDIR)/%.o:%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJDIR)
	clear
	@echo "🧚 tout propre 🧚"

fclean : clean
	rm -f $(NAME)
	clear
	@echo "🧚 tout propre 🧚"

git : fclean
	git add *
	git commit
	git push

re : fclean all

.PHONY : all clean fclean re git

.SILENT : all clean fclean re git $(NAME) $(OBJDIR)
