CFLAGS=-g
CXX=g++
TESTS=test_format test_create test_simplelist test_delete test_rename test_copy test_open test_close test_write test_read test_list
OBJS=test_format.o test_create.o test_simplelist.o test_delete.o test_rename.o test_copy.o test_open.o test_close.o test_write.o test_read.o test_list.o base_test.o ../filesys.o ../operations.o

tests: ${TESTS}
	./test_format
	./test_create
	./test_simplelist
	./test_delete
	./test_rename
	./test_copy
	./test_open
	./test_close
	./test_write
	./test_read
	./test_list

../filesys.o: ../filesys.cpp ../filesys.h
	${CXX} ${CFLAGS} -c -o ../filesys.o ../filesys.cpp

../operations.o: ../operations.cpp ../filesys.h
	${CXX} ${CFLAGS} -c -o ../operations.o ../operations.cpp

test_format: test_format_launcher.cpp ${OBJS}
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_create: test_create_launcher.cpp ${OBJS}
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_simplelist: test_simplelist_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_list: test_list_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_delete: test_delete_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_rename: test_rename_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_copy: test_copy_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_open: test_open_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_close: test_close_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_write: test_write_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

test_read: test_read_launcher.cpp ${OBJS} 
	${CXX} ${CFLAGS} -o $@ ${OBJS} $<

%.o: %.cpp base_test.h
	${CXX} -c ${CFLAGS} -o $@ $<

.PHONY: clean

clean: 
	rm -f *.o *.img ${TESTS}
