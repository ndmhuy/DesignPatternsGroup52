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
- **Git Branch Check**: Retrieve the active git branch name (e.g., running `git branch --show-current`).
  - Branches starting with `A/` or `A-` indicate **Member A (Trần Gia Huy)** is working.
  - Branches starting with `B/` or `B-` indicate **Member B (Nguyễn Đình Minh Huy)** is working.
- **Git User Check**: Retrieve the local git user configuration (`git config user.name`).
- **Profile Check**: Check if `.member_profile.json` exists at the workspace root.

### 2. Private Knowledge & Custom User Orders
Since all git-tracked files are shared, custom personal notes, reminders, or private user orders for the agent should be kept in a local, gitignored configuration file called `.member_profile.json` at the project root.

Each developer can create their own `.member_profile.json` locally. The agent must search for and read this file (if present) to load custom, member-specific orders.

#### Example `.member_profile.json` Schema:
```json
{
  "memberName": "B",
  "developerName": "Nguy\~{\^e}n \DJ\`inh Minh Huy",
  "privateNotes": "Any specific reminders or notes from the user that should not be shared via Git.",
  "agentCustomInstructions": [
    "Ensure LaTeX report compiles with pdflatex cleanly.",
    "Propose code changes that are standard-compliant."
  ]
}
```
If `.member_profile.json` is missing, the agent must gracefully fall back to git configuration or branch detection or invite the developer to create this file.

---

## 🤖 Guidelines for AI Actions

