# Changes Since Last Presentation

This document outlines the modifications, enhancements, and bug fixes applied to the DesignPatternsGroup52 project repository since the last presentation milestone.

## 1. Codebase Refactoring & Implementation
- **Mediator Pattern**: Completed the full C++17 pattern-based implementation in `Mediator/src/pattern.cpp`. Replaced the $O(N^2)$ direct-pointer mesh from `naive.cpp` with a centralized `ATCTower` mediator, adopting a star topology that manages runway coordination, holding queues, and emergency overrides.
- **Observer Pattern**: Refactored the Observer implementation to separate event dissemination cleanly. Combined the Observer pattern with Mediator to document an "Event Aggregator/Event Bus" approach. Added `runNaiveDemo()` global wrapper to `naive.cpp` and updated `main.cpp` to execute both naive and pattern demos uniformly.
- **Interpreter Pattern**: Stabilized the Interpreter source code; confirmed correct recursive AST evaluation for complex boolean expressions. Updated `runNaiveDemo()` in `naive.cpp` to highlight algebraic precedence vs. left-to-right evaluation divergence.

## 2. LaTeX Reports & Documentation
- **Removed Quizzes**: Extracted the "Interactive Quiz" sections from the `Observer`, `Interpreter`, and `Mediator` LaTeX reports to strictly adhere to the rubric (quizzes are now solely in the PPTX decks).
- **Logical Flaw Correction**: Corrected mathematical operator precedence demonstration in `Interpreter/reports/report.tex` (Section 2.1) to cleanly prove divergence between naive left-to-right evaluation and algebraic precedence ($\text{AND} > \text{OR}$).
- **Cross-Referencing & Consistency**: Resolved all orphaned `\label` entries across `Observer`, `Interpreter`, and `Mediator` reports by adding direct in-text references (`Figure~\ref{...}`, `Table~\ref{...}`) for all class diagrams and drawback tables.
- **Mediator Report Enhancements**:
  - Expanded TikZ diagram dimensions (Figures 1 and 2) to eliminate node overlaps and fix visual clipping.
  - Replaced markdown-style bolding (`**Event Aggregator**`) with proper LaTeX `\textbf{}` commands.
  - Wrapped large UML diagrams and execution trace tables with `\resizebox` to ensure they fit neatly within the document margins.
  - Rewrote sentences containing long contiguous strings (e.g., `declareEmergency()`, `requestLandingPermission()`) to resolve all `Overfull \hbox` compilation warnings.
- **PDF Compilation**: Automatically regenerated and synchronized all PDF artifacts (`report.pdf`) across all three patterns (`Observer`, `Interpreter`, `Mediator`) ensuring a zero-warning build process.

## 3. Project Tooling & Logs
- **AI Tracking**: All AI prompt generations and code modifications have been rigorously logged with commit hashes in `logs/agent_history.log` in accordance with the project's AI Usage guidelines.
- **Deliverables**: Generated submission-ready assets including the `AI_Usage_Declaration.md` and the updated Project Evaluation spreadsheet.
