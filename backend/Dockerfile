FROM node:18-bullseye

RUN apt-get update && apt-get install -y \
    flex \
    bison \
    gcc \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY package*.json ./
RUN npm install

COPY . .

RUN mkdir -p temp

EXPOSE 3001

CMD ["npm", "start"]
