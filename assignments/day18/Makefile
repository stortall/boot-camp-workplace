compiler = g++

main: main.cpp libshape.so
	$(compiler) main.cpp -o main.out -L. -l shape

libshape.so: 
	$(compiler) --shared -fPIC ../day5/shape.cpp -o libshape.so

clean:
	@echo -- Cleaning up folder
	rm -rf libshape.so main.out

# Remember to run this in terminal before run executable:
# export LD_LIBRARY_PATH=.