##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CGLinux
ConfigurationName      :=Debug
WorkspacePath          :=/home/bies/Documents/programming/c/CGLinux
ProjectPath            :=/home/bies/Documents/programming/c/CGLinux/CGLinux
IntermediateDirectory  :=../bin/Intermidiates/Debug-linux-x86_64/CGLinux
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=bies
Date                   :=02/16/20
CodeLitePath           :=/home/bies/.codelite
LinkerName             :=clang
SharedObjectLinkerName :=clang -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../bin/Debug-linux-x86_64/CGLinux/CGLinux
Preprocessors          :=$(PreprocessorSwitch)_CRT_SECURE_NO_WARNINGS $(PreprocessorSwitch)GLFW_INCLUDE_NONE $(PreprocessorSwitch)CG_DEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="CGLinux.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -m64 ../Dependencies/glad/bin/Debug-linux-x86_64/glad/libglad.a ../Dependencies/GLFW/bin/Debug-linux-x86_64/GLFW/libGLFW.a -lGL -lGLU -lX11 -ldl -lXinerama -lXcursor -lm -lXxf86vm -lXrandr -lpthread -lXi
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)src $(IncludeSwitch)../Dependencies/GLFW/include $(IncludeSwitch)../Dependencies/glad/include $(IncludeSwitch)../Dependencies/CGLM/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := clang++
CC       := clang
CXXFLAGS :=  -m64 -g -std=c99 $(Preprocessors)
CFLAGS   :=  -m64 -g -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_vlib_core_vtree.c$(ObjectSuffix) $(IntermediateDirectory)/src_vlib_core_vstring_builder.c$(ObjectSuffix) $(IntermediateDirectory)/src_graphics_graphics_buffer.c$(ObjectSuffix) $(IntermediateDirectory)/src_vlib_core_vstring.c$(ObjectSuffix) $(IntermediateDirectory)/src_vlib_core_vdynamic_array_i32.c$(ObjectSuffix) $(IntermediateDirectory)/src_vlib_core_vbinary_tree.c$(ObjectSuffix) $(IntermediateDirectory)/src_graphics_graphics_shader.c$(ObjectSuffix) $(IntermediateDirectory)/src_vlib_core_vmath.c$(ObjectSuffix) $(IntermediateDirectory)/src_vlib_core_varray.c$(ObjectSuffix) $(IntermediateDirectory)/src_vlib_core_vdynamic_table.c$(ObjectSuffix) \
	$(IntermediateDirectory)/src_vlib_core_vmemory_debug.c$(ObjectSuffix) $(IntermediateDirectory)/src_main.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d "../.build-debug/glad" "../.build-debug/GLFW" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

"../.build-debug/glad":
	@$(MakeDirCommand) "../.build-debug"
	@echo stam > "../.build-debug/glad"


"../.build-debug/GLFW":
	@$(MakeDirCommand) "../.build-debug"
	@echo stam > "../.build-debug/GLFW"




MakeIntermediateDirs:
	@test -d ../bin/Intermidiates/Debug-linux-x86_64/CGLinux || $(MakeDirCommand) ../bin/Intermidiates/Debug-linux-x86_64/CGLinux


$(IntermediateDirectory)/.d:
	@test -d ../bin/Intermidiates/Debug-linux-x86_64/CGLinux || $(MakeDirCommand) ../bin/Intermidiates/Debug-linux-x86_64/CGLinux

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_vlib_core_vtree.c$(ObjectSuffix): src/vlib/core/vtree.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/vtree.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_vtree.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_vtree.c$(PreprocessSuffix): src/vlib/core/vtree.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_vtree.c$(PreprocessSuffix) src/vlib/core/vtree.c

$(IntermediateDirectory)/src_vlib_core_vstring_builder.c$(ObjectSuffix): src/vlib/core/vstring_builder.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/vstring_builder.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_vstring_builder.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_vstring_builder.c$(PreprocessSuffix): src/vlib/core/vstring_builder.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_vstring_builder.c$(PreprocessSuffix) src/vlib/core/vstring_builder.c

