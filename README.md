# External Merge Sort Simulation

## 📌 Overview

This project implements **External Merge Sort**, a sorting algorithm used when the dataset is too large to fit into main memory (RAM).

Instead of sorting all data at once, the algorithm divides the dataset into smaller chunks, sorts them individually, and then merges them to produce a fully sorted output.

---

## ⚙️ How It Works

### 1. Data Generation

A large dataset is generated and stored in a file (`large_dataset.txt`).

### 2. Run Creation

* The dataset is divided into smaller chunks that fit into memory
* Each chunk is sorted in memory
* Sorted chunks are stored as **runs** in the `initial_runs/` folder

### 3. Merge Phase

* Multiple sorted runs are merged step-by-step
* Each merge step creates folders like `merge_pass_0`, `merge_pass_1`
* This process continues until only one sorted file remains

### 4. Final Output

* The fully sorted data is stored in `sorted_output.txt`

---

## 🗂️ Project Structure

```
external-merge-sort-simulation/
│
├── code/              # Source files (.cpp, .h)
├── initial_runs/      # Initial sorted chunks (generated)
├── merge_pass_*/      # Intermediate merge steps (generated)
├── sorted_runs/       # Final merged runs (generated)
├── large_dataset.txt  # Input data (generated)
├── sorted_output.txt  # Final output (generated)
```

---

## ▶️ How to Run

```bash
g++ code/*.cpp -o external_sort
.\external_sort.exe
```

---

## 🧠 Key Concepts

* External Sorting
* Divide and Conquer
* File Handling
* Multi-way Merge

---

## 💻 Language Used

C++

---

## 📌 Notes

* Output files and folders are automatically generated during execution
* Ensure you run the program from the project root directory
