# Makefile para o projeto tarefas

# Comando padrão para compilar e gerar o executável (make)
all: check_dependencies clean build run

# Comando para verificar dependências antes de compilar
check_dependencies:
	@echo "Verificando permissões do script de verificação..."
	@chmod +x dependencies.sh
	@./dependencies.sh || (echo "Erro: Verifique as dependências necessárias." && exit 1)

# Comando para configurar e compilar o projeto com CMake (make build)
build:
	@echo "Construindo pastas e arquivos..."
	mkdir -p build bin && cd build && cmake .. && make && cp main ../bin/main && chmod +x ../bin/main

# Comando para executar o projeto (make run)
run:
	@echo "Executando..."
	@ls -l bin/
	cd bin && ./main

# Comando para limpar os arquivos gerados pelo CMake e pelo Make (make clean)
clean:
	@echo "Destruindo pastas e arquivos..."
	rm -rf build bin
	cd imgs && rm -f *.png

.PHONY: all check_dependencies clean build run