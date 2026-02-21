
## 🏛️ Monorepo Architecture

This repository adopts a **Multi-Project Solution** structure within Visual Studio. I treat each learning module as an encapsulated project to ensure modularity.

```text
Engineering-Logic-Roadmap/
├── Engineering-Logic-Roadmap.slnx       # Central Workspace Entry Point
├── README.md                           # Core Documentation & Progress Tracker
├── .gitignore                          # Environment-agnostic filters
│
├── 05-Algorithms-L2/                   # 🧩 Level 2: Standalone Logic & Math
│   ├── 05-Algorithms-L2.vcxproj
│   └── *.cpp                           # Collection of logic exercises
│
└── projects/                           # 📂 Structured Applications
    ├── 05-l2-p1-rock-paper-scissors/   # ✊ Game Project 1
    │   ├── 05-l2-p1-rps.slnx
    │   └── 05-l2-p1-rock-paper-scissors.cpp
    │
    ├── 13-Bank-System/                 # 🏦 [Capstone] OOP Project
    │   └── ...
    │
    └── ...
```
