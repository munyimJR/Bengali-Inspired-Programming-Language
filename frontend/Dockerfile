FROM nginx:alpine

# Copy ALL frontend files (index.html, CSS, JS, images)
COPY . /usr/share/nginx/html/

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]
