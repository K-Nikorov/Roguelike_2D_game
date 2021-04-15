# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kirill/msu_cmc_cg_2021/MyRoguelike

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kirill/msu_cmc_cg_2021/MyRoguelike

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kirill/msu_cmc_cg_2021/MyRoguelike/CMakeFiles /home/kirill/msu_cmc_cg_2021/MyRoguelike/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kirill/msu_cmc_cg_2021/MyRoguelike/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

game.o: game.cpp.o

.PHONY : game.o

# target to build an object file
game.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game.cpp.o
.PHONY : game.cpp.o

game.i: game.cpp.i

.PHONY : game.i

# target to preprocess a source file
game.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game.cpp.i
.PHONY : game.cpp.i

game.s: game.cpp.s

.PHONY : game.s

# target to generate assembly for a file
game.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game.cpp.s
.PHONY : game.cpp.s

game_level.o: game_level.cpp.o

.PHONY : game_level.o

# target to build an object file
game_level.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_level.cpp.o
.PHONY : game_level.cpp.o

game_level.i: game_level.cpp.i

.PHONY : game_level.i

# target to preprocess a source file
game_level.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_level.cpp.i
.PHONY : game_level.cpp.i

game_level.s: game_level.cpp.s

.PHONY : game_level.s

# target to generate assembly for a file
game_level.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_level.cpp.s
.PHONY : game_level.cpp.s

game_object.o: game_object.cpp.o

.PHONY : game_object.o

# target to build an object file
game_object.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_object.cpp.o
.PHONY : game_object.cpp.o

game_object.i: game_object.cpp.i

.PHONY : game_object.i

# target to preprocess a source file
game_object.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_object.cpp.i
.PHONY : game_object.cpp.i

game_object.s: game_object.cpp.s

.PHONY : game_object.s

# target to generate assembly for a file
game_object.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_object.cpp.s
.PHONY : game_object.cpp.s

game_structure.o: game_structure.cpp.o

.PHONY : game_structure.o

# target to build an object file
game_structure.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_structure.cpp.o
.PHONY : game_structure.cpp.o

game_structure.i: game_structure.cpp.i

.PHONY : game_structure.i

# target to preprocess a source file
game_structure.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_structure.cpp.i
.PHONY : game_structure.cpp.i

game_structure.s: game_structure.cpp.s

.PHONY : game_structure.s

# target to generate assembly for a file
game_structure.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/game_structure.cpp.s
.PHONY : game_structure.cpp.s

glad.o: glad.c.o

.PHONY : glad.o

# target to build an object file
glad.c.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/glad.c.o
.PHONY : glad.c.o

glad.i: glad.c.i

.PHONY : glad.i

# target to preprocess a source file
glad.c.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/glad.c.i
.PHONY : glad.c.i

glad.s: glad.c.s

.PHONY : glad.s

# target to generate assembly for a file
glad.c.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/glad.c.s
.PHONY : glad.c.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.s
.PHONY : main.cpp.s

resource_manager.o: resource_manager.cpp.o

.PHONY : resource_manager.o

# target to build an object file
resource_manager.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/resource_manager.cpp.o
.PHONY : resource_manager.cpp.o

resource_manager.i: resource_manager.cpp.i

.PHONY : resource_manager.i

# target to preprocess a source file
resource_manager.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/resource_manager.cpp.i
.PHONY : resource_manager.cpp.i

resource_manager.s: resource_manager.cpp.s

.PHONY : resource_manager.s

# target to generate assembly for a file
resource_manager.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/resource_manager.cpp.s
.PHONY : resource_manager.cpp.s

shader.o: shader.cpp.o

.PHONY : shader.o

# target to build an object file
shader.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/shader.cpp.o
.PHONY : shader.cpp.o

shader.i: shader.cpp.i

.PHONY : shader.i

# target to preprocess a source file
shader.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/shader.cpp.i
.PHONY : shader.cpp.i

shader.s: shader.cpp.s

.PHONY : shader.s

# target to generate assembly for a file
shader.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/shader.cpp.s
.PHONY : shader.cpp.s

sprite_renderer.o: sprite_renderer.cpp.o

.PHONY : sprite_renderer.o

# target to build an object file
sprite_renderer.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/sprite_renderer.cpp.o
.PHONY : sprite_renderer.cpp.o

sprite_renderer.i: sprite_renderer.cpp.i

.PHONY : sprite_renderer.i

# target to preprocess a source file
sprite_renderer.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/sprite_renderer.cpp.i
.PHONY : sprite_renderer.cpp.i

sprite_renderer.s: sprite_renderer.cpp.s

.PHONY : sprite_renderer.s

# target to generate assembly for a file
sprite_renderer.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/sprite_renderer.cpp.s
.PHONY : sprite_renderer.cpp.s

texture.o: texture.cpp.o

.PHONY : texture.o

# target to build an object file
texture.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/texture.cpp.o
.PHONY : texture.cpp.o

texture.i: texture.cpp.i

.PHONY : texture.i

# target to preprocess a source file
texture.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/texture.cpp.i
.PHONY : texture.cpp.i

texture.s: texture.cpp.s

.PHONY : texture.s

# target to generate assembly for a file
texture.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/texture.cpp.s
.PHONY : texture.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... main"
	@echo "... edit_cache"
	@echo "... game.o"
	@echo "... game.i"
	@echo "... game.s"
	@echo "... game_level.o"
	@echo "... game_level.i"
	@echo "... game_level.s"
	@echo "... game_object.o"
	@echo "... game_object.i"
	@echo "... game_object.s"
	@echo "... game_structure.o"
	@echo "... game_structure.i"
	@echo "... game_structure.s"
	@echo "... glad.o"
	@echo "... glad.i"
	@echo "... glad.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... resource_manager.o"
	@echo "... resource_manager.i"
	@echo "... resource_manager.s"
	@echo "... shader.o"
	@echo "... shader.i"
	@echo "... shader.s"
	@echo "... sprite_renderer.o"
	@echo "... sprite_renderer.i"
	@echo "... sprite_renderer.s"
	@echo "... texture.o"
	@echo "... texture.i"
	@echo "... texture.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
