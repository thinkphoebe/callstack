all:
	gcc test_so.c -o libtest.so -g -ldl -shared -rdynamic -fpic
	gcc callstack.c test.c -o callstack -g -ldl -rdynamic -L. -ltest

clean:
	rm -vrf ./*.o ./*.so ./callstack
