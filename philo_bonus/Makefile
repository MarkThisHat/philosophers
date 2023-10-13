# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 11:13:39 by maalexan          #+#    #+#              #
#    Updated: 2023/10/12 23:12:23 by maalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
BNAME		:=	philo_bonus

# Directories for source, object and libraries
BSRC_DIR	:=	./srcs
BOBJ_DIR	:=	./objs
BHDR_DIR	:=	./incl

# Compilation flags
BCFLAGS		:=	-Wall -Wextra -Werror -g -I $(BHDR_DIR)

# Source files: main, args, setters, time, helpers, utils
BFUN		:=	nihilism.c \
				dialetic.c \
				praxis.c \
				atomism.c \
				hermeneutics.c \
				heuristics.c \
				operationalism.c \
#				fatalism.c \
#				existentialism.c \
#				pluralism.c \

# Object files
BOBJ		:=	$(BFUN:%.c=$(BOBJ_DIR)/%.o)

all: $(BNAME)

$(BNAME): $(BOBJ)
	cc $(BOBJ) -lpthread -o $@

$(BOBJ_DIR)/%.o: $(BSRC_DIR)/%.c
	@mkdir -p $(@D)
	cc $(BCFLAGS) -c $< -o $@

$(BOBJ_DIR)/%.o: $(BSRC_DIR)/%.c
	@mkdir -p $(@D)
	@cc $(BCFLAGS) -c $< -o $@

val: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${BNAME} || echo ""

clean:
	@[ -d ./objs ] && rm -rf ./objs || echo Object directory doesn\'t exist

fclean: clean
	@[ -f ./$(BNAME) ] && rm $(BNAME) || echo Program $(BNAME) isn\'t compiled

re: fclean all

.PHONY: all clean fclean re
