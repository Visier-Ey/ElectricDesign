FROM node:18-bullseye

WORKDIR /app
COPY package*.json ./
RUN npm install --production
COPY . .

EXPOSE 1883
CMD ["node", "app.js"]
