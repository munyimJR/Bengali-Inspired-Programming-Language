# Bangla Programming Language - Online Compiler

A full-stack web application for compiling and running Bangla programming language code online with pure HTML/CSS/JavaScript frontend.

## 🚀 Features

- ✨ Beautiful, modern IDE interface
- 🔥 Real-time code compilation and execution
- 📝 Code examples library
- 💾 Download and copy code functionality
- 🎨 Clean, responsive design
- 📱 Mobile-friendly interface
- ⚡ Pure HTML/CSS/JavaScript (no framework dependencies)

## 📋 Prerequisites

### Backend Requirements
- Node.js (v16 or higher)
- npm or yarn
- flex (lexical analyzer)
- bison (parser generator)
- gcc (C compiler)

### Frontend Requirements
- Any modern web browser
- Web server (optional, can open HTML file directly)

## 🛠️ Installation

### Backend Setup

1. **Install system dependencies** (Ubuntu/Debian):
```bash
sudo apt-get update
sudo apt-get install flex bison gcc make
```

For macOS:
```bash
brew install flex bison gcc
```

2. **Create backend directory and setup files**:
```bash
mkdir bangla-compiler-backend
cd bangla-compiler-backend
```

3. **Copy the required files**:
- Place `server.js` in the backend directory
- Place `package.json` in the backend directory
- Copy your `scanner.l` file to the backend directory
- Copy your `parser.y` file to the backend directory

4. **Install Node.js dependencies**:
```bash
npm install
```

5. **Start the backend server**:
```bash
npm start
```

The backend will run on `http://localhost:3001`

### Frontend Setup

**Option 1: Direct File Opening (Simple)**
1. Save the HTML file as `index.html`
2. Open it directly in your browser
3. Make sure backend is running on `http://localhost:3001`

**Option 2: Using a Local Web Server (Recommended)**

**Using Python:**
```bash
# Python 3
python -m http.server 8000

# Python 2
python -m SimpleHTTPServer 8000
```

**Using Node.js (http-server):**
```bash
npm install -g http-server
http-server -p 8000
```

**Using PHP:**
```bash
php -S localhost:8000
```

Then open `http://localhost:8000` in your browser.

**Option 3: Using Live Server (VS Code)**
1. Install "Live Server" extension in VS Code
2. Right-click on `index.html`
3. Select "Open with Live Server"

## 📁 Project Structure

```
bangla-compiler/
├── backend/
│   ├── server.js
│   ├── package.json
│   ├── scanner.l
│   ├── parser.y
│   ├── .env (optional)
│   ├── Dockerfile (optional)
│   └── temp/ (auto-created)
│
└── frontend/
    └── index.html (complete standalone file)
```

## 🎯 Usage

1. **Start the backend server:**
   ```bash
   cd backend
   npm start
   ```

2. **Open the frontend:**
   - Double-click `index.html` OR
   - Serve it using a local web server
   - Navigate to `http://localhost:8000` (if using web server)

3. **Write or select example Bangla code**

4. **(Optional) Provide input in the input section**

5. **Click "Run Code" button**

6. **View output in the right panel**

## 🔧 Configuration

### Change Backend Port
Edit `server.js`:
```javascript
const PORT = process.env.PORT || 3001;
```

### Change API URL in Frontend
Edit `index.html` (line ~318):
```javascript
const API_URL = 'http://localhost:3001/api';
// Change to your backend URL
```

### CORS Configuration
If accessing from different domains, update `server.js`:
```javascript
app.use(cors({
    origin: ['http://localhost:8000', 'http://yourdomain.com']
}));
```

## 📝 Example Code

```bangla
শুরু
    পূর্ণসংখ্যা a = 10, b = 20;
    পূর্ণসংখ্যা sum = a + b;
    দেখাও << "Sum: " << sum << "\n";
শেষ
```

## 🐳 Docker Setup (Optional)

### Backend with Docker

1. **Create Dockerfile** in backend directory:
```dockerfile
FROM node:18-bullseye

RUN apt-get update && apt-get install -y flex bison gcc make

WORKDIR /usr/src/app
COPY package*.json ./
RUN npm install
COPY . .
RUN mkdir -p temp

EXPOSE 3001
CMD ["npm", "start"]
```

2. **Build and run:**
```bash
docker build -t bangla-compiler-backend .
docker run -p 3001:3001 bangla-compiler-backend
```

### Frontend with Docker (Nginx)

