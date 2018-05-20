CUDA_PREFIX=/usr/local/cuda
CXXFLAGS=`pkg-config --cflags dlib-1 opencv` -I. -std=c++14 -O2
LIBS=-Wl,-Bdynamic `pkg-config --libs opencv` -Wl,-Bstatic `pkg-config --libs dlib-1` -L${CUDA_PREFIX}/lib64 -lcudnn_static -lcusolver_static -lcublas_static -lcufft_static -lcurand_static -lcusparse_static -lculibos -lcudart_static -Wl,-Bdynamic -lcuda -lpthread -lrt -ldl -lgcc -lboost_program_options
OBJS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: detector

detector: FaceDetector.o main.o
	$(CXX) $^ $(LIBS) -o ${@}

clean:
	$(RM) detector $(OBJS)

