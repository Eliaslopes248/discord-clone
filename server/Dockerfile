# NODE/LINUX IMAGE
FROM node:alpine

# CREATE /app DIR
WORKDIR /app

# COPY ALL MODULES TO /app
COPY package-*.json .

# COPY ALL FILES
COPY . .

# INSTALL MODULES
RUN npm install 

# RUN CONTAINER
CMD [ "node", "start.js" ]
