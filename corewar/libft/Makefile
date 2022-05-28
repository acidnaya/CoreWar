NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRC = ft_lstiter.c ft_putchar_fd.c ft_strdel.c ft_strncpy.c ft_atoi.c \
		ft_lstmap.c ft_putendl.c ft_strdup.c ft_strnequ.c ft_bzero.c \
		ft_lstnew.c ft_putendl_fd.c ft_strequ.c ft_strnew.c ft_isalnum.c \
		ft_memalloc.c ft_putnbr.c ft_striter.c ft_strnstr.c ft_isalpha.c \
		ft_memccpy.c ft_putnbr_fd.c ft_striteri.c ft_strrchr.c ft_isascii.c \
		ft_memchr.c ft_putstr.c ft_strjoin.c ft_strsplit.c ft_isdigit.c \
		ft_memcmp.c ft_putstr_fd.c ft_strlcat.c ft_strstr.c ft_isprint.c \
		ft_memcpy.c ft_strcat.c ft_strlen.c ft_strsub.c ft_itoa.c ft_memdel.c \
		ft_strchr.c ft_strmap.c ft_strtrim.c ft_lstadd.c ft_memmove.c ft_strclr.c \
		ft_strmapi.c ft_tolower.c ft_lstdel.c ft_memset.c ft_strcmp.c ft_strncat.c \
		ft_toupper.c ft_lstdelone.c ft_putchar.c ft_strcpy.c ft_strncmp.c \
		ft_strsplit_symbols.c ft_strchr_index.c \
		printf.c print_numbers.c print_pointer.c libft_funcs_part1.c \
		get_format.c print_chars_and_strings.c \
		get_int_width.c get_double_width.c put_signed_intgrs.c \
		put_unsigned_intgrs.c put_floats.c put_long_floats.c \
		print_date.c parse_data_type.c switch_formatting.c \
		get_next_line.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):
	@ gcc $(FLAGS) -c $(SRC)
	@ ar rc $(NAME) $(OBJ)
	@ ranlib $(NAME)

clean:
	@ rm -f $(OBJ)

fclean: clean
	@ rm -f $(NAME)

re: fclean all
