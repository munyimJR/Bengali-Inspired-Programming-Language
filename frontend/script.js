const API_URL = 'http://localhost:3001/api';
        
        // Initialize
        document.addEventListener('DOMContentLoaded', () => {
            loadExamples();
            setDefaultCode();
        });

        function setDefaultCode() {
            const defaultCode = `শুরু
    দেখাও << "হ্যালো, বাংলা প্রোগ্রামিং!" << নতুনলাইন;
শেষ`;
            document.getElementById('codeEditor').value = defaultCode;
        }

        // Load examples from API
        async function loadExamples() {
            try {
                const response = await fetch(`${API_URL}/examples`);
                const examples = await response.json();
                
                const examplesList = document.getElementById('examplesList');
                examplesList.innerHTML = examples.map(example => `
                    <div class="example-item" onclick='loadExample(${JSON.stringify(example.code)})'>
                        <div class="example-title">${example.title}</div>
                        <div class="example-subtitle">Click to load</div>
                    </div>
                `).join('');
            } catch (error) {
                console.error('Failed to load examples:', error);
            }
        }

        // Switch between tabs
        function switchTab(tab) {
            const tabs = document.querySelectorAll('.tab');
            tabs.forEach(t => t.classList.remove('active'));
            
            if (tab === 'editor') {
                document.getElementById('editorPanel').classList.remove('hidden');
                document.getElementById('examplesPanel').classList.add('hidden');
                tabs[0].classList.add('active');
            } else {
                document.getElementById('editorPanel').classList.add('hidden');
                document.getElementById('examplesPanel').classList.remove('hidden');
                tabs[1].classList.add('active');
            }
        }

        // Load example code
        function loadExample(code) {
            document.getElementById('codeEditor').value = code;
            switchTab('editor');
        }

        // Copy code to clipboard
        function copyCode() {
            const code = document.getElementById('codeEditor').value;
            navigator.clipboard.writeText(code).then(() => {
                const btnText = document.getElementById('copyBtnText');
                btnText.textContent = 'Copied!';
                setTimeout(() => {
                    btnText.textContent = 'Copy';
                }, 2000);
            });
        }

        // Download code
        function downloadCode() {
            const code = document.getElementById('codeEditor').value;
            const blob = new Blob([code], { type: 'text/plain' });
            const url = URL.createObjectURL(blob);
            const a = document.createElement('a');
            a.href = url;
            a.download = 'code.txt';
            a.click();
            URL.revokeObjectURL(url);
        }

        // Run code
        async function runCode() {
            const code = document.getElementById('codeEditor').value;
            const input = document.getElementById('inputEditor').value;
            const runBtn = document.getElementById('runBtn');
            const runBtnText = document.getElementById('runBtnText');
            const outputContent = document.getElementById('outputContent');

            if (!code.trim()) {
                showError('Please enter some code to run');
                return;
            }

            // Show loading state
            runBtn.disabled = true;
            runBtnText.textContent = '⏳ চলছে...';
            outputContent.innerHTML = '<div class="output-placeholder"><p>কম্পাইল হচ্ছে...</p></div>';

            try {
                const response = await fetch(`${API_URL}/compile`, {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify({ code, input }),
                });

                const result = await response.json();

                if (result.success) {
                    showOutput(result.output, result.error);
                } else {
                    showError(result.output || result.error);
                }
            } catch (error) {
                showError('সার্ভারের সাথে সংযোগ ব্যর্থ হয়েছে। নিশ্চিত করুন যে backend port 3001-এ চলছে।');
            } finally {
                runBtn.disabled = false;
                runBtnText.textContent = '▶️ কোড চালান';
            }
}

        // Show output
        function showOutput(output, error) {
            const outputContent = document.getElementById('outputContent');
            let html = `<pre class="output-text">${escapeHtml(output)}</pre>`;
            
            if (error) {
                html += `
                    <div class="error-box" style="margin-top: 1rem;">
                        <div class="error-title">Warnings/Errors:</div>
                        <pre class="error-text">${escapeHtml(error)}</pre>
                    </div>
                `;
            }
            
            outputContent.innerHTML = html;
        }

        // Show error
        function showError(error) {
            const outputContent = document.getElementById('outputContent');
            outputContent.innerHTML = `
                <div class="error-box">
                    <div class="error-title">Error:</div>
                    <pre class="error-text">${escapeHtml(error)}</pre>
                </div>
            `;
        }

        // Escape HTML
        function escapeHtml(text) {
            const div = document.createElement('div');
            div.textContent = text;
            return div.innerHTML;
        }