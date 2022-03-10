# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esylva <esylva@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 13:16:30 by crobot            #+#    #+#              #
#    Updated: 2022/03/10 18:23:32 by esylva           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

LIBFT 		= $(LIBFT_DIR)libft.a
LIBFT_DIR 	= ./libft/

LIBS 		= $(LIBFT)

HEAD 		= ./inc/
# HEADER_RDL	=	/Users/king/.brew/opt/readline/include
HEADER_RDL	=	/Users/esylva/.brew/opt/readline/include/

SRC_DIR 	= src/
PARS_DIR	= pars/
EXE_DIR		= exe/
UTL_DIR		= utils/

UTL_F		= ft_env_I.c ft_env_II.c ft_free.c ft_init.c ft_list.c ft_pid.c ft_prompt.c ft_utilz_I.c ft_utilz_II.c
PARS_F		= ft_dollar_handler.c ft_parser.c ft_parse_aid.c ft_preparser.c ft_pipe_handler.c ft_quotes_handler.c \
            	ft_redirect_handler.c ft_redirect_handler2.c ft_redirect_handler3.c \

EXE_F		= ft_pipe_work.c ft_execute.c ft_run_cd.c ft_run_echo.c ft_run_env.c ft_run_pwd.c ft_run_export.c \
				ft_run_unset.c ft_exec_utils.c ft_exit.c\

MAIN_F 		= minishell.c\

UTILS		= $(addprefix $(UTL_DIR), $(UTL_F))
PARSER		= $(addprefix $(PARS_DIR), $(PARS_F))
EXE			= $(addprefix $(EXE_DIR), $(EXE_F))
SRC_F		= $(addprefix $(SRC_DIR), $(MAIN_F) $(PARSER) $(EXE) $(UTILS))

OBJ_DIR 	= obj/
OBJ_F		= $(addprefix $(OBJ_DIR), $(UTL_F) $(PARS_F) $(EXE_F) $(MAIN_F))
OBJ			= $(patsubst %.c, %.o, $(SRC_F))

CC 			= gcc
FLAGS 		= -Wall -Werror -Wextra -g

INC 		= -I$(HEAD) -I$(HEADER_RDL)
# RL			= -L/Users/king/.brew/opt/readline/lib -lreadline
RL			= -L/Users/esylva/.brew/opt/readline/lib -lreadline

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(HEAD) Makefile
	$(CC) $(FLAGS) $(LIBS) $(INC) $(RL) $(OBJ) -o $(NAME)
	@echo "$(GREEN)$(NAME) CREATED!$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

%.o : %.c
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)LIBFT OK!$(RESET)"

clean:
	@make -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ)
	@echo "$(GREEN)CLEAR!$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "$(GREEN)EXTRA CLEAR!$(RESET)"

re: fclean all
