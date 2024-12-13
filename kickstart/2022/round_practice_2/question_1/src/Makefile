ifndef VERBOSE
.SILENT:
endif

APPNAME  := program
SOURCES  := $(shell find . -maxdepth 1 -name "*.cpp")
OBJDIR   := objects
DEPFLAGS  = -MT $@ -MMD -MP -MF $(OBJDIR)/$*.d
DEPFILES := $(SOURCES:%.cpp=$(OBJDIR)/%.d)
OBJFILES := $(DEPFILES:%.d=%.o)
INCDIRS  := -I ../../../../../include

CXX := g++
CXXFLAGS := -g -std=c++17 -Wall -Wextra -Werror -pedantic -O3 $(INCDIRS)

define mkdir_for_target
test -d $(@D) \
  || ( echo "Creating directory $(@D)" && mkdir -p $(@D) ) \
  || echo Unable to create $(@D);
endef

define mkdir_target
test -d $@ \
  || ( echo "Creating directory $@" && mkdir -p $@ ) \
  || echo Unable to create $@;
endef

.PHONY: all clean

all: $(APPNAME)

$(APPNAME) : $(OBJFILES)
	$(mkdir_for_target)
	$(CXX) $(CXXFLAGS) -o $(APPNAME) $(OBJFILES)

$(OBJDIR)/%.o : %.cpp $(OBJDIR)/%.d | $(OBJDIR)
	@echo Compiling $<
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -o $@ -c $<

$(OBJDIR) :
	$(mkdir_target)

$(DEPFILES) :

include $(wildcard $(DEPFILES))

clean :
	@echo Removing objects and dependency files
	rm -rf $(OBJDIR) > /dev/null 2>&1
	@echo Removing executable
	rm -f $(APPNAME) > /dev/null 2>&1
