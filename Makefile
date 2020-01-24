# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/25 16:38:11 by wbraeckm          #+#    #+#              #
#    Updated: 2020/01/23 11:03:35 by ntom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh
CC = gcc
FLAGS = -O3 -Wall -Wextra -Werror #-fsanitize=address
INCLUDES = ./includes/
SRCSFOLDER = ./srcs/
OBJFOLDER = ./obj/
.DEFAULT_GOAL = all

LIBFT_FOLDER = ./libft/
include $(LIBFT_FOLDER)libft.mk

ITEMS = $(shell find srcs -type f | grep -E "\.c$$" | sed 's/srcs//g')
SRCS = $(addprefix $(SRCSFOLDER), $(ITEMS))
HEADERS = $(shell find includes -type f)
OBJ = $(addprefix $(OBJFOLDER), $(ITEMS:.c=.o))
SRCSUBS = $(shell find ./srcs -type d)
OBJSUBS = $(SRCSUBS:./srcs%=./obj%)
LONGEST = $(shell echo $(notdir $(SRCS)) | tr " " "\n" | \
	awk ' { if ( length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c \
	| sed 's/ //g')

all: $(NAME)

$(OBJFOLDER)/%.o:$(SRCSFOLDER)/%.c $(HEADERS) $(LIBFT_HEADERS) Makefile
	@printf "\r$(CC_BLUE)Compiling %-$(LONGEST)s" $(notdir $<)
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -I$(LIBFT_INCLUDES)
	@printf "$(CC_GRAY)[$(CC_LIGHT_GREEN)√$(CC_GRAY)]$(CC_EOC)"

$(OBJSUBS):
	@mkdir $@

$(NAME): $(LIBFT) $(OBJSUBS) $(OBJ)
	@printf "\r$(CC_LIGHT_CYAN)Compiling $(NAME) "
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -I$(INCLUDES) \
-I$(LIBFT_INCLUDES) $(LIBFT) -ltermcap
	@printf "$(CC_GRAY)[$(CC_LIGHT_GREEN)√$(CC_GRAY)]$(CC_EOC)"
	@printf "                                                     \n"

clean:
	@printf "$(CC_RED)"
	rm -rf $(OBJFOLDER) $(LIBFT_OBJFOLDER)
	@printf "$(CC_EOC)"

fclean: clean
	@printf "$(CC_RED)"
	rm -rf $(NAME) $(LIBFT)
	@printf "$(CC_EOC)"

re: fclean all

norm:
	@norminette $(SRCSFOLDER) $(INCLUDES)

.PHONY: norm clean fclean re