$(IntermediateDirectory)/src_graphics_graphics_buffer.c$(ObjectSuffix): src/graphics/graphics_buffer.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/graphics/graphics_buffer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_graphics_graphics_buffer.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_graphics_graphics_buffer.c$(PreprocessSuffix): src/graphics/graphics_buffer.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_graphics_graphics_buffer.c$(PreprocessSuffix) src/graphics/graphics_buffer.c

$(IntermediateDirectory)/src_vlib_core_vstring.c$(ObjectSuffix): src/vlib/core/vstring.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/vstring.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_vstring.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_vstring.c$(PreprocessSuffix): src/vlib/core/vstring.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_vstring.c$(PreprocessSuffix) src/vlib/core/vstring.c

$(IntermediateDirectory)/src_vlib_core_vdynamic_array_i32.c$(ObjectSuffix): src/vlib/core/vdynamic_array_i32.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/vdynamic_array_i32.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_vdynamic_array_i32.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_vdynamic_array_i32.c$(PreprocessSuffix): src/vlib/core/vdynamic_array_i32.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_vdynamic_array_i32.c$(PreprocessSuffix) src/vlib/core/vdynamic_array_i32.c

$(IntermediateDirectory)/src_vlib_core_vbinary_tree.c$(ObjectSuffix): src/vlib/core/vbinary_tree.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/vbinary_tree.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_vbinary_tree.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_vbinary_tree.c$(PreprocessSuffix): src/vlib/core/vbinary_tree.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_vbinary_tree.c$(PreprocessSuffix) src/vlib/core/vbinary_tree.c

$(IntermediateDirectory)/src_graphics_graphics_shader.c$(ObjectSuffix): src/graphics/graphics_shader.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/graphics/graphics_shader.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_graphics_graphics_shader.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_graphics_graphics_shader.c$(PreprocessSuffix): src/graphics/graphics_shader.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_graphics_graphics_shader.c$(PreprocessSuffix) src/graphics/graphics_shader.c

$(IntermediateDirectory)/src_vlib_core_vmath.c$(ObjectSuffix): src/vlib/core/vmath.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/vmath.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_vmath.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_vmath.c$(PreprocessSuffix): src/vlib/core/vmath.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_vmath.c$(PreprocessSuffix) src/vlib/core/vmath.c

$(IntermediateDirectory)/src_vlib_core_varray.c$(ObjectSuffix): src/vlib/core/varray.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/varray.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_varray.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_varray.c$(PreprocessSuffix): src/vlib/core/varray.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_varray.c$(PreprocessSuffix) src/vlib/core/varray.c

$(IntermediateDirectory)/src_vlib_core_vdynamic_table.c$(ObjectSuffix): src/vlib/core/vdynamic_table.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/vdynamic_table.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_vdynamic_table.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_vdynamic_table.c$(PreprocessSuffix): src/vlib/core/vdynamic_table.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_vdynamic_table.c$(PreprocessSuffix) src/vlib/core/vdynamic_table.c

$(IntermediateDirectory)/src_vlib_core_vmemory_debug.c$(ObjectSuffix): src/vlib/core/vmemory_debug.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/vlib/core/vmemory_debug.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vlib_core_vmemory_debug.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vlib_core_vmemory_debug.c$(PreprocessSuffix): src/vlib/core/vmemory_debug.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vlib_core_vmemory_debug.c$(PreprocessSuffix) src/vlib/core/vmemory_debug.c

$(IntermediateDirectory)/src_main.c$(ObjectSuffix): src/main.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/CGLinux/src/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.c$(PreprocessSuffix): src/main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.c$(PreprocessSuffix) src/main.c

##
## Clean
##
clean:
	$(RM) -r ../bin/Intermidiates/Debug-linux-x86_64/CGLinux/