1. **Create Dockerfile** in frontend directory:
```dockerfile
FROM nginx:alpine
COPY index.html /usr/share/nginx/html/
EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
```

2. **Build and run:**
```bash
docker build -t bangla-compiler-frontend .
docker run -p 8080:80 bangla-compiler-frontend
```

## 🔒 Security Considerations

- Code execution is sandboxed with timeout limits (5 seconds)
- Temporary files are automatically cleaned up
- File size limits are enforced on backend
- CORS is configured for development
- Input validation on both client and server

## 🐛 Troubleshooting

### Backend Issues

**"flex: command not found"**
```bash
sudo apt-get install flex bison gcc
```

**"Cannot open file 'scanner.l'"**
- Ensure scanner.l and parser.y are in the backend directory
- Check file names match exactly (case-sensitive)

**Port already in use**
```bash
# Kill process on port 3001
lsof -ti:3001 | xargs kill -9
# Or change PORT in server.js
```

### Frontend Issues

**"Failed to connect to server"**
- Verify backend is running: `curl http://localhost:3001/api/health`
- Check browser console for CORS errors
- Ensure API_URL in HTML matches your backend URL

**CORS errors**
- Update CORS configuration in server.js
- Use same protocol (http/https) for both frontend and backend

**Examples not loading**
- Check backend is running
- Verify `/api/examples` endpoint works
- Check browser console for errors

### Compilation Errors

**"Syntax error in Bangla code"**
- Check for missing semicolons
- Verify keyword spelling (বাংলা characters)
- Ensure proper block structure with { }

**"Division by zero"**
- Check your arithmetic operations
- The compiler will catch this at runtime

## 📦 Deployment

### Backend Deployment (Heroku Example)

1. **Create `Procfile`:**
```
web: node server.js
```

2. **Add buildpack for C compiler:**
```bash
heroku buildpacks:add --index 1 heroku-community/apt
```

3. **Create `Aptfile`:**
```
flex
bison
gcc
make
```

4. **Deploy:**
```bash
git init
heroku create your-app-name
git add .
git commit -m "Initial commit"
git push heroku main
```

### Frontend Deployment

**GitHub Pages:**
1. Update API_URL to your backend URL
2. Push to GitHub repository
3. Enable GitHub Pages in repository settings

**Netlify:**
1. Update API_URL in index.html
2. Drag and drop index.html to Netlify
3. Or connect GitHub repository

**Vercel:**
```bash
npm install -g vercel
vercel
```

## 🌐 Environment Variables (Backend)

Create `.env` file in backend directory:
```env
PORT=3001
NODE_ENV=production
COMPILE_TIMEOUT=10000
EXECUTION_TIMEOUT=5000
```

## 📊 API Endpoints

### Health Check
```
GET /api/health
Response: { "status": "ok", "message": "..." }
```

### Get Examples
```
GET /api/examples
Response: [{ "id": 1, "title": "...", "code": "..." }, ...]
```

### Compile and Run
```
POST /api/compile
Body: { "code": "...", "input": "..." }
Response: { "success": true, "output": "...", "error": "..." }
```

## 🎨 Customization

### Change Color Scheme
Edit the CSS in `index.html`:
```css
/* Main gradient background */
background: linear-gradient(135deg, #0f172a 0%, #581c87 50%, #0f172a 100%);

/* Primary button colors */
background: linear-gradient(to right, #9333ea, #ec4899);
```

### Add More Examples
Edit `server.js` examples endpoint or modify the frontend to add static examples.

## 📄 License

MIT License

## 👨‍💻 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📧 Support

For issues and questions:
1. Check this README first
2. Review troubleshooting section
3. Open an issue on GitHub with:
   - Error message
   - Steps to reproduce
   - Environment details (OS, Node version, etc.)

## 🔄 Updates

To update the compiler:
1. Modify `scanner.l` or `parser.y`
2. Restart the backend server
3. The changes will be reflected immediately

## ⚡ Performance Tips

1. **Backend**: 
   - Run cleanup regularly
   - Monitor temp directory size
   - Use PM2 for production: `pm2 start server.js`

2. **Frontend**:
   - Minify HTML/CSS for production
   - Enable gzip compression on server
   - Use CDN for static assets

## 📚 Resources

- Flex Documentation: https://github.com/westes/flex
- Bison Documentation: https://www.gnu.org/software/bison/
- Node.js Documentation: https://nodejs.org/
- Express.js Guide: https://expressjs.com/"# Bengali-Inspired-Programming-Language" 
