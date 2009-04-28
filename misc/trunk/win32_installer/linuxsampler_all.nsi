; LinuxSampler Windows installer
;
; Copyright (C) 2007-2009, The LinuxSampler Developers
;
; All-in-one Installer for all subprojects / software components of the
; LinuxSampler Project.
;
; PREREQUISITES:
;
; -> You must install the file cpudesc\cpudesc.dll into the NSIS's
;    plugin directory before being able to compile this installer!
;
; -> The compiled binaries must be placed into the respecitve directories
;    under bin\ (you have to read this file in order to get those exact
;    locations and expected file names).

; Probably the best compression ratio
SetCompressor lzma

;Include Modern UI
!include "MUI.nsh"

!define RELEASE_DATE "20090428"

; The name of the installer
Name "LinuxSampler (${RELEASE_DATE})"

; The file to write
OutFile "linuxsampler_${RELEASE_DATE}_setup.exe"

; Java Runtime Environment, needed for JSampler
!define JRE_VERSION "1.6"
!define JRE_URL "http://javadl.sun.com/webapps/download/AutoDL?BundleId=11292"

; The default installation directory
InstallDir $PROGRAMFILES\LinuxSampler

; Get installation folder from registry if available
InstallDirRegKey HKCU "Software\LinuxSampler" ""

;--------------------------------
;Interface Settings

!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "linuxsampler.bmp"
!define MUI_ABORTWARNING

;--------------------------------
;Version Information

VIProductVersion "0.0.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "all-in-one installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "http://linuxsampler.org"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "The LinuxSampler Project"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" ""
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© 2003-2009 The LinuxSampler Project"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "LinuxSampler Installer (${RELEASE_DATE})"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "0.0.0"

!define BIN_TYPE_64BIT  "64 bit"
!define BIN_TYPE_686SSE "686 SSE"
!define BIN_TYPE_686    "686"

;--------------------------------
; Pages

!insertmacro MUI_PAGE_LICENSE "license.rtf"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

!insertmacro MUI_LANGUAGE "English"

;--------------------------------

Function .onInit
  Var /GLOBAL installingLinuxSampler
  Var /GLOBAL installingJSampler
  Var /GLOBAL installingQSampler
  Var /GLOBAL installinggigedit
  StrCpy $installingLinuxSampler "0"
  StrCpy $installingJSampler "0"
  StrCpy $installingQSampler "0"
  StrCpy $installinggigedit "0"
FunctionEnd

; detects CPU capabilities and determmines which native binary type to install
Function DetectSystemType
  Var /GLOBAL binType

  ; check if this is a 64 bit windows
  System::Call "kernel32::GetCurrentProcess() i .s"
  System::Call "kernel32::IsWow64Process(i s, *i .r0)"
  IntCmp $0 0 not64bit
  StrCpy $binType BIN_TYPE_64BIT
  DetailPrint "64 bit Windows detected."
  Goto DetectSystemDone

  not64bit: ; a 32 bit system

  ; check if CPU supports SSE
  cpudesc::tell
  Pop $0                     ; full identification string in $0
  StrCpy $1 $0 1, 34         ; pull out one character after SSE=
  IntFmt $2 "%u" $1          ; and turn it into a number
  IntCmpU $2 1 +1 +4 +4
  StrCpy $binType BIN_TYPE_686SSE
  DetailPrint "32 bit Windows, SSE CPU detected."
  Goto DetectSystemDone
  StrCpy $binType BIN_TYPE_686
  DetailPrint "32 bit Windows (no SSE support) detected."

  DetectSystemDone:
FunctionEnd

; Check for the presence of gtkmm, and if false, ask the user whether to
; download and install gtkmm now from the internet.
Function CheckForGtkmm
  Var /GLOBAL gtkmmSetupFile

  ClearErrors
  ; This is just a lazy check for the presence of gtkmm, we should better use:
  ; System::Call function (NSI internal function) to actually call an arbitrary
  ; gtkmm function (/method) from a gtkmm DLL to make it certain
  ReadRegStr $0 HKCU "Software\gtkmm\2.4" "Installer Language"
  IfErrors +2 0
  goto NoAbort
  MessageBox MB_YESNO "gtkmm not found. Install it now (internet connection needed)?" IDYES InstallGtkmm
    MessageBox MB_YESNO "gigedit won't work without gtkmm. Continue anyway?" IDYES NoAbort
      Abort ;  causes installer to quit
  InstallGtkmm:
    ClearErrors
	StrCpy $gtkmmSetupFile $TEMP\gtkmm-win32-runtime-2.10.11-1.exe
    NSISdl::download "http://ftp.gnome.org/pub/gnome/binaries/win32/gtkmm/2.10/gtkmm-win32-runtime-2.10.11-1.exe" $gtkmmSetupFile
    IfErrors 0 +2
	Goto InstallGtkmmFailed
	ExecWait $gtkmmSetupFile
    Delete $gtkmmSetupFile ; we don't need it anymore
	IfErrors 0 +2
	Goto InstallGtkmmFailed
	Goto NoAbort
  InstallGtkmmFailed:
	MessageBox MB_YESNO "Could not download gtkmm. gigedit won't work without gtkmm. Continue anyway?" IDYES NoAbort
      Abort ;  causes installer to quit
  NoAbort:
