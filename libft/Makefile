# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/12 08:11:26 by wbraeckm          #+#    #+#              #
#    Updated: 2018/09/25 17:56:45 by wbraeckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -O3 -Wall -Wextra -Werror
INCLUDES = includes/
SRCSFOLDER = srcs
OBJFOLDER = obj

ITEMS = $(shell find srcs -type f | grep -E "\.c$$" | sed 's/srcs//g')
SRCS = $(addprefix $(SRCSFOLDER), $(ITEMS))
OBJ = $(addprefix $(OBJFOLDER), $(ITEMS:.c=.o))
SRCSUBS = $(shell find ./srcs -type d)
OBJSUBS = $(SRCSUBS:./srcs%=./obj%)
LONGEST = $(shell echo $(notdir $(SRCS)) | tr " " "\n" | \
	awk ' { if ( length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)

ccblue = "\33[0;34m"
ccred = "\033[0;91m"
ccgreen = "\033[0;92m"
ccgreenhard = "\033[0;32m"
cccyan = "\033[0;96m"
ccreset = "\033[0;0m"
cclightgray = "\033[0;37m"

all: $(NAME)

$(OBJFOLDER)/%.o:$(SRCSFOLDER)/%.c
	@printf $(ccblue)
	@printf "Compiling %-$(LONGEST)s" $(notdir $<)
	@$(CC) $(FLAGS) -o $@ -c $< -I $(INCLUDES)
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "\r"

$(OBJSUBS):
	@mkdir $@

$(NAME): $(OBJSUBS) $(OBJ)
	@printf $(cccyan)
	@printf "Compiling $(NAME) "
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "                                                     \n"

clean:
	@printf $(ccred)
	/bin/rm -rf obj/
	@printf $(ccreset)

fclean: clean
	@printf $(ccred)
	/bin/rm -f $(NAME)
	@printf $(ccreset)

re: fclean all

norm:
	@norminette $(SRCS)

.PHONY: norm clean fclean re
