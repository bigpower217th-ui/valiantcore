# Contributing to ValiantCore

First off, thank you for checking out ValiantCore! Developing an operating system kernel requires extreme focus, precision, and adherence to system-level rules. We highly appreciate your willingness to help us build a solid core.

Please carefully read and follow this document before opening a Pull Request (PR).

---

## 🚀 How to Contribute

### 1. Finding Issues
Look for issues labeled with `help wanted` or `good first issue`. If you want to work on an existing issue, please drop a comment so it can be assigned to you.

### 2. Reporting Bugs & Panic Scenarios
If you encounter a kernel panic, a triple fault, or driver misbehavior (especially regarding hardware like the Realtek RTL8111), open an issue with:
* The exact trigger condition.
* Your emulator environment setup (e.g., QEMU, Bochs version).
* Register dumps, stack traces, or panic logs.

---

## 🛠️ Mandatory Code & Compilation Rules

### 1. Object File Compilation & Strict Syntax Verification
* **Modular Compilation:** Every single C (`.c`) and Assembly (`.asm`/`.s`) source file must be compiled independently into an intermediate object file (`.o`) using the `-c` compiler flag before the linking stage. Directly outputting to the final binary without object verification is strictly forbidden.
* **Zero-Warning Tolerance:** Your code must conform to the absolute strictest syntax rules. The project utilizes `-Wall -Wextra -Werror` flags. This means **any compiler warning will be treated as a hard error**, failing the object file build immediately.
* **Syntax Integrity:** Unused variables, unreachable code, incorrect function prototypes, or implicit type-casting that triggers data loss warnings will not pass the object build stage.

### 2. Freestanding Environment Constraints
* ValiantCore runs in a **freestanding environment**. Standard hosted C libraries (`<stdio.h>`, `<stdlib.h>`, `<string.h>`, etc.) are completely unavailable.
* You must strictly use the custom kernel libraries (`klib`) and architecture-specific headers provided within the repository.

### 3. Code Style & Formatting
* **Indentation:** Use **4 spaces** for indentation. Do not use tabs.
* **Naming Conventions:** Use `snake_case` for all variable and function names (e.g., `init_idt()`, `rtl8111_write_register()`).

### 4. Verification and Local Testing
* Before pushing your branch, you must verify that the kernel compiles cleanly with the main `Makefile`.
* Run the kernel in an emulator (QEMU). Ensure that your changes do not introduce regressions, memory corruption, or unexpected triple faults.

---

## 🔀 Git & Commit Workflow

* **Branching:** Never push directly to the `main` branch. Create a descriptive branch for your changes (e.g., `feature/rtl8111-rx`, `fix/gdt-alignment`).
* **Commit Formatting:** Keep commit messages clean, imperative, and structured. 
  * *Format:* `[module]: [description]`
  * *Examples:* `feat(interrupts): implement IDT initialization`, `fix(mem): resolve page fault in pmm`.

---

## 💬 Communication

If you want to discuss kernel architecture, memory management strategies, or need help debugging a specific low-level fault, feel free to start a thread under the **GitHub Discussions** tab.

Let's build a reliable core together!
