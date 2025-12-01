# 🇧🇩 বাংলা প্রোগ্রামিং ভাষা (Bangla Programming Language)

A complete programming language with Bengali/Bangla syntax, supporting Bangla keywords, variable names, and digits. Write code entirely in your native language!

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language: Bangla](https://img.shields.io/badge/Language-Bangla-green.svg)](https://github.com/munyimJR/Bengali-Inspired-Programming-Language)
[![Node.js Version](https://img.shields.io/badge/node-%3E%3D16.0.0-brightgreen)](https://nodejs.org/)

## 🌟 Features

- ✅ **Pure Bangla Syntax** - Write code completely in Bangla
- ✅ **Bangla Variable Names** - Use `এ`, `বি`, `সংখ্যা` instead of `a`, `b`, `num`
- ✅ **Bangla Digits** - Support for `০১২৩৪৫৬৭৮৯`
- ✅ **AST-Based Interpreter** - Working loops with Abstract Syntax Tree execution
- ✅ **Web-Based IDE** - Beautiful online compiler with real-time execution
- ✅ **UTF-8 Support** - Full Unicode Bangla character support
- ✅ **Interactive Examples** - Built-in code examples to get started

## 🚀 Installation

### Prerequisites

- **Node.js** (v16 or higher)
- **npm** or **yarn**
- **flex** (Fast Lexical Analyzer)
- **bison** (Parser Generator)
- **gcc** (GNU C Compiler)

### Quick Start (Windows Users)

**For Windows users, we provide automated batch scripts:**

1. **Clone Repository:**
```bash
git clone https://github.com/munyimJR/Bengali-Inspired-Programming-Language.git
cd Bengali-Inspired-Programming-Language
```

2. **Run start.bat:**
```bash
start.bat
```

**What start.bat does:**
- ✅ Installs npm dependencies automatically
- ✅ Compiles scanner.l using Flex
- ✅ Compiles parser.y using Bison
- ✅ Compiles the C code using GCC
- ✅ Starts the backend server on port 3001
- ✅ Opens frontend in your default browser

3. **Stop the server (when needed):**
```bash
stop.bat
```

**What stop.bat does:**
- ✅ Finds Node.js process running on port 3001
- ✅ Stops the backend server gracefully

### Manual Installation Steps

#### 1. Install System Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install flex bison gcc make nodejs npm
```

**macOS:**
```bash
brew install flex bison gcc node
```

**Windows:**
- Install [Node.js](https://nodejs.org/)
- Install [MinGW-w64](https://www.mingw-w64.org/) for gcc, flex, bison
- Or use [WSL2](https://docs.microsoft.com/en-us/windows/wsl/install) with Ubuntu

#### 2. Clone Repository

```bash
git clone https://github.com/munyimJR/Bengali-Inspired-Programming-Language.git
cd Bengali-Inspired-Programming-Language
```

#### 3. Install Dependencies

```bash
cd backend
npm install
```

#### 4. Compile the Compiler

**Windows (using start.bat):**
```bash
start.bat
```

**Manual Compilation:**
```bash
cd backend
flex scanner.l
bison -d parser.y
gcc -o compiler lex.yy.c parser.tab.c -lm
```

#### 5. Start the Server

**Windows (Quick Start):**
```bash
# The start.bat script will:
# 1. Compile the compiler automatically
# 2. Install npm dependencies
# 3. Start the backend server
# 4. Open the frontend in your default browser

start.bat
```

**Manual Start:**
```bash
cd backend
node server.js
```

The server will run on `http://localhost:3001`

**To Stop (Windows):**
```bash
stop.bat
```

#### 6. Open Frontend

**If using start.bat:** The frontend will open automatically in your browser.

**Manual Open:**
- Simply open `frontend/index.html` in your browser, or
- Serve it using a local server:

```bash
# Using Python
cd frontend
python -m http.server 8080

# Using Node.js http-server
cd frontend
npx http-server -p 8080
```

Access at: `http://localhost:8080`

## ⚡ Quick Start

### Your First Bangla Program

```bangla
শুরু
    দেখাও << "হ্যালো, বাংলা প্রোগ্রামিং!" << নতুনলাইন;
শেষ
```

**Output:**
```
হ্যালো, বাংলা প্রোগ্রামিং!
```

### Variables and Arithmetic

```bangla
শুরু
    পূর্ণসংখ্যা এ = ১০, বি = ২০;
    পূর্ণসংখ্যা যোগফল = এ + বি;
    দেখাও << "যোগফল: " << যোগফল << নতুনলাইন;
শেষ
```

**Output:**
```
যোগফল: 30
```

## 📖 Language Syntax

### Keywords (কীওয়ার্ড)

| Bangla | English | Description |
|--------|---------|-------------|
| `শুরু` | start | Program start |
| `শেষ` | end | Program end |
| `পূর্ণসংখ্যা` | int | Integer type |
| `দশমিক` | float | Float type |
| `অক্ষর` | string | String type |
| `যদি` | if | If condition |
| `নাহলে` | else | Else condition |
| `যতক্ষণ` | while | While loop |
| `জন্য` | for | For loop |
| `দেখাও` | print | Output/Print |
| `নাও` | input | Input |
| `নতুনলাইন` | newline | New line |

### Data Types (ডেটা টাইপ)

#### Integer (পূর্ণসংখ্যা)
```bangla
পূর্ণসংখ্যা সংখ্যা = ১০;
পূর্ণসংখ্যা এ = ৫, বি = ১৫;
```

#### Float (দশমিক)
```bangla
দশমিক মূল্য = ৯৯.৯৯;
দশমিক পাই = ৩.১৪১৫৯;
```

#### String (অক্ষর)
```bangla
অক্ষর নাম = "রহিম";
অক্ষর বার্তা = "স্বাগতম!";
```

### Operators (অপারেটর)

| Operator | Description | Example |
|----------|-------------|---------|
| `+` | Addition | `এ + বি` |
| `-` | Subtraction | `এ - বি` |
| `*` | Multiplication | `এ * বি` |
| `/` | Division | `এ / বি` |
| `=` | Assignment | `এ = ১০` |
| `==` | Equal to | `এ == বি` |
| `!=` | Not equal | `এ != বি` |
| `<` | Less than | `এ < বি` |
| `>` | Greater than | `এ > বি` |
| `<=` | Less or equal | `এ <= বি` |
| `>=` | Greater or equal | `এ >= বি` |
| `&&` | Logical AND | `(এ > 0) && (বি > 0)` |
| `||` | Logical OR | `(এ > 0) || (বি > 0)` |
| `++` | Increment | `এ++` |
| `--` | Decrement | `এ--` |
| `+=` | Add assign | `এ += ৫` |
| `-=` | Subtract assign | `এ -= ৫` |
| `*=` | Multiply assign | `এ *= ২` |
| `/=` | Divide assign | `এ /= ২` |
| `<<` | Output operator | `দেখাও << "text"` |
| `>>` | Input operator | `নাও >> variable` |

### Bangla Digits (বাংলা সংখ্যা)

Both English and Bangla digits are supported:

| Bangla | English |
|--------|---------|
| ০ | 0 |
| ১ | 1 |
| ২ | 2 |
| ৩ | 3 |
| ৪ | 4 |
| ৫ | 5 |
| ৬ | 6 |
| ৭ | 7 |
| ৮ | 8 |
| ৯ | 9 |

### Input/Output (ইনপুট/আউটপুট)

#### Output
```bangla
দেখাও << "Hello" << নতুনলাইন;
দেখাও << "সংখ্যা: " << ৫০ << নতুনলাইন;
```

#### Input
```bangla
পূর্ণসংখ্যা বয়স;
দেখাও << "আপনার বয়স লিখুন: ";
নাও >> বয়স;
দেখাও << "আপনার বয়স: " << বয়স << নতুনলাইন;
```

### Control Flow (নিয়ন্ত্রণ প্রবাহ)

#### If-Else Statement
```bangla
যদি (সংখ্যা > ১০) {
    দেখাও << "বড় সংখ্যা" << নতুনলাইন;
} নাহলে {
    দেখাও << "ছোট সংখ্যা" << নতুনলাইন;
}
```

#### While Loop
```bangla
পূর্ণসংখ্যা i = ১;
যতক্ষণ (i <= ৫) {
    দেখাও << "লাইন: " << i << নতুনলাইন;
    i++;
}
```

#### For Loop
```bangla
পূর্ণসংখ্যা i;
জন্য (i = ১; i <= ১০; i++) {
    দেখাও << i << নতুনলাইন;
}
```

## 💡 Examples

### Example 1: Hello World
```bangla
শুরু
    দেখাও << "হ্যালো, বিশ্ব!" << নতুনলাইন;
শেষ
```

### Example 2: Calculator
```bangla
শুরু
    পূর্ণসংখ্যা প্রথম = ২৫, দ্বিতীয় = ১৫;
    
    দেখাও << "যোগফল: " << (প্রথম + দ্বিতীয়) << নতুনলাইন;
    দেখাও << "বিয়োগফল: " << (প্রথম - দ্বিতীয়) << নতুনলাইন;
    দেখাও << "গুণফল: " << (প্রথম * দ্বিতীয়) << নতুনলাইন;
শেষ
```

### Example 3: Factorial
```bangla
শুরু
    পূর্ণসংখ্যা সংখ্যা = ৫;
    পূর্ণসংখ্যা ফ্যাক্টরিয়াল = ১;
    পূর্ণসংখ্যা i;
    
    জন্য (i = ১; i <= সংখ্যা; i++) {
        ফ্যাক্টরিয়াল = ফ্যাক্টরিয়াল * i;
    }
    
    দেখাও << সংখ্যা << " এর ফ্যাক্টরিয়াল: " << ফ্যাক্টরিয়াল << নতুনলাইন;
শেষ
```

**Output:** `5 এর ফ্যাক্টরিয়াল: 120`

### Example 4: User Input
```bangla
শুরু
    অক্ষর নাম;
    পূর্ণসংখ্যা বয়স;
    
    দেখাও << "আপনার নাম লিখুন: ";
    নাও >> নাম;
    
    দেখাও << "আপনার বয়স লিখুন: ";
    নাও >> বয়স;
    
    দেখাও << "হ্যালো " << নাম << ", আপনার বয়স " << বয়স << নতুনলাইন;
শেষ
```

### Example 5: Sum of First N Numbers
```bangla
শুরু
    পূর্ণসংখ্যা n = ১০;
    পূর্ণসংখ্যা যোগফল = ০;
    পূর্ণসংখ্যা i;
    
    জন্য (i = ১; i <= n; i++) {
        যোগফল += i;
    }
    
    দেখাও << "প্রথম " << n << " সংখ্যার যোগফল: " << যোগফল << নতুনলাইন;
শেষ
```

**Output:** `প্রথম 10 সংখ্যার যোগফল: 55`

### Example 6: Multiplication Table
```bangla
শুরু
    পূর্ণসংখ্যা সংখ্যা = ৫;
    পূর্ণসংখ্যা i;
    
    দেখাও << সংখ্যা << " এর গুণিতক সারণি:" << নতুনলাইন;
    
    জন্য (i = ১; i <= ১০; i++) {
        দেখাও << সংখ্যা << " x " << i << " = " << (সংখ্যা * i) << নতুনলাইন;
    }
শেষ
```

## 📁 Project Structure

```
Bengali-Inspired-Programming-Language/
├── backend/
│   ├── server.js           # Express server
│   ├── scanner.l           # Flex lexer with Bangla digit support
│   ├── parser.y            # Bison parser with AST implementation
│   ├── package.json        # Node.js dependencies
│   ├── Dockerfile          # Backend Docker config
│   └── temp/               # Temporary compilation files (auto-created)
├── frontend/
│   ├── index.html          # Web interface
|   ├── style.css           # Styling 
|   ├── script.js           # IDE interface
│   ├── Dockerfile          # Frontend Docker config
│   └── nginx.conf          # Nginx configuration (optional)
├── docker-compose.yml      # Docker Compose setup
├── start.bat               # Windows startup script
├── stop.bat                # Windows stop script
├── README.md               # This file
└── LICENSE                 # MIT License
```

## 🏗️ Architecture

### Compiler Pipeline

1. **Lexical Analysis (scanner.l)**
   - Tokenizes Bangla keywords
   - Converts Bangla digits (০-৯) to ASCII
   - Handles UTF-8 encoding

2. **Parsing (parser.y)**
   - Builds Abstract Syntax Tree (AST)
   - Supports all language constructs
   - Implements two-phase execution

3. **Execution**
   - AST-based interpreter
   - Properly handles loops (for/while)
   - Manages symbol table for variables

4. **Output**
   - UTF-8 encoded output
   - Supports Bangla text in strings
   - Real-time compilation results

## 🛠️ Development

### Running Locally

```bash
# Navigate to backend
cd backend

# Compile the compiler
flex scanner.l
bison -d parser.y
gcc -o compiler lex.yy.c parser.tab.c -lm

# Start backend
node server.js

# In another terminal, open frontend
cd frontend
# Open index.html in browser or use a local server
python -m http.server 8080
```

### Testing Manually

Create a test file in `backend/test.txt`:
```bangla
শুরু
    পূর্ণসংখ্যা এ = ১০;
    দেখাও << "মান: " << এ << নতুনলাইন;
শেষ
```

Run:
```bash
cd backend
./compiler test.txt
```

### Modifying the Language

1. **Add Keywords**: Edit `backend/scanner.l` to add new Bangla keywords
2. **Add Grammar Rules**: Edit `backend/parser.y` to add new language constructs
3. **Recompile**: 
   ```bash
   cd backend
   flex scanner.l
   bison -d parser.y
   gcc -o compiler lex.yy.c parser.tab.c -lm
   ```
4. **Restart Server**: Stop and restart `node server.js`

## 🐳 Docker Deployment

### Using Docker Compose (Recommended)

```bash
# Build and start all services
docker-compose up --build

# Run in background
docker-compose up -d --build

# Stop services
docker-compose down
```

**Access:**
- Frontend: `http://localhost:8080`
- Backend: `http://localhost:3001`

### Manual Docker Build

**Backend:**
```bash
cd backend
docker build -t bangla-compiler-backend .
docker run -p 3001:3001 bangla-compiler-backend
```

**Frontend:**
```bash
cd frontend
docker build -t bangla-compiler-frontend .
docker run -p 8080:80 bangla-compiler-frontend
```

## 🚀 Deployment

### Deploy Backend (Heroku)

1. Navigate to backend directory:
```bash
cd backend
```

2. Create `Procfile`:
```
web: node server.js
```

3. Create `Aptfile`:
```
flex
bison
gcc
make
```

4. Deploy:
```bash
heroku create your-app-name
heroku buildpacks:add --index 1 heroku-community/apt
heroku buildpacks:add heroku/nodejs
git push heroku main
```

### Deploy Frontend (Netlify/Vercel)

1. Update `API_URL` in `frontend/index.html` to your Heroku backend URL
2. Deploy `frontend/` directory to Netlify or Vercel
3. Done! 🎉

## 🐛 Troubleshooting

### Common Issues

**Error: "flex: command not found"**
```bash
# Ubuntu/Debian
sudo apt-get install flex bison gcc

# macOS
brew install flex bison gcc
```

**Error: "Undeclared variable"**
- Declare variables before using: `পূর্ণসংখ্যা x = 5;`
- Check spelling of variable names

**Error: "Cannot use keyword as variable name"**
- Don't use keywords like `শুরু`, `শেষ` as variable names
- Use different names like `x`, `সংখ্যা`, `মান`

**Error: "Comma-separated declarations not working"**
- Make sure you're using the latest parser.y (AST-based)
- Recompile after updating parser

**Loops only execute once**
- Verify you're using the AST-based parser
- Check loop condition syntax

**String input shows 0 or empty**
- Use `অক্ষর` type for strings
- Make sure input is on separate line

**Port already in use**
```bash
# Linux/macOS
lsof -ti:3001 | xargs kill -9

# Windows
netstat -ano | findstr :3001
taskkill /PID <PID> /F
```

## 📚 API Reference

### Endpoints

#### Health Check
```
GET /api/health
Response: { "status": "ok", "message": "Bangla Compiler API is running" }
```

#### Get Examples
```
GET /api/examples
Response: [
  { "id": 1, "title": "Hello World", "code": "..." },
  ...
]
```

#### Compile Code
```
POST /api/compile
Body: {
  "code": "শুরু\n    দেখাও << \"Hello\" << নতুনলাইন;\nশেষ",
  "input": "optional input data"
}
Response: {
  "success": true,
  "output": "Hello\n[Program completed successfully]",
  "error": ""
}
```

## 🤝 Contributing

Contributions are welcome! Here's how:

1. **Fork** the repository
2. **Create** a feature branch: `git checkout -b feature/amazing-feature`
3. **Commit** your changes: `git commit -m 'Add amazing feature'`
4. **Push** to branch: `git push origin feature/amazing-feature`
5. **Open** a Pull Request

### Areas to Contribute

- 🐛 Bug fixes
- ✨ New language features (functions, arrays)
- 📖 Documentation improvements
- 🎨 UI/UX enhancements
- 🧪 Test coverage
- 🌐 More examples
- 📱 Mobile app version

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**munyimJR**
- GitHub: [@munyimJR](https://github.com/munyimJR)
- Repository: [Bengali-Inspired-Programming-Language](https://github.com/munyimJR/Bengali-Inspired-Programming-Language)

## 🙏 Acknowledgments

- Built with Flex, Bison, Node.js, and Express
- Inspired by the need for native language programming
- Thanks to all contributors and the Bangla programming community

## 📞 Support

⭐ **Star this repository** if you find it useful!

For questions or issues:
- 📝 Open an [Issue](https://github.com/munyimJR/Bengali-Inspired-Programming-Language/issues)
- 💬 Start a [Discussion](https://github.com/munyimJR/Bengali-Inspired-Programming-Language/discussions)

## 🗺️ Roadmap

- [ ] Function support (`ফাংশন`)
- [ ] Array data type (`তালিকা`)
- [ ] Comments (`//` and `/* */`)
- [ ] Modulo operator (`%`)
- [ ] Break and Continue statements
- [ ] Switch-case statement
- [ ] String concatenation improvements
- [ ] File I/O operations
- [ ] Standard library functions
- [ ] VS Code extension
- [ ] Syntax highlighting
- [ ] Code auto-completion
- [ ] Debugging support
- [ ] Mobile app
- [ ] Package manager

---

<div align="center">

**Made with ❤️ for the Bangla programming community**

🇧🇩 **বাংলায় কোড লিখুন, বাংলায় চিন্তা করুন!**

[⭐ Star](https://github.com/munyimJR/Bengali-Inspired-Programming-Language) · [🐛 Report Bug](https://github.com/munyimJR/Bengali-Inspired-Programming-Language/issues) · [✨ Request Feature](https://github.com/munyimJR/Bengali-Inspired-Programming-Language/issues)

</div>