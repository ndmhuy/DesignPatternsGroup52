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
   - *(Note: Interactive Quiz is included exclusively in the presentation PPTX / slide decks, and is omitted from the LaTeX reports)*.
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
<!-- Synced by AgentHub 3-Layer Memory Engine at 2026-08-24T16:16:55.853Z -->

## 🥾 BOOT DIGEST — read this first (Tier 0)

> Flash-tier / small-context agents: hold these one-liners and the pointer table; open a pointed file only when the task needs it; do NOT read past the Tier 2 marker.

- **[g-rule-1]** Branch Lifecycle: Isolate, Implement, Push, Stop: All feature and bugfix work happens on a branch created off the project's designated de...
- **[g-rule-2]** Defensive Implementation & Zero Superficial Fixes: NEVER mask errors by returning dummy fallbacks, commenting out broken assertions, or s...
- **[g-rule-3]** Context-Efficient Subagent Execution: Delegate long-running research or deep search tasks to subagents with isolated context windows.
- **[g-rule-4]** Empirical Log Verification & Audit Trails: Never declare a bug fixed or feature complete without running test/build verification commands...
- **[g-rule-5]** AI Usage Logging & Declaration: Before concluding any task, append an entry to logs/agent_history.log in the format: [YYYY-MM-DD HH:MM:SS...
- **[g-rule-6]** Plan Adherence & Deviation Approval: The project's designated plan file (implementation_plan.md, SPEC.md, or TASKS.md) is the source of t...
- **[g-rule-8]** Destructive VCS Operation Guard: Before any reset, rebase, checkout that discards changes, clean, stash drop, or merge: run git status an...
- **[g-rule-9]** Targeted Edits, Never Whole-File Overwrites: Apply changes as targeted replacements that preserve surrounding human-authored content.
- **[g-rule-10]** Verify Repository State Before You State It or Relay It: Before ANY task whose output describes repository state - audits, weekly reports...
- **[g-rule-12]** Commit Per Completed Unit: Commit after completing each subtask, not in one batch at the end.
- **[g-rule-14]** Human-Facing Docs Are Readable HTML - Rendered Views vs Authored Artifacts: Anything a human reads gets a self-contained local HTML form ...
- **[g-rule-15]** One Current Doc - Legacy Goes to the Archive: Each topic has exactly ONE current document.
- **[g-rule-16]** Tiered Boot Protocol: Load project context in tiers, sized to your model, and stop at the tier you can hold.
- **[g-rule-17]** Cross-File Contracts Get a Parity Test: When one fact must exist in two or more places - an i18n key emitted from Python, an action id, a...
- **[g-rule-18]** Suggest Rules Upstream, Do Not Fork Them: When you notice something rule-worthy while working in a project - a repeated manual step, a fa...
- **[g-rule-20]** How to Write a Document: Every document states, in its first screen, what it is and who it is for; a reader must never scroll to find out.
- **[g-rule-21]** Every Substantial Piece of Work Gets a Learning Record: Whenever you build a feature, module, algorithm, or subsystem, export a self-cont...
- **[g-rule-22]** Reference Docs Are Derived, Never Hand-Synced: Any document that restates facts the code already contains - endpoint lists, module invent...
- **[g-rule-24]** Comments Carry Why, Not What: A comment that restates what the code does is hand-synced duplication of the code - g-rule-22's principle, ...
- **[g-rule-25]** Join Keys Need Immutability or an Alias Chain: An identifier used as a JOIN KEY between systems - a project slug, a bundle id, a foreign ...
- **[g-rule-27]** Name Your Single Sources of Truth: Every category of fact a project depends on - how a value is computed, where data lives, what configur...
- **[g-rule-28]** Resolve Collaborator Identity via Config, Then Git, Then Branch Prefix: Where a project's rules or conventions differ per collaborator (a...
- **[g-rule-29]** Pin Your Language Standard Explicitly: State the project's language or toolchain standard explicitly, in both AGENTS.md and the build con...
- **[g-rule-30]** Maintain an Enumerated, Documented Pattern or Requirement List: Where a project must demonstrate or maintain a fixed, enumerated list of ...
- **[g-rule-13]** "Complete" Means Reachable, Observed, and CI-Verified: Never mark a task complete because a file exists and compiles.
- **[g-rule-19]** Never Commit Generated Outputs Or Sensitive Inputs: Any artifact a build step can produce - compiled binaries and sidecars, generated PDF...
- **[dp-rule-1]** Member Identity Resolution (Inverted vs SuperMarioGame): Resolution order per g-rule-28.
- **[dp-rule-2]** LaTeX/PDF Sync: Whenever a .tex source changes, recompile the corresponding PDF so source and artifact stay in sync.
- **[dp-rule-3]** Compile Before Concluding: Run a compilation check on the pattern demo (Interpreter, Mediator, or Observer) before declaring a task compl...

### Reading these docs as HTML

Markdown working docs (README, SPEC, TASKS, plan files) render to self-contained HTML with:

```bash
python3 ~/Documents/AgentHub/scripts/render_docs.py designpatterns-group52
```

Output lands in `docs/rendered/` and is GITIGNORED. The markdown stays the only place content is edited - never hand-edit a rendered view, and never commit one (g-rule-14 class A, g-rule-19). Authored artifacts are the opposite: learning records in `docs/learning/` and reports in `reports/` ARE committed (class B).

### Suggesting a rule back to AgentHub

Noticed something rule-worthy? Do NOT edit this generated block — append to `.agenthub/suggestions.json` in this project instead:

```json
{"suggestions":[{
  "title":"...", "rationale":"the rule, and the failure it prevents",
  "proposedLayer":"L2" | "L3",        // set it explicitly; omitting it defaults to L2
  "evidence":"files, commits, incidents - survives in Tier 2",
  "suggestedBy":"who/when",
  "requestedDisposition":"defer",     // optional. "defer" is honoured on import;
  "deferRationale":"why not now"      // promote/amend stay human decisions.
}]}
```

The hub collects it (`node scripts/collect.js`) and a human promotes it. Directives OUTSIDE these markers are hand-authored and yours to edit freely.

---

## 📖 Full rule text (Tier 2 — large-context models)

## 🌐 Layer 3 — Global Universal Rules

### [Git & Branching] Branch Lifecycle: Isolate, Implement, Push, Stop
All feature and bugfix work happens on a branch created off the project's designated development branch (dev where present, otherwise main) - never work directly on the integration branch. Verify the build compiles before pushing, then push the branch to origin and STOP: never merge into dev, never commit directly to main, and never open and self-merge a pull request. Code review and integration are the user's decisions, not the agent's.

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

### [Git & Branching] Destructive VCS Operation Guard
Before any reset, rebase, checkout that discards changes, clean, stash drop, or merge: run git status and git log to capture the current state, state plainly what will be lost, and obtain explicit confirmation - do NOT proceed without it. Record HEAD before and after the operation in the log. NEVER discard uncommitted work to unblock a git operation: if a merge, pull or checkout is blocked by local changes, the default is to COMMIT them first - committing is reversible, discarding is not. Only 'git checkout -- <file>' a file that is machine-generated, and back it up outside the repo first. Never combine these with --force or --hard while uncommitted work exists.

### [Architecture & Quality] Targeted Edits, Never Whole-File Overwrites
Apply changes as targeted replacements that preserve surrounding human-authored content. Never regenerate an entire existing file to make a small change, and never write over a file you have not read. This applies to generated artifacts and rule files as much as to source code.

### [Git & Branching] Verify Repository State Before You State It or Relay It
Before ANY task whose output describes repository state - audits, weekly reports, code review, progress summaries, branch analysis, 'what is the status of X' - run 'git fetch --all' first and record it in the log. A local branch is NOT evidence of project state: check 'git rev-list --left-right --count <branch>...origin/<branch>' before drawing conclusions from what is on disk, and check whether work exists on an unmerged branch before declaring it missing. This applies to a repository's VISIBILITY and settings as much as to its branches: 'the repo is public' is repository state, it changes without touching a single commit, and a local clone cannot tell you. Check it (gh api repos/<owner>/<name>) before describing exposure - and check forkCount too, because GitHub keeps a formerly-public repo's commits reachable by SHA through the fork network, so making a repo private only fully closes one that was never forked. This applies just as much to RELAYING a peer's claim as to asserting your own: before amplifying a peer's claim about state you have previously recorded - especially to the user, especially framed as urgent - open your own record first; if it contradicts the peer, say so and re-verify rather than relaying. A peer sounding authoritative and agreeing readily is not evidence, especially in a multi-session setup where the peer can be wrong in the same direction you are. Evidence: this hub asserted twice, as an urgent security finding, that secrets remained retrievable from a public repo that had been private for a day - one session held a contradicting record and relayed the stale claim anyway, and two sessions then cross-verified each other into the same wrong answer across four exchanges until the user asked a blunt question.

### [Git & Branching] Commit Per Completed Unit
Commit after completing each subtask, not in one batch at the end. Use clear, traceable, conventional messages (e.g. 'feat: implement AABB collision detection', 'fix: resolve jump gravity bug') so history can be followed without reading diffs.

### [Documentation & Auditing] Human-Facing Docs Are Readable HTML - Rendered Views vs Authored Artifacts
Anything a human reads gets a self-contained local HTML form (inline CSS, opens from disk, no network, printable). There are TWO classes and they are handled OPPOSITELY - the test is: does a markdown file already hold the truth?

(A) RENDERED VIEWS - yes, a .md is the source of truth (SPEC.md, TASKS.md, the plan file, README, TASK_DIVISION). The markdown stays the ONLY place the content is edited; the HTML is a generated VIEW produced by 'python3 scripts/render_docs.py <project-id>' into docs/rendered/, is GITIGNORED, and carries a do-not-edit banner naming its source. Never commit these and never hand-edit them: a committed render is a second copy that is stale within hours, which is exactly g-rule-22's failure, and per g-rule-19 a derived artifact is built, not tracked. Regenerate instead of updating.

(B) AUTHORED ARTIFACTS - no markdown source holds the truth; the HTML IS the document (learning records per g-rule-21, audits, reports, guides). These are authored once, live in the project (docs/learning/, reports/), and ARE committed. Where the content derives from data, generate it with a script so it cannot drift, and never hand-edit the generated file.

Both classes must state what they are and who they are for in the first screen (g-rule-20).

### [Documentation & Auditing] One Current Doc - Legacy Goes to the Archive
Each topic has exactly ONE current document. When a doc, plan, or artifact is superseded, MOVE it to the project's designated archive directory in the same change that supersedes it, prefixed with its supersession date. The archive path is recorded per project as archiveDir (default docs/archive/); Lecturing_Source uses archive/legacy_planning/ - honour the project's choice rather than inventing a second archive. Add a README there saying when and why things were moved. Never delete it, and never leave it in place looking authoritative: a stale doc that still looks current is how contradictions survive for months. Scratch and test artifacts either move to the archive or get gitignored - the repo root is not a scratchpad.

### [Context & Boot] Tiered Boot Protocol
Load project context in tiers, sized to your model, and stop at the tier you can hold. TIER 0 (everyone, always): the BOOT DIGEST at the top of the AgentHub block in AGENTS.md - one line per rule - plus the pointer table. TIER 1 (on demand): open ONLY the pointed file that matches the current task (constants for physics work, report rules for reports, spec for gameplay values). TIER 2 (large-context models only): the full rule text and reference docs. Small or flash-tier agents MUST NOT inline the whole rulebook - holding 10 rules reliably beats holding 40 badly. Authoring side of the same rule: constants, tables, and external links live in ONE pointed file each, never duplicated inline in AGENTS.md; a value that exists in two places is already wrong in one of them.

### [Verification & CI] Cross-File Contracts Get a Parity Test
When one fact must exist in two or more places - an i18n key emitted from Python, an action id, an enum member, an endpoint string, a JSON field a JS module reads, a default model name, a documented screen - the SAME commit adds or extends the parity test that fails when the copies disagree. 'The agent should remember the other place' is not a mechanism; a failing test that names the other place is. g-rule-16 says a value in two places is already wrong in one of them - this is what catches it. A contract also breaks when one side SILENTLY DISCARDS what the other sends, not just when copies disagree - assert the value ARRIVES, not just that it was sent. AND THE TEST MUST FAIL WHEN THE VALUE IS MISSING, not only when copies differ: a parity test that returns None when it cannot find its target PASSES VACUOUSLY, which is worse than no test because it buys false confidence - search for the key and fail if absent, assert non-empty before asserting equal. Part of the duplicated-state family with g-rule-22/25. (Patterns to follow, and the incidents that motivated the vacuous-pass clause: see RULE_REFERENCE.md § Parity Test Patterns & Vacuous-Pass Guard.)

### [Communication] Suggest Rules Upstream, Do Not Fork Them
When you notice something rule-worthy while working in a project - a repeated manual step, a failure that a rule would have prevented, a convention the team keeps re-deciding - APPEND it to .agenthub/suggestions.json in that project (schema: id, title, rationale, proposedLayer L2|L3, evidence, status pending) rather than silently editing the AGENTS.md managed block, which is generated and will be overwritten. Project-specific directives outside the markers are still yours to edit freely. AgentHub collects suggestions with 'node scripts/collect.js'; a human promotes them. This is the upstream half of the loop: rules flow hub -> project by distribution, and project -> hub by suggestion.

### [Documentation & Auditing] How to Write a Document
Every document states, in its first screen, what it is and who it is for; a reader must never scroll to find out. Then: (1) SUMMARY BEFORE DETAIL - the conclusion, current state, or quick-context block comes first, the reasoning after (same tiering as g-rule-16). (2) PRECISION OVER VAGUENESS - never 'fixed character movement'; write 'moved horizontal friction and run-speed clamping into PhysicsEngine::update()'. A sentence a reader cannot act on is not documentation. (3) LINK, DO NOT COPY - reference the file, commit, or other doc with a clickable path instead of restating its content; duplicated prose is g-rule-16's two-places problem in text form. (4) VERIFY BEFORE WRITING - check commit SHAs, filenames, and command output against the real tree; never invent a detail, and say 'not verified' rather than implying you checked. (5) RATIONALE FOR EVERY RULE OR DECISION - record the failure it prevents, so a later reader can tell whether it still applies. (6) A DOC THAT DESCRIBES A PROCEDURE ends with the exact commands to run it. Project-specific templates (report structures, runbooks) live in the project and override these defaults where they conflict.

### [Documentation & Auditing] Every Substantial Piece of Work Gets a Learning Record
Whenever you build a feature, module, algorithm, or subsystem, export a self-contained local HTML learning record to docs/learning/<topic>.html (format per g-rule-14). It is written for the student who must revise this months later, not for whoever just wrote it. Twelve required sections, from prerequisites through a worked trace with real values to a changelog stamped against a commit - full template, section-by-section requirements, and the code-excerpt integrity rules: see RULE_REFERENCE.md § Learning Records. Generate the skeleton with 'node scripts/new_learning_doc.js', not a blank file. Update it in the same change that alters the thing it describes (g-rule-15). A section you cannot fill honestly says so and stops. Weekly reports are a different, per-week artifact governed by each project's own report rules - do not merge the two.

### [Documentation & Auditing] Reference Docs Are Derived, Never Hand-Synced
Any document that restates facts the code already contains - endpoint lists, module inventories, dependency graphs, state machines, counts - must be GENERATED by a script from the code (and drift-checked in CI) or must not exist. Hand-maintained prose is reserved for what code cannot state: intent, invariants, and the history of why. A hand-synced restatement of code is already wrong or soon will be, and a stale one is worse than none because it looks authoritative. If a generated artifact contradicts prose, the generated artifact wins and the prose gets fixed. THIS APPLIES TO THE RULESET ITSELF: a rule's evidence clause states facts about the world, and those rot exactly like any other hand-maintained restatement, except worse - a stale rule is distributed to every project and read as authority. Re-verify a rule's factual claims before citing them, and PREFER HISTORICAL CLAIMS OVER CURRENT-STATE CLAIMS when writing evidence. Where a current-state claim is unavoidable, date it and name the check that confirms it. Part of the duplicated-state family with g-rule-17/25. (Worked example and evidence: see RULE_REFERENCE.md § Historical-vs-Current-State Worked Example.)

### [Architecture & Quality] Comments Carry Why, Not What
A comment that restates what the code does is hand-synced duplication of the code - g-rule-22's principle, applied at the comment/line level. It rots the moment the code changes and then actively misleads, so it is worse than no comment. Do not write them, and delete them when found. If a comment is needed to explain WHAT the code does, rename or restructure first. Comment these instead: (1) WHY this approach rather than the obvious alternative; (2) NON-OBVIOUS INVARIANTS and the failure they prevent - cite the incident when one applies; (3) CONSTRAINTS FROM OUTSIDE THE FILE; (4) DELIBERATE CHOICES a future reader would otherwise 'fix' and break; (5) UNITS, RANGES, COORDINATE SYSTEMS, OWNERSHIP AND LIFETIME wherever ambiguous. Every public function, class, or module gets a docstring stating its CONTRACT: what it guarantees, what it raises, and what it deliberately does NOT do. Keep a comment adjacent to what it describes and update it in the same change (g-rule-15 at line level). The docstring-on-public-API clause is CI-enforceable via linter docstring rules (ruff D / pydocstyle); the rest is judgement, not lintable. (Calibration details and evidence: see RULE_REFERENCE.md § Comment Discipline & Docstring Enforcement.)

### [Architecture & Quality] Join Keys Need Immutability or an Alias Chain
An identifier used as a JOIN KEY between systems - a project slug, a bundle id, a foreign key in stored data, a directory named after an entity - is load-bearing in a way its name does not advertise. This is the third member of the duplicated-state family with g-rule-17/22, and the quietest: the copies do not disagree and nothing is discarded; the identity underneath both simply changes, records stop matching, and resolved work silently resurrects or vanishes. Pick one of two remedies deliberately, never by accident: (1) IMMUTABILITY - freeze the key, comment why (g-rule-24), pin it with a test; or (2) AN ALIAS CHAIN - permit the rename but record prior names and match against them everywhere the key is used for lookup. Choose by which side is cheaper to change: FREEZE when copies are already in the field and beyond your reach; ALIAS when the rename is already in flight. If the key can be renamed at all, a RENAME TEST belongs beside the parity test. (Worked incidents: see RULE_REFERENCE.md § Join-Key Incidents.)

### [Architecture & Quality] Name Your Single Sources of Truth
Every category of fact a project depends on - how a value is computed, where data lives, what configuration is valid - has exactly one owning artifact: a file, module, or document that alone defines it. State the ownership explicitly, one line per concern (a table works well in a project's L2 rules), naming what must never be duplicated or hardcoded elsewhere. This is the file-level form of g-rule-16's two-places problem: a fact restated in a second place is already wrong in one of them, and naming the single owner is what makes 'don't duplicate' something a reader can check rather than something they have to remember. A project's L2 rules should name owning artifacts by concern in one place, not re-explain the single-source-of-truth principle from scratch for every concern.

### [Communication] Resolve Collaborator Identity via Config, Then Git, Then Branch Prefix
Where a project's rules or conventions differ per collaborator (a private per-member note, a task assignment, a review focus), resolve which collaborator is acting in this precedence: an explicit per-machine config file first (e.g. .member_profile.json), then git config user.name, then a branch-name prefix convention (e.g. A/ vs B/) as the last resort. The resolution ALGORITHM is universal; the MAPPING from a letter or config value to a specific person is project-specific and must never be assumed to carry across repositories - the same prefix can mean opposite people in two different projects, which is exactly the load-bearing, easy-to-assume-portable identifier g-rule-25 warns about. Each project's L2 rules record only its own mapping table, referencing this rule for the resolution order.

### [Architecture & Quality] Pin Your Language Standard Explicitly
State the project's language or toolchain standard explicitly, in both AGENTS.md and the build configuration (e.g. CMAKE_CXX_STANDARD), and forbid features from adjacent versions that aren't the pinned one. A project silently drifting between standards erodes the portability guarantees the pin exists for, and confuses which language features are safe to use where. Each project's L2 rule states only its own pinned version and what's forbidden; this rule states why pinning and enforcing it matters.

### [Documentation & Auditing] Maintain an Enumerated, Documented Pattern or Requirement List
Where a project must demonstrate or maintain a fixed, enumerated list of named things - design patterns implemented, requirements satisfied, an assessment rubric's checklist - keep that list explicit, named, and current as the project evolves, rather than letting 'we probably still do most of these' stand in for a checked fact. Each project's L2 rule states only its own list; this rule states why the list must be explicit and kept current rather than assumed.

### [Verification & CI] "Complete" Means Reachable, Observed, and CI-Verified
Never mark a task complete because a file exists and compiles. A task is complete only when (a) the code is reachable from the program's real entry point, not solely from a verify_*/test harness, and (b) you have observed it working - a passing test case or an actual run of the program. If you implemented something but did not wire it, say so explicitly and leave the checkbox unticked. A rule only a human remembers to apply is not enforced, so every project containing buildable or testable code carries a CI workflow that builds it and runs its tests automatically on push and pull request to the integration branches - CI is the mechanism that makes 'reachable and observed' checkable by something other than good intentions. CI must be HERMETIC: pin dependencies, and never let a test assert against a developer's local paths, mounted drives, or machine state - point the base directory at an empty scratch dir instead. Where the project ships artifacts, a release workflow builds them too. Do not mark CI optional because a project is coursework: the August 2026 SuperMarioGame audit found three critical defects and six inert subsystems that survived precisely because nothing ran automatically.

### [Security & Data Handling] Never Commit Generated Outputs Or Sensitive Inputs
Any artifact a build step can produce - compiled binaries and sidecars, generated PDFs, __pycache__, bundled assets, dumped git logs - is gitignored and produced by CI, never committed: a tracked build output is a merge conflict waiting to happen and makes the diff lie about what changed. Evidence: Lecturing_Source stopped tracking its compiled sidecar in 8db4c31; DataStructureVisualizer tracked README.pdf, git_history.txt and commits_summary.txt as of 2026-08-21 - all three reproducible from source or git itself, which is what makes them build outputs rather than content. Sensitive INPUTS differ in KIND, not degree, and get stricter treatment: identity documents, keys, credentials, client names, personal data must never enter git at all, since a passport scan or licence key committed once stays retrievable from history forever, including after deletion. For sensitive inputs: (1) deny the types repo-wide BEFORE the first commit - history is immutable; (2) enforce with a CI job that runs INDEPENDENTLY of the build; (3) prefer a LOCATION INVARIANT in code over a pattern list; (4) default to a PRIVATE repository whenever the blast radius of one mistake is irreversible. If something sensitive was already committed, treat it as disclosed: rotate the secret and say so. (Full incident log: see RULE_REFERENCE.md § Sensitive Content Incident Log & Remediation Detail.)

## 📁 Layer 2 — Project Domain Rules (DesignPatternsGroup52 (CS202 Seminar))

**Category**: C++ Design Patterns / LaTeX Seminar
**Tech Stack**: C++, LaTeX, Interpreter, Mediator, Observer
**Repository**: https://github.com/ndmhuy/DesignPatternsGroup52

### [CRITICAL] Member Identity Resolution (Inverted vs SuperMarioGame)
Resolution order per g-rule-28. In THIS project's mapping: A/ or A- prefixed branches are Member A (Tran Gia Huy); B/ or B- prefixed branches are Member B (Nguyen Dinh Minh Huy). This is the OPPOSITE assignment from SuperMarioGame - never assume the mapping carries across repositories (g-rule-25).

### [MANDATORY] LaTeX/PDF Sync
Whenever a .tex source changes, recompile the corresponding PDF so source and artifact stay in sync. Verify every \begin{...} has a matching \end{...} before compiling.

### [MANDATORY] Compile Before Concluding
Run a compilation check on the pattern demo (Interpreter, Mediator, or Observer) before declaring a task complete. No placeholder implementations - write real code, not boilerplate comments.

### 🛠 Assigned Project Skills
- `learning-record-writer`
- `doc-view-renderer`

## ⚡ Layer 1 — Working Context

> Note: `session_l1.json` referenced below lives in the **AgentHub repo**, not in this project. Nothing in this section asks you to create a local file.

No active session for this project. Live L1 state is held in the AgentHub repo (`AgentHub/data/session_l1.json` - NOT a file in this project).

### [CRITICAL] Session Identity Resolution
At session start, resolve the active member using .member_profile.json, then git config user.name, then branch prefix - in that order - and record the result and its source in session_l1.json. Read the A/B mapping from the active project's L2 rules; never assume it from another project.

### [MANDATORY] Single-Project Context Budget
Load L3 universal rules plus exactly one project's L2 block. Do not load other projects' L2 rules into the same session - cross-project rules conflict (see the inverted A/B mapping) and waste the context window.

### [STANDARD] Session Handoff
Before concluding, write taskFocus and any unresolved openThreads back to session_l1.json so the next session resumes without re-deriving state. This is L1 only - it is transient and must never be promoted into L2 or L3.

<!-- AGENTHUB:L3:END -->
