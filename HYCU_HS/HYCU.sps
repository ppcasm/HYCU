# Sunplus S+core IDE Project File - Name = "HYCU"
# Sunplus S+core IDE Generated Build File Format Version V2.6.1
#**DO NOT EDIT**
CFG = Debug

# Begin Project

!IF "$(CFG)" == "HYCU - Debug"

OutPut Type = elf
OutPut Dir = Debug
Inc Path = 
Lib Path = 
Compiler = ..\S_CORE~1.1\GNU\bin\gcc
Compiler DefFlag = -mscore7 -mel -g -Wall
Compiler AddFlag = 
Assembler = ..\S_CORE~1.1\GNU\bin\as
Assembler DefFlag = -Wa,-gdwarf-2  -x assembler-with-cpp
Assembler AddFlag = 
Linker = ..\S_CORE~1.1\GNU\bin\ld
Linker DefFlag = -T$(LDSCRIPT)   -lm -lc -lgcc
Linker AddFlag = -Wl,-Map,$@.map
RM = ..\S_CORE~1.1\GNU\bin\rm
RM Flag = 
AR = ..\S_CORE~1.1\GNU\bin\ar
AR Flag = 
OBJCOPY = ..\S_CORE~1.1\GNU\bin\objcopy
OBJCOPY Flag = 
OBJDUMP = ..\S_CORE~1.1\GNU\bin\objdump
OBJDUMP FLag = 
IMG2BIN = ..\S_CORE~1.1\GNU\bin\img2bin
IMG2BIN FLag = 
Lik Lib = 
Stack base address = a0fffffc
Pre-Link Description = 
Pre-Link Command = 
Post-Build Description = 
Post-Build Command = 
Custom Build Enable = 0
WorkDir = 
Custom Build = 
Custom Clean = 
Makefile = 1
SymBol File = 0
Binary File = 1
Dasm File = 0
Resource File = 1
LD File = 1
Use C++ Configuration = 0
Search Header File = 0
Initial Stop = Main
Stop Point = 
Use_DBCT = 0
Remote_Device = COM1
BOOL_CUSTOM_CMD = 0
STR_CUSTOM_CMD = 
Parallel = LPT1
Device = Simulator
TCP_Address = 
TCP_Port = 
Serial_Device = 
Serial_Speed = 
Probe_Speed = LOW
Remote_Manner = Serial
Remote_Manner = 
Enable OSInfo = 0
OSInfo Dll = 
Project Path = C:\Users\Administrator\Documents\GitHub\HYCU\HYCU_HS
OSInfo INIT = 
Show Cycles = 0
Exception Debug = 0
ROM Debug = 0
Adjust Reloc = 0
Check Sum = 0
ReDownload Data = 1
Class View = 1
Original Path = 
Replaced Path = 
Debug Level = 0
EXCP_ADDR = 0xA0000000
Initial Address = 
Address Check = 0
!ELSEIF "$(CFG)" == "HYCU - Release"

OutPut Type = elf
OutPut Dir = Release
Inc Path = 
Lib Path = 
Compiler = ..\S_CORE~1.1\GNU\bin\gcc
Compiler DefFlag = -mscore7 -mel -O2 -Wall
Compiler AddFlag = 
Assembler = ..\S_CORE~1.1\GNU\bin\as
Assembler DefFlag = -x assembler-with-cpp
Assembler AddFlag = 
Linker = ..\S_CORE~1.1\GNU\bin\ld
Linker DefFlag = -T$(LDSCRIPT)   -lm -lc -lgcc
Linker AddFlag = -Wl,-Map,$@.map
RM = ..\S_CORE~1.1\GNU\bin\rm
RM Flag = 
AR = ..\S_CORE~1.1\GNU\bin\ar
AR Flag = 
OBJCOPY = ..\S_CORE~1.1\GNU\bin\objcopy
OBJCOPY Flag = 
OBJDUMP = ..\S_CORE~1.1\GNU\bin\objdump
OBJDUMP FLag = 
IMG2BIN = ..\S_CORE~1.1\GNU\bin\img2bin
IMG2BIN FLag = 
Lik Lib = 
Stack base address = a0fffffc
Pre-Link Description = 
Pre-Link Command = 
Post-Build Description = 
Post-Build Command = 
Custom Build Enable = 0
WorkDir = 
Custom Build = 
Custom Clean = 
Makefile = 1
SymBol File = 0
Binary File = 0
Dasm File = 0
Resource File = 1
LD File = 1
Use C++ Configuration = 0
Search Header File = 0
Initial Stop = Main
Stop Point = 
Use_DBCT = 0
Remote_Device = COM1
BOOL_CUSTOM_CMD = 0
STR_CUSTOM_CMD = 
Parallel = LPT2
Device = Simulator
TCP_Address = 
TCP_Port = 
Serial_Device = 
Serial_Speed = 
Probe_Speed = LOW
Remote_Manner = Serial
Remote_Manner = 
Enable OSInfo = 0
OSInfo Dll = 
Project Path = 
OSInfo INIT = 
Show Cycles = 0
Exception Debug = 0
ROM Debug = 0
Adjust Reloc = 0
Check Sum = 0
ReDownload Data = 1
Class View = 1
Original Path = 
Replaced Path = 
Debug Level = 0
EXCP_ADDR = 0xA0000000
Initial Address = 
Address Check = 0
!ENDIF

# Name "HYCU - Debug
# Name "HYCU - Release
# Begin SubItem "HYCU files"

# Begin Group "Source Files"
#PROP Default_Filter = c;cpp;cc;C;cxx;asm;s;

# Begin Source File
SOURCE=.\libgloss.c
USEPARAM=FALSE
PARAM=
# End Source File

# Begin Source File
SOURCE=.\main.c
USEPARAM=FALSE
PARAM=
# End Source File

# End Group
# Begin Group "Header Files"
#PROP Default_Filter = h;inc;

# Begin Source File
SOURCE=.\defz.h
USEPARAM=FALSE
PARAM=
# End Source File

# Begin Source File
SOURCE=.\font.h
USEPARAM=FALSE
PARAM=
# End Source File

# Begin Source File
SOURCE=.\image.h
USEPARAM=FALSE
PARAM=
# End Source File

# Begin Source File
SOURCE=.\Resource.h
USEPARAM=FALSE
PARAM=
# End Source File

# Begin Source File
SOURCE=.\Resource.inc
USEPARAM=FALSE
PARAM=
# End Source File

# End Group
# Begin Group "Resource Files"
#PROP Default_Filter = rc;

# Begin Source File
SOURCE=.\HYCU.rc
USEPARAM=FALSE
PARAM=
# End Source File

# End Group
# Begin Group "External Dependencies"
#PROP Default_Filter = 

# Begin Source File
SOURCE=.\HYCU_Prog.ld
USEPARAM=FALSE
PARAM=
# End Source File

# Begin Source File
SOURCE=.\HYCU_startup.s
USEPARAM=FALSE
PARAM=
# End Source File

# Begin Source File
SOURCE=.\Makefile
USEPARAM=FALSE
PARAM=
# End Source File

# End Group
# Begin Group "External Headers"
#PROP Default_Filter = h;

# End Group
# End SubItem
# End Project
