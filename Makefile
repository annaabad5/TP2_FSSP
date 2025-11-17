# Compilador
CXX = g++
# Flags de compilación: -g (debug), -std=c++17 (moderno), -Wall (warnings), -Iinclude (para encontrar los .hpp)
CXXFLAGS = -g -std=c++17 -Wall -Iinclude

# Directorios
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Busca todos los archivos .cpp en src/
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# Reemplaza 'src/%.cpp' por 'build/%.o' (archivos objeto)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# Nombre del ejecutable final
TARGET = $(BUILDDIR)/main

# Regla principal: compila todo
all: $(TARGET)

# Regla para crear el ejecutable final
$(TARGET): $(OBJS)
	@mkdir -p $(BUILDDIR) # Crea el directorio build si no existe
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Compilación exitosa! Ejecutable en: $(TARGET)"

# Regla para compilar un .cpp en un .o
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar
clean:
	@echo "Limpiando..."
	@rm -rf $(BUILDDIR)

.PHONY: all clean