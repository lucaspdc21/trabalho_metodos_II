# Usa uma imagem do Node.js
FROM node:18-alpine

# Define o diretório de trabalho
WORKDIR /app

# Copia os arquivos do frontend para dentro do container
COPY . .

# Instala as dependências e compila o projeto
RUN npm install && npm run build

# Instala um servidor HTTP para servir os arquivos estáticos
RUN npm install -g serve

# Expõe a porta do frontend
EXPOSE 3000

# Comando para rodar o servidor
CMD ["serve", "-s", "dist"]
