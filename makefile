CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -fsanitize=address

OBJ_DIR = zlasdtest
MYTEST_DIR = zmytest

# Elenco dei file oggetto senza duplicati
OBJS = \
    $(OBJ_DIR)/container/container.o \
    $(OBJ_DIR)/exercise1a/fulltest.o \
    $(OBJ_DIR)/exercise1a/simpletest.o \
    $(OBJ_DIR)/exercise1b/fulltest.o \
    $(OBJ_DIR)/exercise1b/simpletest.o \
    $(OBJ_DIR)/exercise2a/fulltest.o \
    $(OBJ_DIR)/exercise2a/simpletest.o \
    $(OBJ_DIR)/exercise2b/fulltest.o \
    $(OBJ_DIR)/exercise2b/simpletest.o \
    $(OBJ_DIR)/test.o \
    $(MYTEST_DIR)/test.o \
    main.o

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o main

# Regole di compilazione (esempio)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/**/*.o $(MYTEST_DIR)/*.o main

