CXX = g++ 
CXXFLAGS = -Wall -O2 -g  -std=gnu++0x #-pg 
#CXXFLAGS = -Wall -O2  -std=gnu++0x
LDFLAGS = 


aux: graphtest.cpp
	$(CXX) $(CXXFLAGS) graphtest.cpp -c
	$(CXX) -o graphaux graphtest.o
FastDLL: FastDLL.cpp FastDLL.h
	$(CXX) $(CXXFLAGS) -c  $< 
CFLReach: CFLReach.cpp CFLReach.h FastDLL.h
	$(CXX) $(CXXFLAGS) -c  $< 
dkmerge: CFLReach FastDLL dkMerge.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) dkMerge.cpp -o dkmerge

clean:
	rm -rf *.o
	rm CFLReach DyckReach DyckIntersect SummaryEdge graphaux dkmerge
