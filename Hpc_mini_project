# 🚀 Huffman Encoding on GPU (Mini Project)

This project demonstrates how to **compress data faster** using **Huffman Encoding** with the help of **GPU acceleration**. It's built using Python, Numba, and CUDA.

---

## 📌 What is Huffman Encoding?

Huffman Encoding is a **lossless compression** technique that assigns:
- **Shorter codes** to frequently occurring symbols
- **Longer codes** to rare symbols

This reduces the overall size of the data without losing any information — like zipping a file!

---

## ⚡️ Why GPU?

Traditional CPU-based implementations handle data sequentially, which is slow for large files. In contrast, **GPUs have thousands of cores** that can process large amounts of data **in parallel**, making compression much faster.

---

## 🔧 How It Works

1. **Input a message or file** (as bytes)
2. **Count symbol frequencies** (GPU histogram)
3. **Build Huffman Tree** (CPU)
4. **Generate binary codes** for each symbol
5. **Use GPU to encode symbols** into a binary stream
6. **Pack the bits into bytes** and return compressed output

---

## 🛠 Technologies Used

- **Python**
- **NumPy** – Array handling
- **Numba with CUDA** – Writing GPU code in Python
- **heapq** – Huffman Tree construction
- **CUDA-enabled GPU** (e.g. NVIDIA GTX/RTX)

---

## 📈 Results

For the string:  
`"this is an example for huffman encoding on the GPU"`

- **Original size:** 50 bytes (400 bits)  
- **Compressed size:** 26 bytes (208 bits) + 1 padding bit  
- **Compression ratio:** ~52%  

This shows effective compression **with faster encoding** using GPU.

---

## 🧠 Challenges Faced

- Managing memory between CPU and GPU
- Prefix-sum calculation for bit offsets had to be done on CPU
- Small input sizes don't benefit much due to GPU overhead

---

## 🔮 Future Improvements

- Move more logic (like tree-building) to GPU
- Add **GPU-based decoder**
- Enable real-time applications like video or file stream compression
- Package the implementation into a **Python module or C++ extension**

---

## 📝 How to Run

```bash
# Clone the repo and install dependencies
git clone https://github.com/your-username/huffman-gpu
cd huffman-gpu
pip install numpy numba

# Run the main script
python miniproject.py