* **Always preserve context:** Do not overwrite existing code or markdown files fully; use targeted replacement blocks.
* **Keep code compilable:** Before concluding a task, run a compilation check to ensure there are no syntax errors.
* **Keep LaTeX syntax valid:** Ensure all LaTeX blocks are closed properly, particularly `\begin{...}` and `\end{...}`.
* **No placeholders:** Write real implementations instead of standard boilerplate comments where possible.
* **Recompile PDFs on changes:** Every time a LaTeX file (e.g., `.tex` source for reports or scripts) is modified, the corresponding PDF must be recompiled to keep it in sync with the source content.
* **Commit and push changes:** Always stage, commit, and push all modifications to the remote repository (`git push`) before concluding any task.
* **Proactive rule updates:** If you identify repetitive manual requirements or workflow improvements, automatically propose updating the rules in this `AGENTS.md` file.
* **Automatic Task & Prompt Logging:** Automatically append a summary of each user prompt and the corresponding results to the local log file: [agent_history.log](file:///Users/huynguyen/Documents/CS202-Cpp/DesignPatternsGroup52/logs/agent_history.log) in the specified format before concluding a task.

---

## 📝 Automatic Log Entry Format

Every time you finish a task, append to `logs/agent_history.log` at the project root in this format:

```text
[YYYY-MM-DD HH:MM:SS] Branch: <branch_name>
Prompt: <brief prompt summary>
Files Modified: <list of files>
Summary of Changes: <brief bulleted list>
---
```

---

<!-- AGENTHUB:L3:BEGIN — generated, do not edit by hand -->
<!-- Synced by AgentHub 3-Layer Memory Engine at 2026-08-21T08:12:49.055Z -->

## 🥾 BOOT DIGEST — read this first (Tier 0)

> Flash-tier / small-context agents: hold these one-liners and the pointer table; open a pointed file only when the task needs it; do NOT read past the Tier 2 marker.

- **[g-rule-1]** Strict Git Branch Isolation: All feature and bugfix work happens on a branch created off the project's designated development branch (dev...
- **[g-rule-2]** Defensive Implementation & Zero Superficial Fixes: NEVER mask errors by returning dummy fallbacks, commenting out broken assertions, or s...
- **[g-rule-3]** Context-Efficient Subagent Execution: Delegate long-running research or deep search tasks to subagents with isolated context windows.
- **[g-rule-4]** Empirical Log Verification & Audit Trails: Never declare a bug fixed or feature complete without running test/build verification commands...
- **[g-rule-5]** AI Usage Logging & Declaration: Before concluding any task, append an entry to logs/agent_history.log in the format: [YYYY-MM-DD HH:MM:SS...
- **[g-rule-6]** Plan Adherence & Deviation Approval: The project's designated plan file (implementation_plan.md, SPEC.md, or TASKS.md) is the source of t...
- **[g-rule-7]** Human-Owned Integration (No Auto-Merge): Agents implement on their task branch, verify compilation, push the branch to origin, and stop.
- **[g-rule-8]** Destructive VCS Operation Guard: Before any reset, rebase, checkout that discards changes, clean, stash drop, or merge: run git status an...
- **[g-rule-9]** Targeted Edits, Never Whole-File Overwrites: Apply changes as targeted replacements that preserve surrounding human-authored content.
- **[g-rule-10]** Fetch Before You Read the Repository: Before ANY task whose output describes repository state - audits, weekly reports, code review, prog...
- **[g-rule-11]** "Complete" Means Reachable and Observed: Never mark a task complete because a file exists and compiles.
- **[g-rule-12]** Commit Per Completed Unit: Commit after completing each subtask, not in one batch at the end.
- **[g-rule-13]** Automated Verification Gate (CI/CD): Every project containing buildable or testable code carries a CI workflow that builds it and runs it...
- **[g-rule-14]** Deliverables Export as Local HTML: Any generated deliverable meant for humans to read - a report, audit, guide, or review - is exported a...
- **[g-rule-15]** One Current Doc - Legacy Goes to the Archive: Each topic has exactly ONE current document.
- **[g-rule-16]** Tiered Boot Protocol: Load project context in tiers, sized to your model, and stop at the tier you can hold.
- **[dp-rule-1]** Member Identity Resolution (Inverted vs SuperMarioGame): In THIS project: A/ or A- prefixed branches are Member A (Tran Gia Huy); B/ or B...
- **[dp-rule-2]** LaTeX/PDF Sync: Whenever a .tex source changes, recompile the corresponding PDF so source and artifact stay in sync.
- **[dp-rule-3]** Compile Before Concluding: Run a compilation check on the pattern demo (Interpreter, Mediator, or Observer) before declaring a task compl...

---

## 📖 Full rule text (Tier 2 — large-context models)

## 🌐 Layer 3 — Global Universal Rules

### [Git & Branching] Strict Git Branch Isolation
All feature and bugfix work happens on a branch created off the project's designated development branch (dev where present, otherwise main). Never work directly on the integration branch. Verify the build compiles before pushing. Integration itself is governed by g-rule-7.

### [Architecture & Quality] Defensive Implementation & Zero Superficial Fixes
NEVER mask errors by returning dummy fallbacks, commenting out broken assertions, or swallowing exceptions. Root cause analysis must precede all code changes.

### [AI Subagent Delegation] Context-Efficient Subagent Execution
Delegate long-running research or deep search tasks to subagents with isolated context windows. Do not poll in a loop; wait for asynchronous task completion.

### [Documentation & Auditing] Empirical Log Verification & Audit Trails
Never declare a bug fixed or feature complete without running test/build verification commands and reading un-truncated log outputs.

### [AI Governance] AI Usage Logging & Declaration
Before concluding any task, append an entry to logs/agent_history.log in the format: [YYYY-MM-DD HH:MM:SS] Branch: <branch> / Prompt: <summary> / Files Modified: <list> / Summary of Changes: <bullets> / Git Fingerprint: <commit before> -> <after>. EVERY field the project's template defines is mandatory: a field you cannot answer is written 'n/a' WITH a reason, never omitted. Report honestly - if code compiles but nothing calls it, say so; if you did not run the program, write 'build only'. An optimistic entry is worse than no entry because it stops anyone looking again. The log is append-only shared history: when it CONFLICTS during a merge, resolve by UNION - keep every entry from both sides sorted by timestamp, never choose a side. Maintain prompts.md where the course requires an AI Usage Declaration.

### [Planning & Scope] Plan Adherence & Deviation Approval
The project's designated plan file (implementation_plan.md, SPEC.md, or TASKS.md) is the source of truth for scope. Read it before writing code. If you intend to deviate from the approved plan, or to do work not in it, inform the user and obtain confirmation first. Update task checkboxes as work completes.

### [Git & Branching] Human-Owned Integration (No Auto-Merge)
Agents implement on their task branch, verify compilation, push the branch to origin, and stop. Never merge into dev, never commit directly to main, never open and self-merge a pull request. Code review and integration are the user's decisions.

### [Git & Branching] Destructive VCS Operation Guard
Before any reset, rebase, checkout that discards changes, clean, stash drop, or merge: run git status and git log to capture the current state, state plainly what will be lost, and obtain explicit confirmation - do NOT proceed without it. Record HEAD before and after the operation in the log. NEVER discard uncommitted work to unblock a git operation: if a merge, pull or checkout is blocked by local changes, the default is to COMMIT them first - committing is reversible, discarding is not. Only 'git checkout -- <file>' a file that is machine-generated, and back it up outside the repo first. Never combine these with --force or --hard while uncommitted work exists.

### [Architecture & Quality] Targeted Edits, Never Whole-File Overwrites
Apply changes as targeted replacements that preserve surrounding human-authored content. Never regenerate an entire existing file to make a small change, and never write over a file you have not read. This applies to generated artifacts and rule files as much as to source code.

### [Git & Branching] Fetch Before You Read the Repository
Before ANY task whose output describes repository state - audits, weekly reports, code review, progress summaries, branch analysis, 'what is the status of X' - run 'git fetch --all' first and record it in the log. A local branch is NOT evidence of project state: check 'git rev-list --left-right --count <branch>...origin/<branch>' before drawing conclusions from what is on disk, and check whether work exists on an unmerged branch before declaring it missing.

### [Documentation & Auditing] "Complete" Means Reachable and Observed
Never mark a task complete because a file exists and compiles. A task is complete only when (a) the code is reachable from the program's real entry point, not solely from a verify_*/test harness, and (b) you have observed it working - a passing test case or an actual run of the program. Building is not verifying. If you implemented something but did not wire it, say so explicitly and leave the checkbox unticked.

### [Git & Branching] Commit Per Completed Unit
Commit after completing each subtask, not in one batch at the end. Use clear, traceable, conventional messages (e.g. 'feat: implement AABB collision detection', 'fix: resolve jump gravity bug') so history can be followed without reading diffs.

### [Verification & CI] Automated Verification Gate (CI/CD)
Every project containing buildable or testable code carries a CI workflow that builds it and runs its tests automatically on push and pull request to the integration branches. A rule only a human remembers to apply is not enforced - CI is the mechanism that makes g-rule-11 ('complete means reachable and observed') checkable by something other than good intentions. CI must be HERMETIC: pin dependencies, and never let a test assert against a developer's local paths, mounted drives, or machine state - point the base directory at an empty scratch dir instead. Where the project ships artifacts, a release workflow builds them too. Do not mark CI optional because a project is coursework: the August 2026 SuperMarioGame audit found three critical defects and six inert subsystems that survived precisely because nothing ran automatically.

### [Documentation & Auditing] Deliverables Export as Local HTML
Any generated deliverable meant for humans to read - a report, audit, guide, or review - is exported as a SELF-CONTAINED local HTML file inside the project (inline CSS, no CDN dependencies), alongside its markdown source when one exists. Local-first: the file must open from disk with no server and no network. Follow the AgentHub pattern (audit.html, guides.html): if the content derives from data, generate it with a script so it cannot drift, and never hand-edit the generated file.

### [Documentation & Auditing] One Current Doc - Legacy Goes to the Archive
Each topic has exactly ONE current document. When a doc, plan, or artifact is superseded, MOVE it to docs/archive/ (create it if absent) in the same change that supersedes it - prefixed with its supersession date, e.g. docs/archive/2026-08-20_old_plan.md. Never delete it, and never leave it in place looking authoritative: a stale doc that still looks current is worse than no doc, because it is how contradictions like C++17-vs-C++20 survive for months. Scratch and test artifacts (test-*.svg, scratch_*, one-off dumps) either move to the archive or get gitignored - the repo root is not a scratchpad.

### [Context & Boot] Tiered Boot Protocol
Load project context in tiers, sized to your model, and stop at the tier you can hold. TIER 0 (everyone, always): the BOOT DIGEST at the top of the AgentHub block in AGENTS.md - one line per rule - plus the pointer table. TIER 1 (on demand): open ONLY the pointed file that matches the current task (constants for physics work, report rules for reports, spec for gameplay values). TIER 2 (large-context models only): the full rule text and reference docs. Small or flash-tier agents MUST NOT inline the whole rulebook - holding 10 rules reliably beats holding 40 badly. Authoring side of the same rule: constants, tables, and external links live in ONE pointed file each, never duplicated inline in AGENTS.md; a value that exists in two places is already wrong in one of them.

## 📁 Layer 2 — Project Domain Rules (DesignPatternsGroup52 (CS202 Seminar))

**Category**: C++ Design Patterns / LaTeX Seminar
**Tech Stack**: C++, LaTeX, Interpreter, Mediator, Observer
**Repository**: https://github.com/ndmhuy/DesignPatternsGroup52

### [CRITICAL] Member Identity Resolution (Inverted vs SuperMarioGame)
In THIS project: A/ or A- prefixed branches are Member A (Tran Gia Huy); B/ or B- prefixed branches are Member B (Nguyen Dinh Minh Huy). This is the OPPOSITE assignment from SuperMarioGame - never assume the mapping carries across repositories.

### [MANDATORY] LaTeX/PDF Sync
Whenever a .tex source changes, recompile the corresponding PDF so source and artifact stay in sync. Verify every \begin{...} has a matching \end{...} before compiling.

### [MANDATORY] Compile Before Concluding
Run a compilation check on the pattern demo (Interpreter, Mediator, or Observer) before declaring a task complete. No placeholder implementations - write real code, not boilerplate comments.

## ⚡ Layer 1 — Working Context

No active session for this project. Live state lives in `data/session_l1.json`.

### [CRITICAL] Session Identity Resolution
At session start, resolve the active member using .member_profile.json, then git config user.name, then branch prefix - in that order - and record the result and its source in session_l1.json. Read the A/B mapping from the active project's L2 rules; never assume it from another project.

### [MANDATORY] Single-Project Context Budget
Load L3 universal rules plus exactly one project's L2 block. Do not load other projects' L2 rules into the same session - cross-project rules conflict (see the inverted A/B mapping) and waste the context window.

### [STANDARD] Session Handoff
Before concluding, write taskFocus and any unresolved openThreads back to session_l1.json so the next session resumes without re-deriving state. This is L1 only - it is transient and must never be promoted into L2 or L3.

<!-- AGENTHUB:L3:END -->