FunctionEnd

; Downloads and launches the JRE installer from the internet
Function GetJRE
        MessageBox MB_OK "JSampler requires Java ${JRE_VERSION}, it will now \
                         be downloaded and installed"

        StrCpy $2 "$TEMP\Java Runtime Environment.exe"
        nsisdl::download /TIMEOUT=30000 ${JRE_URL} $2
        Pop $R0 ;Get the return value
                StrCmp $R0 "success" +3
                MessageBox MB_OK "Download failed: $R0"
                Quit
        ExecWait $2
        Delete $2
FunctionEnd

; Checks if the JRE is already installed, if not it will download and install it from the internet
Function DetectJRE
  ReadRegStr $2 HKLM "SOFTWARE\JavaSoft\Java Runtime Environment" \
             "CurrentVersion"
  StrCmp $2 ${JRE_VERSION} done

  Call GetJRE

  done:
FunctionEnd

;--------------------------------

; primer things to do
Section ""
  Call DetectSystemType
SectionEnd

;--------------------------------

; The stuff to install
Section "LinuxSampler 0.5.1" SecLinuxSampler
  DetailPrint "Installing LinuxSampler binaries ..."
  StrCpy $installingLinuxSampler "1"

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  StrCmp $binType BIN_TYPE_64BIT linuxsampler64
  StrCmp $binType BIN_TYPE_686SSE linuxsampler686sse
  Goto linuxsampler686

  ; Files to install

  linuxsampler64:
  ;File bin\64\linuxsampler.exe
  ;File bin\64\liblinuxsampler-1.dll
  Goto done

  linuxsampler686sse:
  ;File bin\686sse\linuxsampler.exe
  ;File bin\686sse\liblinuxsampler-1.dll
  Goto done

  linuxsampler686:
  ;File bin\686\linuxsampler.exe
  ;File bin\686\liblinuxsampler-1.dll
  Goto done

  done:
SectionEnd

Section "JSampler 'Fantasia' 0.8a" SecJSampler
  DetailPrint "Installing JSampler binaries ..."
  ; make sure JRE is installed
  Call DetectJRE
  StrCpy $installingJSampler "1"
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  ; Files to install
  ;File bin\Fantasia-0.8a.jar
  ;File jsampler.ico
SectionEnd

Section "QSampler 0.2.1" SecQSampler
  DetailPrint "Installing QSampler binaries ..."
  StrCpy $installingQSampler "1"
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  ; Files to install
  ;File bin\qsampler.exe
  ;File bin\QtCore4.dll
  ;File bin\QtGui4.dll
  ;File bin\mingwm10.dll
  ;File qsampler.ico
SectionEnd

Section "gigedit 0.1.1" Secgigedit
  DetailPrint "Installing gigedit binaries ..."
  StrCpy $installinggigedit "1"

  ; make sure gtkmm is installed
  Call CheckForGtkmm
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  StrCmp $binType BIN_TYPE_64BIT gigedit64
  StrCmp $binType BIN_TYPE_686SSE gigedit686sse
  Goto gigedit686

  ; Files to install

  gigedit64:
  ;File bin\64\gigedit.exe
  SetOutPath "$INSTDIR\Plugins"
  ;File bin\64\libgigedit.dll
  Goto done

  gigedit686sse:
  ;File bin\686sse\gigedit.exe
  SetOutPath "$INSTDIR\Plugins"
  ;File bin\686sse\libgigedit.dll
  Goto done

  gigedit686:
  ;File bin\686\gigedit.exe
  SetOutPath "$INSTDIR\Plugins"
  ;File bin\686\libgigedit.dll
  Goto done

  done:
SectionEnd

Section "libgig 3.2.1" Seclibgig
  DetailPrint "Installing libgig binaries ..."
  ; We make this a mandatory component
  SectionIn RO
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  StrCmp $binType BIN_TYPE_64BIT libgig64
  StrCmp $binType BIN_TYPE_686SSE libgig686sse
  Goto libgig686

  ; Files to install

  libgig64:
  ;File bin\64\libgig-6.dll
  ;File bin\64\rifftree.exe
  ;File bin\64\dlsdump.exe
  ;File bin\64\gigdump.exe
  ;File bin\64\gigextract.exe
  Goto done

  libgig686sse:
  ;File bin\686sse\libgig-6.dll
  ;File bin\686sse\rifftree.exe
  ;File bin\686sse\dlsdump.exe
  ;File bin\686sse\gigdump.exe
  ;File bin\686sse\gigextract.exe
  Goto done

  libgig686:
  ;File bin\686\libgig-6.dll
  ;File bin\686\rifftree.exe
  ;File bin\686\dlsdump.exe
  ;File bin\686\gigdump.exe
  ;File bin\686\gigextract.exe
  Goto done

  done:

  ; As this is a mandatory component, we misuse it to install the uninstaller as well ...
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LinuxSampler" "DisplayName" "LinuxSampler ${RELEASE_DATE}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LinuxSampler" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LinuxSampler" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LinuxSampler" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  ;Store installation folder
  WriteRegStr HKCU "Software\LinuxSampler" "" $INSTDIR
