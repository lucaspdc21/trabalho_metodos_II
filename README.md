## Pré-requisitos

Antes de rodar o projeto, certifique-se de ter os seguintes softwares instalados:
- **Compilador C++ compatível com C++11 ou superior**
- **Make** (para compilar o programa em C++)
- (Opcional, apenas se quiser rodar a interface web)
- **Docker e Docker Compose** (https://docs.docker.com/)

## Como Rodar o Projeto

### 1. Compilar e executar o programa

Na raiz do projeto, execute os seguintes comandos:

```sh
make  # Compila o programa
./main.o  # Executa o programa
```

### 2. Rodar a interface web com Docker

Após gerar o `resultado.json`, execute:

```sh
docker-compose up --build
```

Isso irá construir e rodar o frontend dentro de um container Docker.

## Notas Adicionais

- O frontend consome os dados do `resultado.json` gerado pelo backend em C++.
- Caso encontre erros de permissão ao rodar o `make`, tente:
  ```sh
  chmod +x main
  ```
- Para parar a execução do frontend, use `Ctrl + C` no terminal ou rode:
  ```sh
  docker-compose down
  ```

