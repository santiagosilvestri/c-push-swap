NAME		= push_swap
BONUS		= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes -I libft
DEPFLAGS	= -MMD -MP

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SHARED_SRCS	= srcs/parsing/parsing.c \
			  srcs/parsing/parsing_utils.c \
			  srcs/utils/stack/stack.c \
			  srcs/utils/stack/stack_index.c \
			  srcs/operations/operations_push.c \
			  srcs/operations/operations_rotate.c \
			  srcs/operations/operations_reverse_rotate.c \
			  srcs/operations/operations_swap.c \
			  srcs/algorithms/algorithm_utils.c

SRCS		= srcs/main/main.c \
			  srcs/main/main_utils.c \
			  $(SHARED_SRCS) \
			  srcs/utils/disorder/disorder.c \
			  srcs/utils/bench/bench.c \
			  srcs/algorithms/algorithm_position.c \
			  srcs/algorithms/sort_simple.c \
			  srcs/algorithms/sort_medium.c \
			  srcs/algorithms/sort_complex.c \
			  srcs/algorithms/sort_adaptive.c

BONUS_SRCS	= srcs/main/checker_bonus.c \
			  srcs/main/checker_utils_bonus.c \
			  $(SHARED_SRCS)

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)
DEPS		= $(sort $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d))

all: $(NAME)

bonus: $(BONUS)

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(BONUS): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS)

$(OBJS) $(BONUS_OBJS): | $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)
	rm -f $(DEPS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(BONUS)

re: fclean
	$(MAKE) all

FORCE:

-include $(DEPS)

.PHONY: all bonus clean fclean re FORCE
