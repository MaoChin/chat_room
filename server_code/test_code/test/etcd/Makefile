all:get put
get:get.cc
	g++ -o $@ $^ -std=c++17 -lcpprest -letcd-cpp-api

put:put.cc
	g++ -o $@ $^ -std=c++17 -lcpprest -letcd-cpp-api

.PHONE:clean
clean:
	rm -rf put get
