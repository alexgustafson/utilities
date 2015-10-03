# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_6D53C8B4=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../../../JUCE/modules -I ../../../Monitor/Source -I ../../../DiauproMessage/Source -I ../../../ZeroConf/Source -I ../../../AudioTestApplication/Source -I ../../../TestProcessorNode/Source -I ../../../MidiUtility/Source
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -ldns_sd 

  TARGET := TestProcessprMaster
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_6D53C8B4=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../../../JUCE/modules -I ../../../Monitor/Source -I ../../../DiauproMessage/Source -I ../../../ZeroConf/Source -I ../../../AudioTestApplication/Source -I ../../../TestProcessorNode/Source -I ../../../MidiUtility/Source
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -ldns_sd 

  TARGET := TestProcessprMaster
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/ConsolidatedTests_fa3d6747.o \
  $(OBJDIR)/DiauproProcessor_140ab8f.o \
  $(OBJDIR)/DiauproTestProcessor_cd02bf39.o \
  $(OBJDIR)/ZeroConfManager_bf750d16.o \
  $(OBJDIR)/DiauproMessage_d3d3602f.o \
  $(OBJDIR)/MidiUtiliy_5e1eb1c9.o \
  $(OBJDIR)/Monitor_7abf761f.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/juce_audio_basics_89a6632b.o \
  $(OBJDIR)/juce_audio_devices_3f459929.o \
  $(OBJDIR)/juce_audio_formats_6dc6e2c9.o \
  $(OBJDIR)/juce_audio_processors_eb06e1e3.o \
  $(OBJDIR)/juce_core_a278a20d.o \
  $(OBJDIR)/juce_cryptography_8b2b6667.o \
  $(OBJDIR)/juce_data_structures_c98de09.o \
  $(OBJDIR)/juce_events_afa14001.o \
  $(OBJDIR)/juce_graphics_4cb436e5.o \
  $(OBJDIR)/juce_gui_basics_d5c7a3e1.o \
  $(OBJDIR)/juce_gui_extra_13d359a9.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking TestProcessorMaster
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning TestProcessorMaster
	@$(CLEANCMD)

strip:
	@echo Stripping TestProcessorMaster
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/ConsolidatedTests_fa3d6747.o: ../../Source/ConsolidatedTests.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConsolidatedTests.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DiauproProcessor_140ab8f.o: ../../../AudioTestApplication/Source/DiauproProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DiauproProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DiauproTestProcessor_cd02bf39.o: ../../../TestProcessorNode/Source/DiauproTestProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DiauproTestProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ZeroConfManager_bf750d16.o: ../../../ZeroConf/Source/ZeroConfManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ZeroConfManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DiauproMessage_d3d3602f.o: ../../../DiauproMessage/Source/DiauproMessage.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DiauproMessage.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MidiUtiliy_5e1eb1c9.o: ../../../MidiUtility/Source/MidiUtiliy.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MidiUtiliy.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Monitor_7abf761f.o: ../../../Monitor/Source/Monitor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Monitor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_89a6632b.o: ../../../../../JUCE/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_3f459929.o: ../../../../../JUCE/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_6dc6e2c9.o: ../../../../../JUCE/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_eb06e1e3.o: ../../../../../JUCE/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_a278a20d.o: ../../../../../JUCE/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_8b2b6667.o: ../../../../../JUCE/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_c98de09.o: ../../../../../JUCE/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_afa14001.o: ../../../../../JUCE/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_4cb436e5.o: ../../../../../JUCE/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_d5c7a3e1.o: ../../../../../JUCE/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_13d359a9.o: ../../../../../JUCE/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
