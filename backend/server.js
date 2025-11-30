const express = require('express');
const cors = require('cors');
const { exec } = require('child_process');
const fs = require('fs').promises;
const path = require('path');
const { v4: uuidv4 } = require('uuid');

const app = express();
const PORT = process.env.PORT || 3001;

// Middleware with UTF-8 support
app.use(cors());
app.use(express.json({ charset: 'utf-8', limit: '10mb' }));
app.use(express.urlencoded({ extended: true, charset: 'utf-8' }));

// Set UTF-8 headers for all responses
app.use((req, res, next) => {
    res.setHeader('Content-Type', 'application/json; charset=utf-8');
    next();
});

// Temporary directory for compilation
const TEMP_DIR = path.join(__dirname, 'temp');

// Ensure temp directory exists
(async () => {
    try {
        await fs.mkdir(TEMP_DIR, { recursive: true });
    } catch (err) {
        console.error('Error creating temp directory:', err);
    }
})();

// Cleanup old files (older than 1 hour)
const cleanupOldFiles = async () => {
    try {
        const files = await fs.readdir(TEMP_DIR);
        const now = Date.now();
        const oneHour = 60 * 60 * 1000;

        for (const file of files) {
            const filePath = path.join(TEMP_DIR, file);
            const stats = await fs.stat(filePath);
            if (now - stats.mtimeMs > oneHour) {
                await fs.unlink(filePath);
            }
        }
    } catch (err) {
        console.error('Cleanup error:', err);
    }
};

// Run cleanup every 30 minutes
setInterval(cleanupOldFiles, 30 * 60 * 1000);

// Compile and run endpoint
app.post('/api/compile', async (req, res) => {
    const { code, input } = req.body;
    const sessionId = uuidv4();
    const sessionDir = path.join(TEMP_DIR, sessionId);

    try {
        // Create session directory
        await fs.mkdir(sessionDir, { recursive: true });

        const codeFile = path.join(sessionDir, 'code.txt');
        const inputFile = path.join(sessionDir, 'input.txt');
        const outputFile = path.join(sessionDir, 'output');
        const lexFile = path.join(sessionDir, 'scanner.l');
        const yaccFile = path.join(sessionDir, 'parser.y');

        // Write code and input files with UTF-8 encoding
        await fs.writeFile(codeFile, code, { encoding: 'utf8' });
        if (input) {
            await fs.writeFile(inputFile, input, { encoding: 'utf8' });
        }

        // Copy scanner.l and parser.y from parent directory
        await fs.copyFile(path.join(__dirname, 'scanner.l'), lexFile);
        await fs.copyFile(path.join(__dirname, 'parser.y'), yaccFile);

        // Detect OS and set appropriate commands
        const isWindows = process.platform === 'win32';
        const compilerOutput = isWindows ? 'compiler.exe' : 'compiler';
        const compilerRun = isWindows ? 'compiler.exe' : './compiler';

        // Compile the compiler with UTF-8 support
        const compileCommand = isWindows 
            ? `chcp 65001 > nul && cd ${sessionDir} && flex scanner.l && bison -d parser.y && gcc -o ${compilerOutput} lex.yy.c parser.tab.c -lm`
            : `cd ${sessionDir} && flex scanner.l && bison -d parser.y && gcc -o ${compilerOutput} lex.yy.c parser.tab.c -lm`;

        exec(compileCommand, { timeout: 10000, encoding: 'utf8' }, async (compileError, compileStdout, compileStderr) => {
            if (compileError) {
                await cleanup(sessionDir);
                return res.json({
                    success: false,
                    error: 'কম্পাইলেশন ত্রুটি',
                    output: compileStderr || compileError.message
                });
            }

            // Run the compiled program with UTF-8 environment
            const runCommand = isWindows
                ? (input 
                    ? `chcp 65001 > nul && cd ${sessionDir} && ${compilerRun} code.txt < input.txt`
                    : `chcp 65001 > nul && cd ${sessionDir} && ${compilerRun} code.txt`)
                : (input 
                    ? `cd ${sessionDir} && export LANG=en_US.UTF-8 && ${compilerRun} code.txt < input.txt`
                    : `cd ${sessionDir} && export LANG=en_US.UTF-8 && ${compilerRun} code.txt`);

            exec(runCommand, { 
                timeout: 5000, 
                encoding: 'utf8',
                env: { ...process.env, LANG: 'en_US.UTF-8', LC_ALL: 'en_US.UTF-8' }
            }, async (runError, runStdout, runStderr) => {
                await cleanup(sessionDir);

                if (runError && runError.killed) {
                    return res.json({
                        success: false,
                        error: 'টাইমআউট',
                        output: 'প্রোগ্রাম এক্সিকিউশন টাইমআউট (৫ সেকেন্ড সীমা)'
                    });
                }

                if (runError) {
                    return res.json({
                        success: false,
                        error: 'রানটাইম ত্রুটি',
                        output: runStderr || runError.message
                    });
                }

                res.json({
                    success: true,
                    output: runStdout,
                    error: runStderr || ''
                });
            });
        });

    } catch (err) {
        await cleanup(sessionDir);
        res.status(500).json({
            success: false,
            error: 'সার্ভার ত্রুটি',
            output: err.message
        });
    }
});

