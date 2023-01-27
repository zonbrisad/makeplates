

###LIBSBEGIN###
PKGLIBS  = Qt5Core 
PKGLIBS += Qt5Gui 
PKGLIBS += Qt5Widgets
PKGLIBS += Qt5SerialPort
PKGLIBS += Qt5Network
###LIBSEND###

###SETTINGSBEGIN###

###SETTINGSEND###


###TOOLSBEGIN###

# Define programs and commands ----------------------------------------------
MOC       = moc              # Qt meta object compiler
QMAKE     = qmake            # Qt make program
UIC       = uic              # Qt resource file compiler






###TOOLSEND###



# 
# Qt5 Specific objects
#============================================================================

# Qt objects ----------------------------------------------------------------
MOCSRC = $(patsubst %.h,%_moc.cpp,$(MOCS))         # Generate moc source files
SRC   += $(MOCSRC)
UIH    = $(patsubst src/%.ui, src/ui_%.h, $(UI) )  # Generate UI header files



###TARGETSBEGIN###
# 
# Qt5 Specific targets
#============================================================================
# Qt Meta Object Compiler target --------------------------------------------
$(MOCSRC): %_moc.cpp : %.h 	
	@echo -en $(MSG_MOC) "\n               "
	@echo -e $@ $(F_SOURCE)
	@$(MOC) $(INCDIRS) $< -o $@

# Qt user interface header file generation target ---------------------------
$(UIH): src/ui_%.h: src/%.ui
	@echo -en $(MSG_UI) "\n               "
	@echo -e $@  $(F_SOURCE)  
	@$(UIC) $(INCDIRS) $< -o $@
###TARGETSEND###



###UTILSBEGIN###

###UTILSEND###