# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift

# Include any dependencies generated for this target.
include CMakeFiles/tiltshift.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tiltshift.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tiltshift.dir/flags.make

CMakeFiles/tiltshift.dir/tiltshift.cpp.o: CMakeFiles/tiltshift.dir/flags.make
CMakeFiles/tiltshift.dir/tiltshift.cpp.o: tiltshift.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tiltshift.dir/tiltshift.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tiltshift.dir/tiltshift.cpp.o -c /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift/tiltshift.cpp

CMakeFiles/tiltshift.dir/tiltshift.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tiltshift.dir/tiltshift.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift/tiltshift.cpp > CMakeFiles/tiltshift.dir/tiltshift.cpp.i

CMakeFiles/tiltshift.dir/tiltshift.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tiltshift.dir/tiltshift.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift/tiltshift.cpp -o CMakeFiles/tiltshift.dir/tiltshift.cpp.s

CMakeFiles/tiltshift.dir/tiltshift.cpp.o.requires:

.PHONY : CMakeFiles/tiltshift.dir/tiltshift.cpp.o.requires

CMakeFiles/tiltshift.dir/tiltshift.cpp.o.provides: CMakeFiles/tiltshift.dir/tiltshift.cpp.o.requires
	$(MAKE) -f CMakeFiles/tiltshift.dir/build.make CMakeFiles/tiltshift.dir/tiltshift.cpp.o.provides.build
.PHONY : CMakeFiles/tiltshift.dir/tiltshift.cpp.o.provides

CMakeFiles/tiltshift.dir/tiltshift.cpp.o.provides.build: CMakeFiles/tiltshift.dir/tiltshift.cpp.o


# Object files for target tiltshift
tiltshift_OBJECTS = \
"CMakeFiles/tiltshift.dir/tiltshift.cpp.o"

# External object files for target tiltshift
tiltshift_EXTERNAL_OBJECTS =

tiltshift: CMakeFiles/tiltshift.dir/tiltshift.cpp.o
tiltshift: CMakeFiles/tiltshift.dir/build.make
tiltshift: /usr/local/lib/libopencv_dnn.so.3.3.0
tiltshift: /usr/local/lib/libopencv_ml.so.3.3.0
tiltshift: /usr/local/lib/libopencv_objdetect.so.3.3.0
tiltshift: /usr/local/lib/libopencv_shape.so.3.3.0
tiltshift: /usr/local/lib/libopencv_stitching.so.3.3.0
tiltshift: /usr/local/lib/libopencv_superres.so.3.3.0
tiltshift: /usr/local/lib/libopencv_videostab.so.3.3.0
tiltshift: /usr/local/lib/libopencv_calib3d.so.3.3.0
tiltshift: /usr/local/lib/libopencv_features2d.so.3.3.0
tiltshift: /usr/local/lib/libopencv_flann.so.3.3.0
tiltshift: /usr/local/lib/libopencv_highgui.so.3.3.0
tiltshift: /usr/local/lib/libopencv_photo.so.3.3.0
tiltshift: /usr/local/lib/libopencv_video.so.3.3.0
tiltshift: /usr/local/lib/libopencv_videoio.so.3.3.0
tiltshift: /usr/local/lib/libopencv_imgcodecs.so.3.3.0
tiltshift: /usr/local/lib/libopencv_imgproc.so.3.3.0
tiltshift: /usr/local/lib/libopencv_core.so.3.3.0
tiltshift: CMakeFiles/tiltshift.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tiltshift"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tiltshift.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tiltshift.dir/build: tiltshift

.PHONY : CMakeFiles/tiltshift.dir/build

CMakeFiles/tiltshift.dir/requires: CMakeFiles/tiltshift.dir/tiltshift.cpp.o.requires

.PHONY : CMakeFiles/tiltshift.dir/requires

CMakeFiles/tiltshift.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tiltshift.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tiltshift.dir/clean

CMakeFiles/tiltshift.dir/depend:
	cd /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift /home/felipe/github/wenyaraujo.github.io/Projetos/tiltshift/CMakeFiles/tiltshift.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tiltshift.dir/depend

