SRC_DIR			=	./src/
SRC_FLS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memccpy.c \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c get_next_line.c\
					get_next_line_utils.c ft_printf.c ft_printf_part_I.c ft_printf_part_II.c\
					ft_strcmp_bonus.c

SRCS			= $($(SRC_DIR), $(SRC_FLS))

OBJ_DIR 		= obj/
OBJ_FLS			= $(SRC_FLS:.c=.o)
OBJ				= $(addprefix $(OBJ_DIR), $(OBJ_FLS))

INC 			= -I$(HEAD_DIR)
HEAD_DIR		= ./inc/
HEAD_FLS		= libft.h get_next_line.h
HEAD			= $(addprefix $(HEAD_DIR), $(HEAD_LIST))

CC				= gcc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJ_DIR) $(OBJ)
				ar rc $(NAME) $(OBJ)
				@echo "$(NAME): $(NAME) was created"

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
				@$(CC) $(FLAGS) -c $(INC) $< -o $@

clean:
				$(RM) $(OBJ_DIR)
				@echo "$(NAME): object files were deleted"

fclean:			clean
				$(RM) $(NAME)
				@echo "$(NAME): $(NAME) was deleted"

re:				fclean $(NAME) all

.PHONY:			all clean fclean re
