# VerklemptOS 

*A hobbyist operating system project and the cure to my boredom — minimal now, but growing into something personal, strange, and educational.*

---

## Project Structure

```
VerklemptOS/
 ├─ boot.asm      # Multiboot-compliant bootloader
 ├─ kernel.c      # Minimal C kernel (screen clear + hello world)
 ├─ linker.ld     # Linker script
 ├─ build.sh      # Build + run helper script
 ├─ .gitignore
 └─ README.md
```

---

## Requirements

To build and run VerklemptOS v0.0.1, you’ll need:

* **Linux environment** (or WSL/VM)
* **Build tools**:

  * `nasm` (assembler)
  * `gcc` (with `-m32` support for 32-bit)
  * `ld` (GNU linker)
  * `qemu-system-i386` (virtual machine for testing)

Install dependencies on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install nasm qemu-system-x86 gcc build-essential 
```

---

## Build & Run

1. Clone the repository:

```bash
git clone https://github.com/YOUR_USERNAME/VerklemptOS.git
cd VerklemptOS
```

2. Build and run:

```bash
./build.sh
```

3. Expected output in QEMU:
   A cleared black screen with the text:

```
Welcome to VerklemptOS v0.0.1
```

---

## Technical Notes

* **Bootloader**: Written in NASM assembly, conforms to **Multiboot spec**, and hands control to the kernel.
* **Kernel**: Written in C, linked with a custom linker script to ensure correct memory layout.
* **Video**: Directly writes to **VGA text buffer (0xb8000)** for screen output.
* **Testing**: QEMU is used for safe, fast iteration (before exporting to VirtualBox).

---

## Roadmap

VerklemptOS is currently a barebones kernel (v0.0.1), but the vision is much larger.
See **ROADMAP** for the long-term (and sometimes crazy) ideas.

---

## Why “VerklemptOS”?

The word *Verklempt* means “choked up” or “overcome with emotion.” That's all you need to know about that..
To be frank, this project idea was conceived cause I was pretty much bored out of my mind.

---

## Contributing

VerklemptOS is meant to be playful, experimental, and collaborative. Contributions are welcome in many forms:

- Submitting bug fixes or improvements to existing code.
- Adding new shell commands or fun ASCII art.
- New modules - anything that you feel this project needs. 
- Expanding hardware support (keyboard, timer, paging, etc.)
- Sharing crazy ideas that push the project in weird directions

Contribution Guidelines

- Fork the repo and create a new branch (feature/new-command).
- Make your changes with clear commit messages.
- Submit a Pull Request — describe your idea and why it belongs in VerklemptOS.

Whether you’re here to learn, to tinker, or just to add creepy ASCII skulls, you’re welcome to contribute.

# ROADMAP

## VerklemptOS Roadmap

This section outlines both **practical milestones** and **wild, creative goals** for VerklemptOS.
It’s equal parts technical growth plan and playground for weird ideas.

---

##  Completed

* [x] Bootloader in NASM (multiboot spec compliant)
* [x] C kernel entry (`kernel_main`)
* [x] VGA text buffer printing
* [x] First message  + screen clear (v0.0.1 milestone)

---

##  Short-Term Goals (v0.1.x)

* [ ] Add **keyboard input** (polling scancodes from port `0x60`)
* [ ] Implement a **basic shell loop** (command → execute → prompt)
* [ ] Shell commands:

  * [ ] `help` → list commands
  * [ ] `clear` → clear VGA screen
  * [ ] `ascii` → print horror ASCII art screen
* [ ] Improve text printing (cursor handling, newlines)

---

## Mid-Term Goals

* [ ] Implement a **simple text editor** (insert, delete, save buffer in memory)
* [ ] Expand shell with more commands:

  * [ ] `echo <text>`
  * [ ] `time` (fake clock first, real RTC later)
  * [ ] `reboot` (trigger CPU reset)
* [ ] Memory management basics:

  * [ ] Paging setup
  * [ ] Simple heap allocator (`malloc`/`free`)
* [ ] Add **ASCII animations** (rotating skulls? glitchy static?)

---

## Long-Term

* [ ] File system exploration (maybe a toy FS or FAT12 support)
* [ ] Process management (very simple multitasking)
* [ ] Sound output (PC speaker for my tunes, later maybe WAV playback)
* [ ] Load and run external “programs” (shell modules)
* [ ] Explore **GUI mode** (VGA graphics mode, draw pixels)

---

## Wild / Experimental Ideas

These are more for fun, not practicality:

* [ ] **AI-inspired OS personality** — the OS “talks back” in text mode and self-learns? Something like Skynet? (rule-based first, then maybe ML experiments)
* [ ] **Mood-driven shell themes** (screen changes color schemes / ASCII art based on time or user actions)
* [ ] **Horror Easter Eggs** — random ASCII glitches, creepy whispers (“the void is listening”)
* [ ] **Procedural ASCII art generator** (system invents new horror images)
* [ ] Integration with music: OS can play a playlist or trigger soundscapes

---

## Again, why VerklemptOS ?

VerklemptOS isn’t about being fast, secure, or production-ready.
It’s about:

* Learning OS development
* Playing with low-level code
* Mixing **technical seriousness** with **creative weirdness**

---
