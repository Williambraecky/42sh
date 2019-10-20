# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 17:00:31 by wbraeckm          #+#    #+#              #
#    Updated: 2019/10/20 17:00:33 by wbraeckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(LIBFT_FOLDER),)
LIBFT_FOLDER = ./
endif

ifeq ($(LIBFT_FLAGS),)
LIBFT_FLAGS = -Wall -Wextra -Werror -O3
endif

LIBFT = $(LIBFT_FOLDER)libft.a
LIBFT_INCLUDES = $(LIBFT_FOLDER)includes
LIBFT_SRCSFOLDER = $(LIBFT_FOLDER)srcs
LIBFT_OBJFOLDER = $(LIBFT_FOLDER)obj
LIBFT_ITEMS = $(shell find $(LIBFT_SRCSFOLDER) -type f \
	| grep -E "\.c$$" | sed 's;$(LIBFT_SRCSFOLDER);;g')
LIBFT_HEADERS = $(shell find $(LIBFT_INCLUDES) -type f)
LIBFT_SRCS = $(addprefix $(LIBFT_SRCSFOLDER), $(LIBFT_ITEMS))
LIBFT_OBJS = $(addprefix $(LIBFT_OBJFOLDER), $(LIBFT_ITEMS:.c=.o))
LIBFT_SRCSUBS = $(shell find $(LIBFT_SRCSFOLDER) -type d)
LIBFT_OBJSUBS = $(LIBFT_SRCSUBS:$(LIBFT_SRCSFOLDER)%=$(LIBFT_OBJFOLDER)%)
LIBFT_LONGEST = $(shell echo $(notdir $(LIBFT_SRCS)) | tr " " "\n" | \
	awk ' { if ( length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c \
	| sed 's/ //g')

# Colors

CC_EOC = \e[0m
CC_BOLD = \e[1m
CC_DIM = \e[2m
CC_UNDERLINE = \e[4m
CC_BLINK = \e[5m
CC_INVERT = \e[7m
CC_HIDDEN = \e[8m
CC_DEF = \e[39m
CC_BLACK = \e[30m
CC_RED = \e[31m
CC_GREEN = \e[32m
CC_YELLOW = \e[33m
CC_BLUE = \e[34m
CC_MAGENTA = \e[35m
CC_CYAN = \e[36m
CC_GRAY = \e[37m
CC_DARK_GRAY = \e[90m
CC_LIGHT_RED = \e[91m
CC_LIGHT_GREEN = \e[92m
CC_LIGHT_YELLOW = \e[93m
CC_LIGHT_BLUE = \e[94m
CC_LIGHT_MAGENTA = \e[95m
CC_LIGHT_CYAN = \e[96m
CC_WHITE = \e[97m
CC_BG_DEF = \e[49m
CC_BG_BLACK = \e[40m
CC_BG_RED = \e[41m
CC_BG_GREEN = \e[42m
CC_BG_YELLOW = \e[43m
CC_BG_BLUE = \e[44m
CC_BG_MAGENTA = \e[45m
CC_BG_CYAN = \e[46m
CC_BG_GRAY = \e[47m
CC_BG_DARK_GRAY = \e[100m
CC_BG_LIGHT_RED = \e[101m
CC_BG_LIGHT_GREEN = \e[102m
CC_BG_LIGHT_YEWLLO = \e[103m
CC_BG_LIGHT_BLUE = \e[104m
CC_BG_LIGHT_MAGENTA = \e[105m
CC_BG_LIGHT_CYAN = \e[106m
CC_BG_WHITE = \e[107m

$(LIBFT_OBJFOLDER)/%.o: $(LIBFT_SRCSFOLDER)/%.c $(LIBFT_HEADERS)
	@printf "\r$(CC_BLUE)Compiling %-$(LIBFT_LONGEST)s" $(notdir $<)
	@$(CC) $(LIBFT_FLAGS) -o $@ -c $< -I $(LIBFT_INCLUDES)
	@printf "$(CC_GRAY)[$(CC_LIGHT_GREEN)√$(CC_GRAY)]$(CC_EOC)"

$(LIBFT_OBJSUBS):
	@mkdir $@

$(LIBFT): $(LIBFT_OBJSUBS) $(LIBFT_OBJS)
	@printf "\r$(CC_LIGHT_CYAN)Compiling $(notdir $(LIBFT)) "
	@ar rc $(LIBFT) $(LIBFT_OBJS)
	@ranlib $(LIBFT)
	@printf "$(CC_GRAY)[$(CC_LIGHT_GREEN)√$(CC_GRAY)]$(CC_EOC)"
	@printf "                                                     \n"
