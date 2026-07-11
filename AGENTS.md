# AI Developer Agent Guidelines (`AGENTS.md`)

Welcome, Agent! This file outlines the conventions, requirements, and commands you must follow when contributing to the **DesignPatternsGroup52** repository. 

Our group is developing C++ source code, LaTeX reports, and presentation guides for three design patterns: **Observer**, **Interpreter**, and **Mediator**.

---

## 🛠️ Environment & Tooling

* **Language:** C++17
* **Compilers supported:** `g++` (GCC), `clang++` (Clang)
* **LaTeX Engine:** `pdflatex` or `lualatex`
* **LaTeX Editor compatibility:** Overleaf, TeXworks, VS Code LaTeX Workshop

---

## 📂 Project Structure Conventions

Each design pattern must reside in its own folder (e.g., `Observer/`, `Interpreter/`, `Mediator/`) and adhere to the following structure:

1. `src/naive.cpp`: Implementation of the problem *without* the design pattern. Focus on coupling, hard dependencies, or code complexity that makes maintenance hard.
2. `src/pattern.cpp`: Refactored code utilizing the specific design pattern.
3. `src/main.cpp`: A driver that calls both the naive and pattern solutions to demonstrate the functional difference and compare output or maintenance/extension characteristics.
4. `reports/report.tex`: LaTeX source file for the pattern report.

---

## 📝 Coding Standards (C++)

* **Standard:** Standard library only (no external dependencies like Boost unless explicitly approved).
* **Naming Conventions:**
  - Class Names: `PascalCase` (e.g., `ConcreteObserver`, `Subject`)
  - Method and Variable Names: `camelCase` (e.g., `registerObserver`, `state`)
  - File Names: Lowercase with underscores if needed (e.g., `naive.cpp`)
* **Modularity:** Separate interface (abstract base classes) from concrete implementation where possible, although a single implementation file is acceptable for simple demo code.
* **Memory Management:** Use modern C++ memory management (e.g., `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`) instead of raw pointers (`new`/`delete`) to prevent leaks.

---

## 📄 LaTeX Report Standards

Reports must be structured using standard LaTeX article class. Ensure that each `report.tex` file contains:

1. **Title and Author Info:** Group 52, Nguyễn Đình Minh Huy, ID 25125083.
2. **Sections (Must align with course requirements):**
   - `\section{Real-world Problem}`: Background/context.
   - `\section{Naive Solution}`: Code snippets and description of the naive design.
   - `\section{Naive Solution Drawbacks}`: Discuss tight coupling, violation of SOLID principles (e.g., OCP, SRP).
   - `\section{Design Pattern Introduction}`: Standard Definition, Intent, Structure.
   - `\section{UML Class Diagrams}`: General pattern UML and problem-specific UML (embed images or use TikZ).
   - `\section{Pattern-Based Implementation}`: Code snippets of the refactored code.
   - `\section{Pros and Cons}`: Evaluation of trade-offs.
   - `\section{Modern Web & Mobile Applications}`: Real-world usages.
   - `\section{Interactive Quiz}`: 5-8 multiple-choice questions.
3. **Packages to Include:**
   - `listings` or `minted` for syntax highlighting of C++ code.
   - `graphicx` for importing class diagrams.
   - `hyperref` for clickable references.
   - `amsmath`/`amssymb` for formulas if necessary.

---

## 💻 Command Reference

Ensure all C++ code compiles with the `-Wall -Wextra -std=c++17` flags.

### Compile C++ Code (Example for Observer)
```bash
g++ -std=c++17 -Wall -Wextra Observer/src/main.cpp Observer/src/naive.cpp Observer/src/pattern.cpp -o Observer/src/observer_demo
```

### Run C++ Code
```bash
./Observer/src/observer_demo
```

### Compile LaTeX Report
```bash
pdflatex -output-directory=Observer/reports Observer/reports/report.tex
```

---

## 👥 Member Recognition & Private Knowledge System

To support seamless collaboration between Member A and Member B, agents must dynamically identify which developer is currently working and adapt to their specific custom preferences/orders using a dual system:

### 1. Dynamic Member Recognition
At the start of every session, the agent should run checks to identify the active developer:
- **Git User Check**: Retrieve the local git user configuration (`git config user.name`).
- **Profile Check**: Check if `.member_profile.json` exists at the workspace root.

### 2. Private Knowledge & Custom User Orders
Since all git-tracked files are shared, custom personal notes, reminders, or private user orders for the agent should be kept in a local, gitignored configuration file called `.member_profile.json` at the project root.

Each developer can create their own `.member_profile.json` locally. The agent must search for and read this file (if present) to load custom, member-specific orders.

#### Example `.member_profile.json` Schema:
```json
{
  "memberName": "A",
  "developerName": "Nguy\~{\^e}n \DJ\`inh Minh Huy",
  "privateNotes": "Any specific reminders or notes from the user that should not be shared via Git.",
  "agentCustomInstructions": [
    "Ensure LaTeX report compiles with pdflatex cleanly.",
    "Propose code changes that are standard-compliant."
  ]
}
```
If `.member_profile.json` is missing, the agent must gracefully fall back to git configuration detection or invite the developer to create this file.

---

## 🤖 Guidelines for AI Actions

* **Always preserve context:** Do not overwrite existing code or markdown files fully; use targeted replacement blocks.
* **Keep code compilable:** Before concluding a task, run a compilation check to ensure there are no syntax errors.
* **Keep LaTeX syntax valid:** Ensure all LaTeX blocks are closed properly, particularly `\begin{...}` and `\end{...}`.
* **No placeholders:** Write real implementations instead of standard boilerplate comments where possible.
* **Recompile PDFs on changes:** Every time a LaTeX file (e.g., `.tex` source for reports or scripts) is modified, the corresponding PDF must be recompiled to keep it in sync with the source content.
* **Commit and push changes:** Always stage, commit, and push all modifications to the remote repository (`git push`) before concluding any task.
* **Proactive rule updates:** If you identify repetitive manual requirements or workflow improvements, automatically propose updating the rules in this `AGENTS.md` file.
