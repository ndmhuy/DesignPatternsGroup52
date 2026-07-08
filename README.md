# Design Patterns - Group 52

This repository contains the group assignment for the **CS202 - C++ Programming / Design Patterns** course, developed by Group 52. 

Our group is working on the following design patterns:
1. **Observer Pattern** (Presentation `.pptx` & Report LaTeX)
2. **Interpreter Pattern** (Report LaTeX)
3. **Mediator Pattern** (Report LaTeX)

---

## 👥 Student Information

* **Full Name:** Nguyễn Đình Minh Huy
* **Student ID:** 25125083
* **Class:** 25A01
* *(Note: Add details of other group members here)*

---

## 📂 Repository Structure

The project is structured as follows:

```text
.
├── README.md               # Project overview and instructions
├── AGENTS.md               # AI assistant context & developer guidelines
│
├── Observer/               # 👁️ Observer Pattern (Presentation + Report + Code)
│   ├── src/                # C++ source code files
│   │   ├── naive.cpp       # Naive/problematic implementation
│   │   ├── pattern.cpp     # Refactored design pattern implementation
│   │   └── main.cpp        # Driver code to compare naive vs pattern
│   ├── reports/            # LaTeX documentation
│   │   └── report.tex      # LaTeX template for the report
│   └── presentation/       # Presentation slides & material
│       └── README.md       # Guidelines and links for the presentation
│
├── Interpreter/            # 🗣️ Interpreter Pattern (Report + Code)
│   ├── src/                # C++ source code files
│   │   ├── naive.cpp       # Naive implementation
│   │   ├── pattern.cpp     # Refactored design pattern implementation
│   │   └── main.cpp        # Driver code
│   └── reports/            # LaTeX documentation
│       └── report.tex      # LaTeX template for the report
│
└── Mediator/               # 🤝 Mediator Pattern (Report + Code)
    ├── src/                # C++ source code files
    │   ├── naive.cpp       # Naive implementation
    │   ├── pattern.cpp     # Refactored design pattern implementation
    │   └── main.cpp        # Driver code
    └── reports/            # LaTeX documentation
        └── report.tex      # LaTeX template for the report
```

---

## 📋 Course Requirements (For Each Pattern)

For each design pattern, our submission (Code, Presentation, and LaTeX Report) must address the following points:

1. **Real-world Problem:** A concrete scenario/problem that requires the pattern to solve.
2. **Naive Solution:** A straightforward C++ implementation without using the pattern.
3. **Naive Solution Drawbacks:** Explanation of the issues, maintenance issues, scalability, or code coupling resulting from the naive solution.
4. **Design Pattern Introduction:** Definitions, intent, and concept of the pattern.
5. **General Class Diagram:** The standard structure/UML diagram of the pattern.
6. **Specific Class Diagram:** The UML diagram tailored to our real-world problem.
7. **Implementation:** C++ source code demonstrating the pattern.
8. **Pros & Cons:** The trade-offs when choosing to use this pattern.
9. **Other Real-world Applications:** How this pattern is used in modern web or mobile development.
10. **Quiz:** 5 to 8 multiple-choice questions (ABCD) with answers to interact with the audience (complete with a key).

---

## 🛠️ How to Build and Run the Code

Each pattern contains a C++ CMake setup or can be compiled directly using standard compilers.

### Prerequisites
* A C++ compiler supporting C++17 or later (e.g., `g++`, `clang++`)
* Make or CMake (optional, for build automation)
* A LaTeX distribution (e.g., MacTeX, TeX Live) to compile reports

### Compiling and Running (Observer Example)
To compile the C++ implementation for the Observer pattern manually:
```bash
# Navigate to the Observer source directory
cd Observer/src

# Compile the driver file along with implementation files
g++ -std=c++17 main.cpp naive.cpp pattern.cpp -o observer_demo

# Run the executable
./observer_demo
```

### Compiling LaTeX Reports
To compile the LaTeX report (e.g., using `pdflatex` or `latexmk`):
```bash
cd Observer/reports
pdflatex report.tex
```

---

## 📚 References

* Gamma, E., Helm, R., Johnson, R., & Vlissides, J. (1994). *Design Patterns: Elements of Reusable Object-Oriented Software*. Addison-Wesley.
* Refactoring.Guru. *Design Patterns*. https://refactoring.guru/design-patterns
* *Other references to be updated as the project progresses.*
