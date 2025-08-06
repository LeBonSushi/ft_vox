# Project Configuration
NAME        := ft_vox
SRCDIR      := srcs
INCDIR      := includes
OBJDIR      := obj
LIBDIR      := lib

# Compiler Configuration
CXX         := g++
CC          := gcc
CXXFLAGS    := -Wall -Wextra -Werror -std=c++17 -g
CFLAGS      := -Wall -Wextra -Werror -g
INCLUDES    := -I$(INCDIR) -I$(LIBDIR)/glad/include

# GLFW Libraries
LIBS        := -lglfw -lGL -lm -ldl
UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS    += -lX11 -lXrandr -lXinerama -lXcursor -lXi
endif

# Source Files
SRCS        := $(wildcard $(SRCDIR)/*.cpp)
GLAD_SRC    := $(LIBDIR)/glad/src/glad.c
OBJS        := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS)) \
               $(OBJDIR)/glad.o

# Ensure GLAD source exists before building
BUILD_DEPS := $(GLAD_SRC)

# Main Targets
.PHONY: all clean fclean re run

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CXX) $(OBJS) $(LIBS) -o $@
	@echo "✓ Build complete!"

# GLAD Source Generation
$(GLAD_SRC):
	@echo "Setting up GLAD..."
	@mkdir -p $(LIBDIR)/glad
	@wget -q -O $(LIBDIR)/glad.zip "https://github.com/Dav1dde/glad/archive/refs/heads/master.zip"
	@unzip -q $(LIBDIR)/glad.zip -d $(LIBDIR)
	@python3 -m pip install --user --quiet $(LIBDIR)/glad-master/
	@~/.local/bin/glad --generator=c --spec=gl --api=gl=4.6 --profile=core --out-path=$(LIBDIR)/glad
	@rm -f $(LIBDIR)/glad.zip
	@rm -rf $(LIBDIR)/glad-master
	@echo "✓ GLAD setup complete!"

# Compilation Rules
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/glad.o: $(GLAD_SRC) | $(OBJDIR)
	@echo "Compiling GLAD..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

# Clean Rules
clean:
	@rm -rf $(OBJDIR)
	@echo "✓ Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "✓ Cleaned executable"

# Full clean including GLAD (use with caution)
distclean: fclean
	@rm -rf $(LIBDIR)/glad
	@echo "✓ Full clean complete"

re: fclean all

run: $(NAME)
	@./$(NAME)