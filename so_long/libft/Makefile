
NAME        = libft.a
SRCS        = ft_lst_last.c ft_split.c ft_strlen.c ft_memcpy.c ft_strdup.c ft_substr.c ft_strlcpy.c ft_memset.c

OBJS		= $(SRCS:%.c=%.o)
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f
LIBC		= ar rcs

.PHONY:		all clean fclean re bonus

all:		$(NAME)

$(NAME):	$(OBJS) 
			$(LIBC) $(NAME) $(OBJS)

%.o: %.c
			$(CC) -c $(CFLAGS) $?

bonus: fclean
	$(CC) $(CFLAGS) -c $(SRCS) $(SRCS_BONUS)
	$(LIBC) $(NAME) $(OBJS) $(OBJS_BONUS)

	

clean:          
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	$(CC) -nostartfiles -shared -o libft.so $(OBJS)