// Cleanup function
const cleanup = async (dir) => {
    try {
        const files = await fs.readdir(dir);
        for (const file of files) {
            await fs.unlink(path.join(dir, file));
        }
        await fs.rmdir(dir);
    } catch (err) {
        console.error('Cleanup error:', err);
    }
};

// Health check endpoint
app.get('/api/health', (req, res) => {
    res.json({ status: 'ok', message: 'বাংলা কম্পাইলার API চালু আছে' });
});

// Example codes endpoint
app.get('/api/examples', (req, res) => {
    const examples = [
        {
            id: 1,
            title: 'হ্যালো ওয়ার্ল্ড',
            code: `শুরু
    দেখাও << "হ্যালো, বাংলা প্রোগ্রামিং!" << নতুনলাইন;
শেষ`
        },
        {
            id: 2,
            title: 'ভেরিয়েবল এবং গণিত',
            code: `শুরু
    পূর্ণসংখ্যা এ = ১০, বি = ২০;
    পূর্ণসংখ্যা যোগফল = এ + বি;
    দেখাও << "যোগফল: " << যোগফল << নতুনলাইন;
শেষ`
        },
        {
            id: 3,
            title: 'বাংলা সংখ্যা সাপোর্ট',
            code: `শুরু
    পূর্ণসংখ্যা x = ১১, y = ২৫;
    পূর্ণসংখ্যা ফলাফল = x + y;
    দেখাও << "১১ + ২৫ = " << ফলাফল << নতুনলাইন;
    দেখাও << "বাংলা সংখ্যা কাজ করছে!" << নতুনলাইন;
শেষ`
        },
        {
            id: 4,
            title: 'যদি-নাহলে স্টেটমেন্ট',
            code: `শুরু
    পূর্ণসংখ্যা সংখ্যা = ১৫;
    যদি (সংখ্যা > ১০) {
        দেখাও << "সংখ্যা ১০ এর চেয়ে বড়" << নতুনলাইন;
    } নাহলে {
        দেখাও << "সংখ্যা ১০ এর চেয়ে ছোট বা সমান" << নতুনলাইন;
    }
শেষ`
        },
        {
            id: 5,
            title: 'লুপ উদাহরণ',
            code: `শুরু
    পূর্ণসংখ্যা i;
    জন্য (i = ১; i <= ৫; i++) {
        দেখাও << "গণনা: " << i << নতুনলাইন;
    }
শেষ`
        },
        {
            id: 6,
            title: 'ইউজার ইনপুট',
            code: `শুরু
    পূর্ণসংখ্যা সংখ্যা;
    দেখাও << "একটি সংখ্যা লিখুন: ";
    নাও >> সংখ্যা;
    দেখাও << "আপনি লিখেছেন: " << সংখ্যা << নতুনলাইন;
শেষ`
        },
        {
            id: 7,
            title: 'ফ্যাক্টরিয়াল',
            code: `শুরু
    পূর্ণসংখ্যা সংখ্যা = ৫;
    পূর্ণসংখ্যা ফ্যাক্টরিয়াল = ১;
    পূর্ণসংখ্যা i;
    
    জন্য (i = ১; i <= সংখ্যা; i++) {
        ফ্যাক্টরিয়াল = ফ্যাক্টরিয়াল * i;
    }
    
    দেখাও << সংখ্যা << " এর ফ্যাক্টরিয়াল: " << ফ্যাক্টরিয়াল << নতুনলাইন;
শেষ`
        },
        {
            id: 8,
            title: 'গুণিতক সারণি',
            code: `শুরু
    পূর্ণসংখ্যা সংখ্যা = ৫;
    পূর্ণসংখ্যা i;
    
    দেখাও << সংখ্যা << " এর গুণিতক সারণি:" << নতুনলাইন;
    
    জন্য (i = ১; i <= ১০; i++) {
        দেখাও << সংখ্যা << " x " << i << " = " << (সংখ্যা * i) << নতুনলাইন;
    }
শেষ`
        }
    ];
    res.json(examples);
});

app.listen(PORT, () => {
    console.log(`বাংলা কম্পাইলার সার্ভার পোর্ট ${PORT} এ চালু আছে`);
    console.log(`UTF-8 এনকোডিং সক্রিয় আছে বাংলা ইনপুট সাপোর্টের জন্য`);
});