##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=glad
ConfigurationName      :=Debug
WorkspacePath          :=/home/bies/Documents/programming/c/CGLinux
ProjectPath            :=/home/bies/Documents/programming/c/CGLinux/Dependencies/glad
IntermediateDirectory  :=bin-int/Debug-linux-x86_64/glad
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
OutputFile             :=bin/Debug-linux-x86_64/glad/libglad.a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="glad.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -m64
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)include 
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
CXXFLAGS :=  -m64 -fPIC -g -std=c99 $(Preprocessors)
CFLAGS   :=  -m64 -fPIC -g -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_glad.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/bies/Documents/programming/c/CGLinux/.build-debug"
	@echo rebuilt > "/home/bies/Documents/programming/c/CGLinux/.build-debug/glad"

MakeIntermediateDirs:
	@test -d bin-int/Debug-linux-x86_64/glad || $(MakeDirCommand) bin-int/Debug-linux-x86_64/glad


bin-int/Debug-linux-x86_64/glad:
	@test -d bin-int/Debug-linux-x86_64/glad || $(MakeDirCommand) bin-int/Debug-linux-x86_64/glad

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_glad.c$(ObjectSuffix): src/glad.c 
	$(CC) $(SourceSwitch) "/home/bies/Documents/programming/c/CGLinux/Dependencies/glad/src/glad.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_glad.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_glad.c$(PreprocessSuffix): src/glad.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_glad.c$(PreprocessSuffix) src/glad.c

##
## Clean
##
clean:
	$(RM) -r bin-int/Debug-linux-x86_64/glad/


