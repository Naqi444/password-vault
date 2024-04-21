CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
OPENSSL_LIBS = -lssl -lcrypto

SRCS = main.cpp Password.cpp PasswordVault.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = password_vault

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC) $(OPENSSL_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)
