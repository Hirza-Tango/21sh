NAME=21sh
DEPS=get_next_line/get_next_line.o libft/libft.a
LIBFT_DIR=libft
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=ft_readline/ft_readline.a ft_shell_parser/ft_shell_parser.a \
	$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I . -I $(INCLUDES) -Ofast
ifdef COMPILER_ARGS
CFLAGS+= -D$(COMPILER_ARGS)
endif
CFILES=	ft_getenv.c		ft_setenv.c		ft_unsetenv.c	mini_cd.c		\
		mini_echo.c		mini_env.c		mini_launch.c	mini_pwd.c		\
		mini_setenv.c	mini_unsetenv.c	utils.c			main.c			\
		signal.c		parser.c

OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(OBJ) $(REL_DEPS)
	@gcc $(CFLAGS) -o $(NAME) $^ -ltermcap

$(REL_DEPS):
	@make -C $(dir $@)

build/%.o: %.c
	@mkdir -p build/ft_readline
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME);

clean fclean re::
	@for file in $(dir $(REL_DEPS)) ; do $(MAKE) -C $$file $@ ; done

clean::
	@rm -rf build/

fclean:: clean
	@rm -rf $(NAME)

re:: fclean all

.PHONY: clean fclean re all $(REL_DEPS)