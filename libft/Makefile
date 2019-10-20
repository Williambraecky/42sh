# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 17:00:31 by wbraeckm          #+#    #+#              #
#    Updated: 2019/10/20 17:44:24 by wbraeckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_FOLDER = ./

include $(LIBFT_FOLDER)libft.mk

all: $(LIBFT)

clean:
	@printf "$(CC_RED)"
	rm -rf $(LIBFT_OBJFOLDER)
	@printf "$(CC_EOC)"

fclean: clean
	@printf "$(CC_RED)"
	rm -rf $(LIBFT)
	@printf "$(CC_EOC)"

re: fclean all

norm:
	@norminette $(LIBFT_SRCSFOLDER) $(LIBFT_INCLUDES)

.PHONY: norm clean fclean re
.DEFAULT_GOAL = all
