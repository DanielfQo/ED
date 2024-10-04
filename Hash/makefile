# Nombre del compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -Wall -std=c++11

# Archivos fuente
SRCS = main.cpp ListaEnlazada.h Hash.cpp 

# Archivos objeto
OBJS = $(SRCS:.cpp=.o)

# Nombre del ejecutable
TARGET = programa

# Regla por defecto
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Reglas de dependencias
main.o: main.cpp Hash.h
Hash.o: Hash.h ListaEnlazada.h
ListaEnlazada.o: ListaEnlazada.h

# Regla para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar archivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para limpiar todo
distclean: clean
	rm -f *~