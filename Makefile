build: minlexbfs.cpp disjcnt.cpp revedges.cpp
	g++ -o revedges revedges.cpp	
	g++ -o minlexbfs minlexbfs.cpp
	g++ -o disjcnt disjcnt.cpp

run-p1: minlexbfs
	./minlexbfs

run-p2: disjcnt
	./disjcnt

run-p4: revedges
	./revedges

clean:
	rm -rf minlexbfs revedges disjcnt
