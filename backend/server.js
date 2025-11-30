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
                    error: 'Compilation Error',
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
                        error: 'Timeout',
                        output: 'Program execution timed out (5 seconds limit)'
                    });
                }

                if (runError) {
                    return res.json({
                        success: false,
                        error: 'Runtime Error',
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
            error: 'Server Error',
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
    res.json({ status: 'ok', message: 'Bangla Compiler API is running' });
});

// Example codes endpoint
app.get('/api/examples', (req, res) => {
    const examples = [
        {
            id: 1,
            title: 'Hello World',
            code: `শুরু
    দেখাও << "Hello, Bangla Programming!" << নতুনলাইন;
শেষ`
        },
        {
            id: 2,
            title: 'Variables and Math',
            code: `শুরু
    পূর্ণসংখ্যা a = 10, b = 20;
    পূর্ণসংখ্যা sum = a + b;
    দেখাও << "Sum: " << sum << নতুনলাইন;
শেষ`
        },
        {
            id: 3,
            title: 'Bangla Digits Support',
            code: `শুরু
    পূর্ণসংখ্যা x = ১১, y = ২৫;
    পূর্ণসংখ্যা result = x + y;
    দেখাও << "১১ + ২৫ = " << result << নতুনলাইন;
    দেখাও << "বাংলা সংখ্যা কাজ করছে!" << নতুনলাইন;
শেষ`
        },
        {
            id: 4,
            title: 'If-Else Statement',
            code: `শুরু
    পূর্ণসংখ্যা num = 15;
    যদি (num > 10) {
        দেখাও << "Number is greater than 10" << নতুনলাইন;
    } নাহলে {
        দেখাও << "Number is less than or equal to 10" << নতুনলাইন;
    }
শেষ`
        },
        {
            id: 5,
            title: 'Loop Example',
            code: `শুরু
    পূর্ণসংখ্যা i;
    জন্য (i = 1; i <= 5; i++) {
        দেখাও << "Count: " << i << নতুনলাইন;
    }
শেষ`
        },
        {
            id: 6,
            title: 'User Input (Bangla Digits)',
            code: `শুরু
    পূর্ণসংখ্যা num;
    দেখাও << "একটি সংখ্যা লিখুন: ";
    নাও >> num;
    দেখাও << "আপনি লিখেছেন: " << num << নতুনলাইন;
শেষ`
        }
    ];
    res.json(examples);
});

app.listen(PORT, () => {
    console.log(`Bangla Compiler Server running on port ${PORT}`);
    console.log(`UTF-8 encoding enabled for Bangla input support`);
});