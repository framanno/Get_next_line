# **get_next_line**

This project implements the `get_next_line` function, which reads a line of text from a file, one line at a time, until the end of the file.

---

## **Testing**

### **Mandatory Part**

1. Download the repository.
2. Open `get_next_line.c`.
3. De-comment the main function (remove the `/*` at the top and `*/` at the bottom).
4. Save the file.
5. Compile with:
   ```bash
   gcc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c
   ```
6. Execute the code:
   ```bash
   ./a.out fd0.txt
   ```

### **Bonus Part**

1. Download the repository.
2. Open `get_next_line_bonus.c`.
3. De-comment the main function (remove the `/*` at the top and `*/` at the bottom).
4. Save the file.
5. Compile with:
   ```bash
   gcc -Wall -Werror -Wextra get_next_line_bonus.c get_next_line_utils_bonus.c
   ```
6. Execute the code:
   ```bash
   ./a.out fd1.txt fd2.txt fd3.txt
   ```

---

## **Explanation with a Metaphor**

**The Librarian and the Giant Book**

Imagine you are a librarian who has to read a very large book (the file) aloud, but you can only read a limited number of characters at a time (`BUFFER_SIZE`). Additionally, you have a chalkboard on which you can write the words already read but not yet spoken aloud (`buff_data`).

Your goal is to read the book line by line and deliver each complete line to the listener. However, you might not immediately find a complete sentence that is ready to read, so you must keep track of what you’ve read so far and complete it in the next reading.

---

**Functions:**

### 1. `get_next_line`

This function calls the other functions to read the file in blocks and return one line at a time. `buff_data` is a temporary memory that holds data between reads. When the file is finished, it frees everything and returns `NULL`.

- **First Call:**
  - The file is open, and the buffer is empty.
  - `read_and_buffer` fills `buff_data` with the first chunk of data.
  
- **Next Call:**
  - `get_full_line` extracts the first complete line.
  - The buffer keeps the remaining data for the next read.
  
- **When the File is Finished:**
  - `read_and_buffer` no longer reads data.
  - `buff_data` is freed, and `get_next_line` returns `NULL`.

---

### 2. `read_and_buffer`

**Purpose:** "Read and put in the buffer."

This function reads a chunk of data from the file and adds it to the existing buffer. It uses a temporary buffer to manage the read operation. It reads until it finds a newline (`\n`). The updated buffer is returned.

- **Steps:**
  - If the buffer is empty or contains partial data, it allocates a temporary buffer and reads a block of data.
  - The data is merged with what’s already in `buff_data`.
  - The temporary buffer is freed.
  - The updated buffer is returned.

---

### 3. `read_until_eol`

**Purpose:** Reads data in blocks until it finds `\n` or the end of the file.

This function uses `read()` to get data and adds it to the main buffer. If `\n` is found, the loop ends.

- **Steps:**
  - **First Cycle:** `buff_data` is empty, a chunk of the file is read and stored.
  - **Subsequent Cycles:** Check for `\n`. If not found, read another chunk and add it.
  - **When `\n` is Found:** The cycle ends, and the buffer with the complete or partial line is returned.

---

### 4. `extract_line`

**Purpose:** Separates the first complete line from the buffer.

- **Steps:**
  - Finds the first `\n`.
  - If there’s data after the first line, it saves it as `leftover_data`.
  - Returns the line and keeps the remaining data intact.

---

### 5. `get_full_line`

**Purpose:** Completes the process by extracting a full line.

- **Steps:**
  - Calls `extract_line` to get the complete line.
  - Updates the buffer by removing the extracted line.
  - If there’s no more data, sets the buffer to `NULL`.
  - Returns the line, ready for use.

---

## **Utility Functions**

1. **`int ft_strlen`**
   - Returns the length of a string excluding the null terminator.

2. **`int *ft_strchr`**
   - Finds the first occurrence of a character in a string and returns a pointer to it, or `NULL` if not found.

3. **`char *ft_strjoin`**
   - Joins two strings with a separator.

4. **`char *ft_strdup`**
   - Duplicates a string: allocates memory and copies the source string to new memory.

5. **`char *ft_strncpy`**
   - Copies up to `n` characters from the source string to the destination string.

---

## **Memory Management**

### **Static Buffer Array (`buff_data`)**

This array is defined as `static char *buff_data[1024]`, meaning it is allocated once and persists for the lifetime of the program. Each element of this array is used to store buffered data for different file descriptors.

### **Dynamic Allocation in `read_and_buffer`**

In `read_and_buffer`, the temporary buffer is dynamically allocated with:
```c
malloc((BUFFER_SIZE + 1) * sizeof(char));
```
Once the data is processed, the temporary buffer is freed with:
```c
free(temp_buffer);
```

### **Dynamic Allocation in `extract_line`**

The `extract_line` function dynamically allocates memory for the line using:
```c
malloc(sizeof(char) * (line_len + 1));
```
If there’s leftover data in the buffer after extracting a line, `leftover_data` is also dynamically allocated using `ft_strdup`.

### **Memory Deallocation**

- After extracting a line, the old buffer data is freed with `free(*buff_data)` in `get_full_line`.
- If the extracted line is `NULL` (indicating an error or end of the file), the buffer for that file descriptor is freed and set to `NULL` in `get_next_line`.

---

## **Error Handling**

### **Memory Allocation Failure**

Whenever `malloc` is called, the code checks if the allocation was successful. If not, it returns `NULL` immediately, indicating an error. For instance, if `malloc` fails in `extract_line`, the function returns `NULL`.

---

This README now provides a clear and structured overview of your project, with improved formatting and readability for GitHub users.
