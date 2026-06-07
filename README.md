# Competitive Programming Notebook Generator

Generate a **LaTeX competitive programming notebook** from your `code/` folder and compile it into a PDF automatically.

---

## Folder Rules

* Each **folder** → **section**
* Each **file** → **subsection**
* Use **numeric prefixes** (`01-`, `02-`) to control order; they are removed in the notebook.

**Example:**

```
code/
 ├── 01-graph/
 │    ├── 01-dsu.cpp
 │    └── 02-dijkstra.cpp
 └── 02-dp/
      └── 01-knapsack.cpp
```

---

## Supported Files

* **Code:** `.cpp`, `.c`, `.cc`, `.py`, `.java` → syntax highlighted with `minted`
* **Images:** `.png`, `.jpg`, `.jpeg`, `.pdf` → included in notebook
* **LaTeX:** `.tex` → inserted directly

---

## Usage

```bash
python3 script.py
```

This will generate `contents.tex` and compile `notebook.pdf` automatically.

---

## Requirements (Linux)

Install everything on a fresh Ubuntu:

```bash
sudo apt update
sudo apt install -y python3 python3-pip texlive-full latexmk
pip3 install pygments
```

Verify installation:

```bash
python3 --version
pdflatex --version
latexmk -v
pygmentize -V
```

Once done, run the script and your notebook is ready.
