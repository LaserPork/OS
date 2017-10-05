##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=OS
ConfigurationName      :=Debug
WorkspacePath          :=/Users/radekvavrik/Documents/PPR/PPR
ProjectPath            :=/Users/radekvavrik/Documents/OS
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Radek Vavřík
Date                   :=29/11/2016
CodeLitePath           :="/Users/radekvavrik/Library/Application Support/codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="OS.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/private/var/folders/41/8dnkm2cs6hgcd5f7fbvbnyk00000gn/T/AppTranslocation/005A5365-4DD4-4F38-9A14-BCA791E44C36/d/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/instructions.c$(ObjectSuffix) $(IntermediateDirectory)/tools.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Users/radekvavrik/Documents/OS/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix)main.c

$(IntermediateDirectory)/instructions.c$(ObjectSuffix): instructions.c $(IntermediateDirectory)/instructions.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Users/radekvavrik/Documents/OS/instructions.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/instructions.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/instructions.c$(DependSuffix): instructions.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/instructions.c$(ObjectSuffix) -MF$(IntermediateDirectory)/instructions.c$(DependSuffix) -MM instructions.c

$(IntermediateDirectory)/instructions.c$(PreprocessSuffix): instructions.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/instructions.c$(PreprocessSuffix)instructions.c

$(IntermediateDirectory)/tools.c$(ObjectSuffix): tools.c $(IntermediateDirectory)/tools.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Users/radekvavrik/Documents/OS/tools.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tools.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tools.c$(DependSuffix): tools.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tools.c$(ObjectSuffix) -MF$(IntermediateDirectory)/tools.c$(DependSuffix) -MM tools.c

$(IntermediateDirectory)/tools.c$(PreprocessSuffix): tools.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tools.c$(PreprocessSuffix)tools.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


