CXXFLAGS = $(shell llvm-config --cxxflags) -fno-rtti

all: dce-pass.so licm-pass.so
dce: dce-pass.so
licm: licm-pass.so

DCEPass.o: DCEPass.cpp DCEPass.h Makefile
	$(CXX) $(CXXFLAGS) DCEPass.cpp -c -o $@
LicmPass.o: LicmPass.cpp LicmPass.h Makefile
	$(CXX) $(CXXFLAGS) LicmPass.cpp -c -o $@

dce-pass.so: DCEPass.o
	$(CXX) -shared $^ -o $@
licm-pass.so: LicmPass.o
	$(CXX) -shared $^ -o $@
clean:
	rm -f *.o *~ *.so
