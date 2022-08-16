NAME		=	libft.a

SRCS		=	ft_atoi.c			ft_bzero.c			ft_isalnum.c		ft_isalpha.c\
				ft_isascii.c		ft_isdigit.c		ft_isprint.c		ft_memcpy.c\
				ft_memmove.c		ft_memset.c			ft_strlen.c			ft_tolower.c\
				ft_toupper.c		ft_strchr.c			ft_strrchr.c		ft_strncmp.c\
				ft_memchr.c			ft_memcmp.c			ft_strlcat.c		ft_strlcpy.c\
				ft_strdup.c			ft_calloc.c			ft_strnstr.c		ft_substr.c\
				ft_strjoin.c		ft_strtrim.c		ft_strmapi.c		ft_striteri.c\
				ft_putchar_fd.c		ft_putstr_fd.c		ft_putendl_fd.c		ft_putnbr_fd.c\
				ft_itoa.c			ft_split.c			ft_strcmp.c			new_split.c\

SRCS_BONUS	= 	ft_lstnew.c			ft_lstadd_front.c	ft_lstsize.c		ft_lstlast.c\
				ft_lstadd_back.c	ft_lstdelone.c		ft_lstclear.c		ft_lstiter.c\
				ft_lstmap.c\

HEADER		=	libft.h
OBJ			=	$(SRCS:%.c=%.o)
OBJ_B		=	$(SRCS_BONUS:%.c=%.o)

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

WHITE   	=	\033[0m
BLACK   	=	\033[0;30m
RED     	=	\033[0;31m
GREEN   	=	\033[0;32m
YELLOW  	=	\033[0;33m
BLUE    	=	\033[0;34m
MAGENTA 	=	\033[0;35m
CYAN    	=	\033[0;36m

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

$(NAME)		:	$(OBJ) $(OBJ_B) $(HEADER)
				@ar rcs $(NAME) $?
				@echo "\n[$(BLUE)LIBFT$(WHITE)] OBJECT FILES CREATED\n\c"
				@echo "[$(BLUE)LIBFT$(WHITE)] ARCHIVE FILE CREATED\n\c"

%.o 		:	%.c $(HEADER)
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo "$(GREEN)❱$(WHITE)\c"

bonus		:
				@make OBJ="$(OBJ_B)" all

clean		:
				@rm -f $(OBJ) $(OBJ_B)

fclean		:	clean
				@$(RM) $(NAME)

re			:	fclean all
