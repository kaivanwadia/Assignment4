CXXFLAGS = -w $(shell llvm-config --cxxflags) -fno-rtti

all: dce-pass.so licm-pass.so
dce: dce-pass.so
licm: licm-pass.so

DCEPass.o: DCEPass.cpp DCEPass.h Makefile
	$(CXX) $(CXXFLAGS) DCEPass.cpp -c -o $@
LicmPass.o: LicmPass.cpp LicmPass.h Makefile
	$(CXX) $(CXXFLAGS) LicmPass.cpp -c -o $@
DFAFramework.o: DFAFramework.h Makefile
	$(CXX) $(CXXFLAGS) DFAFramework.h -c -o $@
Worklist.o: Worklist.h Makefile
	$(CXX) $(CXXFLAGS) Worklist.h -c -o $@
Meet.o: Meet.h Makefile
	$(CXX) $(CXXFLAGS) Meet.h -c -o $@
Transfer.o: Transfer.h Makefile
	$(CXX) $(CXXFLAGS) Transfer.h -c -o $@
Hasher.o: Hasher.h Makefile
	$(CXX) $(CXXFLAGS) Hasher.h -c -o $@
Equal.o: Equal.h Makefile
	$(CXX) $(CXXFLAGS) Equal.h -c -o $@

dce-pass.so: DCEPass.o
	$(CXX) -shared $^ -o $@
licm-pass.so: LicmPass.o
	$(CXX) -shared $^ -o $@
clean:
	rm -f *.o *~ *.so
