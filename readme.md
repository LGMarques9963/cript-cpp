# 🔐 Cracking Codes with C++: Implementing "Cracking Codes with Python" in C++

## 📌 About This Project
This repository is a C++ implementation of the ciphers and cryptographic techniques described in *Cracking Codes with Python* by Al Sweigart. It serves as a portfolio demonstrating practical cryptographic skills for a cybersecurity role.

Each cipher algorithm is implemented in modern C++ (C++23), with a focus on clean code, efficiency, and readability.

## 🚀 Features
✅ Implementations of classic ciphers in C++<br>
✅ Modern C++ (C++23) with clean code and efficient algorithms<br>
✅ Code structure following best practices<br>
✅ Educational resources for cryptographic techniques<br>
✅ Demonstrations of encryption, decryption, and brute-force hacking<br>
✅ Unit tests for each cipher implementation
---

## 🛠️ Implemented Ciphers
| Cipher Algorithm               | Description                                                                     |
|--------------------------------|---------------------------------------------------------------------------------|
| **Caesar Cipher**              | A simple substitution cipher that shifts characters by a fixed key              |
| **Transposition Cipher**       | A columnar transposition encryption algorithm                                   |
| **Reverse Cipher**             | A basic cipher that reverses the message                                        |
| **Affine Cipher**              | A more complex substitution cipher based on modular arithmetic                  |
| **Vigenère Cipher**            | A polyalphabetic substitution cipher using a keyword                            |
| **Simple Substitution Cipher** | A basic symmetric encryption using bitwise XOR                                  |
| **Public-Key Cryptography**    | A cryptographic system that uses a pair of keys (public & private)              |
| **One-Time Pad Cipher**        | An **unbreakable** cipher that uses a random key as long as the message itself. |
| **Breaking Ciphers**           | Implementing basic cryptanalysis techniques to break the above ciphers          |

---

## 🚀 Why This Project Matters
- **🔐 Cybersecurity & Cryptography**: Understanding cryptographic algorithms is a fundamental skill for security professionals.
- **⚡ C++ Proficiency**: This project demonstrates **efficient** and **optimized** implementations in **modern C++**.
- **🎯 Algorithmic Thinking**: Many of these ciphers require mathematical reasoning and modular arithmetic.
- **🌟 Cryptanalysis Practice**: Some implementations include **hacking functions** to attempt decryption without a known key.

---

## 📂 Project Structure
```
💾 Cpp-Ciphers
📚 README.md          # Documentation (this file)
📺 src
   📝 caesarCyph.h      # Caesar Cipher Header
   📝 caesarCyph.cpp    # Caesar Cipher Implementation
   📝 transposition.h   # Transposition Cipher Header
   📝 transposition.cpp # Transposition Cipher Implementation
   📝 main.cpp          # Entry Point for Testing Ciphers
   📝 utils.h           # Utility functions (e.g., string processing)
   📝 utils.cpp         # Implementation of utilities
📺 tests
   📝 test_caesar.cpp   # Unit tests for Caesar Cipher
   📝 test_transp.cpp   # Unit tests for Transposition Cipher
📃 CMakeLists.txt     # Build configuration
```

---

## ⚙️ Building and Running the Project
### **🔹 Prerequisites**
- C++23 Compiler (GCC 11+, Clang 14+, MSVC)
- CMake (for easy compilation)
- Git (for version control)

### **🔹 Build Instructions**
```bash
# Clone the repository
git clone https://github.com/LGMarques9963/cript-cpp.git
cd cpp-ciphers

# Create a build directory
mkdir build && cd build

# Run CMake to generate Makefiles
cmake ..

# Compile the project
make

# Run the program
./cript
```

---

## 🛡️ Cybersecurity Relevance
Each cipher implementation includes **basic cryptanalysis techniques**, such as:
- **Brute-force attacks** (e.g., cracking the Caesar Cipher)
- **Frequency analysis** (e.g., breaking simple substitution ciphers)
- **Known-plaintext attacks** (e.g., cracking transposition ciphers)
- **Pattern recognition in encryption schemes**
- **Detecting English text in a message**

These skills are essential in fields such as:
- **Red Teaming / Penetration Testing**
- **Reverse Engineering**
- **Cryptanalysis & Cryptographic Security**
- **CTF (Capture The Flag) Challenges**

---

## 🧠 Testing the Implementations
Unit tests are included to ensure correctness of each cipher.

To run tests:
```bash
cd build
ctest --verbose
```

---

## 🌌 Future Enhancements
✔️ Implement more **ciphers** (Hill Cipher, Playfair, RSA, etc.)<br> 
✔️ Implement **multithreaded brute-force attacks** for efficiency<br>
✔️ Create **interactive CLI and GUI tools** for encrypting messages

---

## 📄 Credits & Resources
- **Book**: *Cracking Codes with Python* by Al Sweigart [(NoStarch Press)](https://nostarch.com/crackingcodes)
- **C++ Documentation**: [cppreference.com](https://en.cppreference.com/)
---

## 🤝 Contributing
If you're interested in contributing:
- Open an issue for bugs or feature requests.
- Fork the repository and submit a pull request.
- Improve documentation and test cases.

---

## 🔒 Disclaimer
This repository is intended **for educational purposes only**.  
**Do not use these implementations for real-world cryptographic security!**  
Always use **strong encryption standards** such as **AES, RSA, and ECC** for securing sensitive information.

---

## 💌 Contact
**📌 Author:** Lorran Marques<br>
**🌐 LinkedIn:** [Lorran Marques](https://www.linkedin.com/in/lgmarques/)  
**🔍 GitHub:** [LGMarques9963](https://github.com/LGMarques9963)  
**📧 Email:** lorran9963@gmail.com

---

### **🔐 Secure the Code. Understand the Math. Hack the Ciphers. 🚀**

---
🌟 *If you find this project helpful, consider giving it a ⭐ on GitHub!*

