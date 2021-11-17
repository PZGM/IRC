ifndef RESET
BLACK		:= $(shell tput -Txterm setaf 0)
RED			:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
RESET		:= $(shell tput -Txterm sgr0)
endif

NAME = ircserv

SRCS =	./srcs/join.cpp			\
		./srcs/mode.cpp			\
		./srcs/nick.cpp			\
		./srcs/oper.cpp			\
		./srcs/parsing.cpp		\
		./srcs/privmsg.cpp		\
		./srcs/server.cpp		\
		./srcs/find_host.cpp	\
		./srcs/send.cpp			\
		./srcs/user.cpp			\
		./srcs/utils.cpp		\
		./srcs/registration.cpp	\
		./srcs/pong.cpp			\
		./srcs/mode_chan.cpp	\
		./srcs/conf.cpp			\
		./srcs/who.cpp			\
		./srcs/whois.cpp		\
		./srcs/quit.cpp			\
		./srcs/part.cpp			\
		./srcs/cap.cpp			\
		# ./srcs/.cpp			\
		
OBJS = ${SRCS:.cpp=.o}

CC  = clang++

FLAGS = -Wall -Wextra -Werror

SANI = -fsanitize=address -O0 -g3 --std=c++11

$(NAME):
	@echo "\r\r${YELLOW}Compilation...${RESET}"
	@${CC} -o ${NAME} ${FLAGS} ${SRCS} 
	@echo "${GREEN}Compilation OK${RESET}"

all:  ${NAME}

clean:
	@echo "${RED}deleting ojbects${RESET}"
	@${RM} ${OBJS}

fclean:  clean
	@echo "${RED}deleting executable${RESET}"
	@${RM} ${NAME}

re: fclean all clean

exe: re
	@echo "nc -C localhost <PORT: 8080 ou 8000>"
	@echo "${YELLOW}Execution${RESET}"
	@./${NAME} conf.conf
	# @./${NAME} 8080 hrien4

exec: fclean
	@${CC} -o ${NAME} ${SRCS} 
	@echo "nc -C localhost <PORT>"
	@echo "${YELLOW}Execution${RESET}"
	@./${NAME}

san: fclean
	@${RM} ${NAME}
	@${CC} -o ${NAME} ${FLAGS} ${SANI} ${SRCS} 
	@${RM}	${OBJS}
	@echo "${YELLOW}Execution${RESET}"
	@./${NAME} conf.conf

.PHONY:    all clean fclean re exe san exec
