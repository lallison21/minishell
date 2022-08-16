NAME		=	minishell

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
RM			=	rm -f
LIBFT		=	-L sources/libft -lft
BREW		=	-L /Users/$(USER)/.brew/opt/readline/lib -lreadline
HISTORY		=	-L /Users/$(USER)/.brew/opt/readline/lib -lhistory

SOURCES_DIR	=	sources/
UTILS_DIR	=	utils/
BUILT_DIR	=	builtins/
HEADER_DIR	=	includes/

SRCS		=	$(addprefix $(SOURCES_DIR),	dollar_sign.c		error_msg.c		\
											ft_signal.c			minishell_main.c\
											quotes_operation.c	parsing.c		\
											command_complite.c	wildcard.c		\
											first_bonus_part.c	)
UTILS		=	$(addprefix $(UTILS_DIR),	check_utils.c		env_utils.c		\
											equals_operation.c	utils.c			\
											utils2.c			utils3.c		\
											utils4.c			refactoring_env.c)
BUILTINS	=	$(addprefix $(BUILT_DIR),	exit.c				echo.c			\
											env.c				export.c		\
											pwd.c				unset.c			\
											cd.c				)
HEADER		=	$(addprefix $(HEADER_DIR),	minishell.h			)

OBJS		=	$(SRCS:%.c=%.o) $(UTILS:%.c=%.o) $(BUILTINS:%.c=%.o)

WHITE   	=	\033[0m
BLACK   	=	\033[0;30m
RED     	=	\033[0;31m
GREEN   	=	\033[0;32m
YELLOW  	=	\033[0;33m
BLUE    	=	\033[0;34m
MAGENTA 	=	\033[0;35m
CYAN    	=	\033[0;36m

.PHONY		:	all clean fclean re

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				@afplay ./sound/all.mp3 &
				@make -C sources/libft
				@echo "[$(BLUE)MINISHELL$(WHITE)] OBJECT FILES CREATED\n\c"
				@$(CC) $(CFLAGS) $(BREW) $(HISTORY) $(LIBFT) $(OBJS) -o $(NAME)
				@echo "[$(BLUE)MINISHELL$(WHITE)] EXECUTABLE FILE CREATED\n\c"

%.o			:	%.c $(HEADER)
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo "$(GREEN)❱$(WHITE)\c"

clean		:
				@afplay ./sound/clean.mp3 &
				@make -C sources/libft clean
				@$(RM) $(OBJS)
				@echo "$(YELLOW)Object files deleted$(WHITE)"

fclean		:
				@afplay ./sound/fclean.mp3 &
				@make -C sources/libft clean
				@$(RM) $(OBJS)
				@echo "$(YELLOW)Object files deleted$(WHITE)"
				@make -C sources/libft fclean
				@$(RM) $(NAME)
				@echo "$(YELLOW)Executable file deleted$(WHITE)"

re			:
				@afplay ./sound/re.mp3 &
				@make -C sources/libft clean
				@$(RM) $(OBJS)
				@echo "$(YELLOW)Object files deleted$(WHITE)"
				@make -C sources/libft fclean
				@$(RM) $(NAME)
				@echo "$(YELLOW)Executable file deleted$(WHITE)"
				@make -C .