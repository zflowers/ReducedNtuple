ROOTCFLAGS    = $(shell root-config --cflags)
ROOTGLIBS     = $(shell root-config --glibs)

#RFCFLAGS    = $(shell restframes-config --cxxflags)
#RFGLIBS     = $(shell restframes-config --libs)

CXX            = g++

#CXXFLAGS       = -fPIC -Wall -O3 -g
CXXFLAGS       = $(filter-out -stdlib=libc++ -pthread , $(ROOTCFLAGS))
CXXFLAGS       += $(filter-out -stdlib=libc++ -pthread , $(RFCFLAGS))

GLIBS          = $(filter-out -stdlib=libc++ -pthread , $(ROOTGLIBS))
GLIBS         += $(filter-out -stdlib=libc++ -pthread , $(RFGLIBS))
GLIBS         += -lRooFit -lRooFitCore -lMinuit #-lRooStats -shared -fPIC


INCLUDEDIR       = ./
SRCDIR           = ./
CXX	         += -I$(INCLUDEDIR) -I.
OUTOBJ	         = ./

CC_FILES := $(wildcard src/*.C)
HH_FILES := $(wildcard include/*.h)
OBJ_FILES := $(addprefix $(OUTOBJ),$(notdir $(CC_FILES:.C=.o)))

Eff: Eff_Nano_Eff.x

Eff_Nano_Eff.x: $(SRCDIR)Eff_Nano_Eff.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o Eff_Nano_Eff.x $(GLIBS) $ $< 
	touch Eff_Nano_Eff.x

Hist: Eff_Nano_Hist.x

Eff_Nano_Hist.x: $(SRCDIR)Eff_Nano_Hist.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o Eff_Nano_Hist.x $(GLIBS) $ $< 
	touch Eff_Nano_Hist.x

Plot: Plotter.x

Plotter.x: $(SRCDIR)Plotter_Eff_Nano.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o Plotter.x $(GLIBS) $ $< 
	touch Plotter.x

Stack: Stacker.x

Stacker.x: $(SRCDIR)Stacker.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o Stacker.x $(GLIBS) $ $< 
	touch Stacker.x

Scale: Scale.x

Scale.x: $(SRCDIR)ScaleFactors.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o Scale.x $(GLIBS) $ $< 
	touch Scale.x

Example_SF: Example_SF.x

Example_SF.x: $(SRCDIR)Example_MET_Trigger_SF.C $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o Example_SF.x $(GLIBS) $ $< 
	touch Example_SF.x

all: run_Eff_Nano.x

run_Eff_Nano.x: $(SRCDIR)run_Eff_Nano_Hist.cc $(OBJ_FILES) $(HH_FILES)
	$(CXX) $(CXXFLAGS) -o run_Eff_Nano.x $(GLIBS) $ $< 
	touch run_Eff_Nano.x

$(OUTOBJ)%.o: /%.C /%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUTOBJ)*.o 
	rm -f *.x
	rm -f *.so
setup:
	rm -f *.x
	rm -f *.so
	rm -f *.log
	rm -f *.d*
	rm -f *.pcm*
