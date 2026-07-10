# Simple Makefile for IRC server (C++98)

CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

SRC_DIR = ft_irc
SRC = \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/clientschanns/channels.cpp \
	$(SRC_DIR)/clientschanns/clients.cpp \
	$(SRC_DIR)/init/irce.cpp \
	$(SRC_DIR)/init/networking.cpp \
	$(SRC_DIR)/commands/INVITE.cpp \
	$(SRC_DIR)/commands/JOIN.cpp \
	$(SRC_DIR)/commands/KICK.cpp \
	$(SRC_DIR)/commands/MODE.cpp \
	$(SRC_DIR)/commands/NICK.cpp \
	$(SRC_DIR)/commands/NOTICE.cpp \
	$(SRC_DIR)/commands/PASS.cpp \
	$(SRC_DIR)/commands/PRIVMSG.cpp \
	$(SRC_DIR)/commands/QUITPING.cpp \
	$(SRC_DIR)/commands/TOPIC.cpp \
	$(SRC_DIR)/commands/USER.cpp \
	$(SRC_DIR)/ProtocolManager/ProtocolManager.cpp \
	$(SRC_DIR)/ProtocolManager/ProtocolUtils.cpp

OBJ = $(SRC:.cpp=.o)

TARGET = ircserv

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
