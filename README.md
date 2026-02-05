# 🔧 MIL Compiler

> A high-performance compiler for the MIL (Minimal Intermediate Language) programming language, written in C++20.

[![C++](https://img.shields.io/badge/C%2B%2B-20-blue?logo=cplusplus)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.10%2B-064687?logo=cmake)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

## 📋 Requirements

| Tool | Version | Purpose |
|------|---------|---------|
| **CMake** | 3.10+ | Build configuration |
| **C++ Compiler** | C++20 | Compilation (GCC 7.0+, Clang 5.0+, or MSVC 2017+) |
| **Make** | Any | Build execution (Linux) |
| **NASM** | Any | Assembly to machine code |
| **GoLink** | Any | Linker (Windows, for generated objects) |

### ⚙️ Installation

<details>
<summary><b>Ubuntu/Debian</b></summary>

```bash
sudo apt-get install cmake build-essential nasm
```
</details>

<details>
<summary><b>Windows</b></summary>

1. Download and install [CMake](https://cmake.org/download/)
2. Download and install [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/)
3. Download and install [NASM](https://www.nasm.us/)
4. Download **GoLink** (linker) and add it to your `PATH`

   - Download: https://www.godevtool.com/GolinkHelp/ (make sure you can locate `golink.exe`)
   - Add the folder containing `golink.exe` to your user or system `PATH`
   - Verify in **PowerShell**:

     ```powershell
     golink /?
     ```
</details>

## 🚀 Quick Start

### Build Instructions

#### Linux (Ubuntu/Debian)

```bash
# Clone the repository
git clone <repository-url> && cd MIL

# Create and enter build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make
```

#### Windows (PowerShell)

Run from a **Developer PowerShell for VS** (or any shell where MSVC is available):

```powershell
# Clone the repository
git clone <repository-url>
cd MIL

# Configure + build (multi-config generators like Visual Studio)
cmake -S . -B build
cmake --build build --config Release
```

The compiled executable will be generated in `build/` (on Windows with Visual Studio generators it is typically under `build/Release/`).

## 💻 Usage

Run the compiler with a MIL source file:

```bash
./compiler <path-to-file.mil>
```

On Windows (PowerShell):

```powershell
.\compiler.exe <path-to-file.mil>
```

### Example:
```bash
./compiler ../dummy.mil
```

The compiler will parse your MIL code and generate assembly output.

## ✅ How To Test (Current Project Stage)

At the current stage, the simplest way to validate behavior is:

1. Run the compiled program.
2. Check the process **exit code** (0 usually means success; non-zero means an error occurred).

### Linux

```bash
./compiler ../dummy.mil
echo $?
```

### Windows (PowerShell)

```powershell
.\compiler.exe ..\dummy.mil
$LASTEXITCODE
```

## 📁 Project Structure

```
MIL/
├── 📄 main.cpp              # Entry point
├── 📂 src/
│   ├── scanner.cpp          # Lexical analyzer (tokenization)
│   └── parser.cpp           # Syntax analyzer (AST generation)
├── 📂 include/
│   ├── scanner.h            # Scanner interface
│   ├── parser.h             # Parser interface
│   └── ast.h                # AST definitions
├── 📂 docs/                 # Documentation
├── 📋 CMakeLists.txt        # Build configuration
├── 🧪 dummy.mil             # Example input file
└── 📝 README.md             # This file
```

## ✨ Features

- **Lexical Analysis** - Tokenizes MIL source code
- **Syntax Analysis** - Builds an Abstract Syntax Tree (AST)
- **Code Generation** - Generates x86-64 assembly output

## 🔨 Build Configurations

### Debug Build
```bash
mkdir cmake-build-debug && cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

### Release Build (Optimized)
```bash
mkdir cmake-build-release && cd cmake-build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## 🧹 Clean Build Artifacts

```bash
rm -rf build/ cmake-build-debug/ cmake-build-release/
```

## 📝 Input File Requirements

- Files must use the `.mil` extension
- Must conform to MIL language syntax (see `docs/grammar.md`)

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| `CMake not found` | Ensure CMake is installed and in your system PATH |
| `Compiler not found` | Install a C++17 compatible compiler (GCC, Clang, or MSVC) |
| `Build fails` | Try a clean rebuild: `rm -rf build/ && mkdir build && cd build && cmake .. && make` |

## 📚 Documentation

Learn more about the MIL language:
- [Grammar](docs/grammar.md) - Language syntax rules
- [Keywords](docs/keywords.txt) - Reserved keywords
- [Regex Patterns](docs/regex.md) - Pattern definitions
- [Alphabet](docs/alphabet.txt) - Character set

## 📜 License

This project is provided as-is for educational and personal use.

## 👤 Author

**Ahmed** - Student Developer

Feel free to use, modify, and learn from this project!