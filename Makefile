# Project Configuration
NAME        := ft_vox
SRCDIR      := srcs
INCDIR      := includes
OBJDIR      := obj
LIBDIR      := lib
GLM_DIR     := $(LIBDIR)/glm

# Compiler Configuration
CXX         := c++
CC          := cc
CXXFLAGS    := -Wall -Wextra -Werror -std=c++20 -g3 -fPIE
CFLAGS      := -Wall -Wextra -Werror -g3 -fPIE
INCLUDES    := -I$(INCDIR) -I$(LIBDIR)/glad/include -I$(LIBDIR) -I$(GLM_DIR)

# GLFW Libraries
LIBS        := -lglfw -lGL -lm -ldl
UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBS    += #-lX11 -lXrandr -lXinerama -lXcursor -lXi
endif

# Source Files
SRCS        := $(wildcard $(SRCDIR)/*.cpp)
GLAD_SRC    := $(LIBDIR)/glad/src/glad.c
OBJS        := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS)) \
               $(OBJDIR)/glad.o



# Ensure GLAD source exists before building
BUILD_DEPS := $(GLAD_SRC) $(GLM_DIR)

# Main Targets
.PHONY: all clean fclean re run

all: $(BUILD_DEPS) $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	@$(CXX) $(OBJS) $(LIBS) -o $@
	@echo "✓ Build complete!"

$(GLM_DIR):
	@echo "Setting up GLM..."
	@mkdir -p $(LIBDIR)
	@wget -q -O $(LIBDIR)/glm.zip "https://github.com/g-truc/glm/archive/refs/heads/master.zip"
	@unzip -q $(LIBDIR)/glm.zip -d $(LIBDIR)
	@mv $(LIBDIR)/glm-master/glm $(GLM_DIR)
	@rm -rf $(LIBDIR)/glm.zip $(LIBDIR)/glm-master
	@echo "✓ GLM setup complete!"


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