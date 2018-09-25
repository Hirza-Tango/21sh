NAME=ft_shell_parser.a
DEPS=libft/libft.a
LIBFT_DIR=../libft
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I. -I$(INCLUDES) -Ofast
ifdef COMPILER_ARGS
CFLAGS+= -D$(COMPILER_ARGS)
endif
CFILES=	ft_shell_parser.c

OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(OBJ) $(REL_DEPS)
	@ar rcs $(NAME) $(OBJ)

$(REL_DEPS):
	@make -C $(dir $@)

build/%.o: %.c
	@mkdir -p build
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