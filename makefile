client:
	g++ -std=c++11 *.cpp main/client_main.cpp Fib2584/*.cpp table/*.cpp -o ai_client

stdio:
	g++ -std=c++11 *.cpp main/main.cpp Fib2584/*.cpp table/*.cpp -o ai_stdio
	
train:
	g++ -std=c++11 *.cpp main/train_main.cpp Fib2584/*.cpp table/*.cpp -o ai_train