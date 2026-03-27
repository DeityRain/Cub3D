# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 11:37:40 by qdeffaux          #+#    #+#              #
#    Updated: 2025/07/16 14:54:52 by qdeffaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#compile: cc file.c -L./libft -lft -o test

# Library name
NAME = libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ift_printf -Iget_next_line
AR = ar rcs

# Header files
HEADER = libft.h
PRINTF_HEADER = ft_printf/ft_printf.h
GNL_HEADER = get_next_line/get_next_line.h

# Source files
LIBFT_SRCS = $(wildcard *.c)
PRINTF_SRCS = $(wildcard ft_printf/*.c)
GNL_SRCS = $(wildcard get_next_line/*.c)

# All source files
SRCS = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)

# Object files
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
OBJS = $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

# Colors for pretty output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Creating library $(NAME)...$(RESET)"
	$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

# Compile libft .c files to .o files
%.o: %.c $(HEADER)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ft_printf .c files to .o files
ft_printf/%.o: ft_printf/%.c $(PRINTF_HEADER) $(HEADER)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# Compile get_next_line .c files to .o files
get_next_line/%.o: get_next_line/%.c $(GNL_HEADER) $(HEADER)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Removing object files...$(RESET)"
	rm -f $(LIBFT_OBJS)
	rm -f $(PRINTF_OBJS)
	rm -f $(GNL_OBJS)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	rm -f $(NAME)

re: fclean all

# Phony targets
.PHONY: all clean fclean re

so:
	$(CC) -fPIC $(CFLAGS) -nostartfiles $(SRCS)
	$(CC) -shared -o libft.so $(OBJS)