SectionEnd

Section "libsndfile 1.0.17" Seclibsndfile
  DetailPrint "Installing libsndfile binaries ..."
  ; We make this a mandatory component
  SectionIn RO
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR

  StrCmp $binType BIN_TYPE_64BIT libsndfile64
  ; I think we don't need a SSE optimized 32 bit binary for libsndfile, one 64bit and one simple 32 bit DLL should be sufficient
  ;StrCmp $binType BIN_TYPE_686SSE libsndfile686sse
  Goto libsndfile686

  ; Files to install

  libsndfile64:
  ;File bin\64\libsndfile-1.dll
  Goto done

  libsndfile686:
  ;File bin\686\libsndfile-1.dll
  Goto done

  done:
SectionEnd

Section "Start Menu Shortcuts" SecShortcuts
  CreateDirectory "$SMPROGRAMS\LinuxSampler"

  CreateShortCut "$SMPROGRAMS\LinuxSampler\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0

  StrCmp $installingLinuxSampler '1' 0 +2
  CreateShortCut "$SMPROGRAMS\LinuxSampler\LinuxSampler 0.5.1 (backend).lnk" "$INSTDIR\linuxsampler.exe" "" "$INSTDIR\linuxsampler.exe" 0

  StrCmp $installingJSampler '1' 0 +2
  CreateShortCut '$SMPROGRAMS\LinuxSampler\JSampler Fantasia 0.8a (frontend).lnk' 'javaw' '-jar "$INSTDIR\Fantasia-0.8a.jar"' '$INSTDIR\jsampler.ico' 0

  StrCmp $installingQSampler '1' 0 +2
  CreateShortCut "$SMPROGRAMS\LinuxSampler\QSampler 0.2.1 (frontend).lnk" "$INSTDIR\qsampler.exe" "" "$INSTDIR\qsampler.ico" 0

  StrCmp $installinggigedit '1' 0 +2
  CreateShortCut "$SMPROGRAMS\LinuxSampler\gigedit 0.1.1 (stand alone).lnk" "$INSTDIR\gigedit.exe" "" "$INSTDIR\gigedit.exe" 0
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\LinuxSampler"
  ; Remove files and uninstaller
  Delete $INSTDIR\*.*
  Delete $INSTDIR\plugins\*.*
  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\LinuxSampler\*.*"
  ; Remove directories used
  RMDir "$SMPROGRAMS\LinuxSampler"
  RMDir "$INSTDIR\plugins"
  RMDir "$INSTDIR"
SectionEnd

;--------------------------------
;Descriptions

;Language strings
LangString DESC_SecLinuxSampler ${LANG_ENGLISH} "Sampler backend, including sampler engine, MIDI and audio drivers, native C++ API as well as network (LSCP) API. Use a frontend application like JSampler or QSampler to control the sampler."
LangString DESC_SecJSampler ${LANG_ENGLISH} "Graphical frontend (user interface) for LinuxSampler written in Java, supporting all current features of LinuxSampler. This is the 'Fantasia' distribution of JSampler, offering a modern skin based look."
LangString DESC_SecQSampler ${LANG_ENGLISH} "Graphical light-weight frontend (user interface) for LinuxSampler written in C++, offering a fast native user interface. NOTE: QSampler doesn't support all LinuxSampler features yet!"
LangString DESC_Secgigedit ${LANG_ENGLISH} "Graphical instrument editor for Gigasampler format v2 and v3 files. Can be used stand-alone or in conjunction with LinuxSampler. NOTE: this is yet an early development version!"
LangString DESC_Seclibgig ${LANG_ENGLISH} "C++ program library for accessing DLS (Level 1 and Level 2) and Gigasampler format (v2 and v3) files. This library is required by LinuxSampler, gigedit and QSampler."
LangString DESC_Seclibsndfile ${LANG_ENGLISH} "C program library for reading and writing files containing sampled sound (such as MS Windows WAV and the Apple/SGI AIFF format), used by gigedit to import samples."
LangString DESC_SecShortcuts ${LANG_ENGLISH} "Installs start menu shortcuts for all applications."

;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecLinuxSampler} $(DESC_SecLinuxSampler)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecJSampler} $(DESC_SecJSampler)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecQSampler} $(DESC_SecQSampler)
  !insertmacro MUI_DESCRIPTION_TEXT ${Secgigedit} $(DESC_Secgigedit)
  !insertmacro MUI_DESCRIPTION_TEXT ${Seclibgig} $(DESC_Seclibgig)
  !insertmacro MUI_DESCRIPTION_TEXT ${Seclibsndfile} $(DESC_Seclibsndfile)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecShortcuts} $(DESC_SecShortcuts)
!insertmacro MUI_FUNCTION_DESCRIPTION_END
